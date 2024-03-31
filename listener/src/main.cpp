#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <jobs.hpp>
#include <config.hpp>
#include <commons.hpp>
#include <compute.hpp>
#include <Listener.hpp>
#include <requester.hpp>
#include <db_handler.hpp>
#include <csv_sym_parser.hpp>
#include <sym_handler.hpp>

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

    // std::vector<std::string> symbols = Requester::get_top_assets(50);
    std::vector<std::string> symbols = CSVSymParser::parse(config->csv_file_path);

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
                [&logbook, symbol = symbol.first, &db, &jobs]
                {
                    std::lock_guard<std::mutex> lock((*logbook)[symbol].mutex);
                    const auto &vec = (*logbook)[symbol].data;

                    if (vec.empty())
                    {
                        return;
                    }

                    double avg = Compute::Average::minute(vec);
                    u_int64_t time = vec.back().second;

                    jobs.enqueue(
                        [&db, symbol, avg, time]
                        {
                            // may include exchange type in the future (switch + enum)
                            std::string lowercase = SymHandler::Binance::transform(symbol);
                            db->insert_to_db(lowercase, avg, time);
                        });
                });
        }
    }

    return 0;
}