#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <jobs.hpp>
#include <config.hpp>
#include <commons.hpp>
#include <listener.hpp>
#include <requester.hpp>
#include <db_handler.hpp>

constexpr int MAX_THREADS = 4;
constexpr int DB_PORT = 33060;

int main(int argc, char *argv[])
{
    std::atomic<bool> running{true};
    Job::Queue jobs{MAX_THREADS};
    std::shared_ptr<Config> config = std::make_shared<Config>(argv[1]);
    std::shared_ptr<book> logbook = std::make_shared<book>();
    std::shared_ptr<Listener> listener = std::make_shared<Listener>(logbook);
    std::shared_ptr<DBHandler> db = std::make_shared<DBHandler>(
        config->host, config->username, config->password, config->database_name, DB_PORT);

    std::vector<std::string> symbols = Requester::get_top_assets(50);
    // subsribe to the top 50 symbols
    for (const std::string symbol : symbols)
    {
        auto lowercase_symbol = std::make_shared<std::string>(symbol);
        std::transform(lowercase_symbol->begin(), lowercase_symbol->end(), lowercase_symbol->begin(), ::tolower);
        listener->connect("wss://fstream.binance.com/ws/" + *lowercase_symbol + "@trade");
    }

    jobs.enqueue(
        [&listener]
        {
            listener->run();
        });

    while (running)
    {
        std::this_thread::sleep_for(std::chrono::minutes(1));

        for (const auto &symbol : (*logbook))
        {
            jobs.enqueue(
                [&logbook, symbol = symbol.first, &db]
                {
                    std::lock_guard<std::mutex> lock((*logbook)[symbol].mutex);
                    const auto &vec = (*logbook)[symbol].data;

                    if (vec.empty())
                    {
                        return;
                    }

                    double sum = std::accumulate(vec.begin(), vec.end(), 0.0,
                                                 [](double acc, const std::pair<double, uint64_t> &p)
                                                 {
                                                     return acc + p.first;
                                                 });

                    double average = sum / vec.size();
                    double time = vec.back().second;
                    db->insert_to_db(symbol, average, time);
                });
        }
    }

    return 0;
}