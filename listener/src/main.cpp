#include <atomic>
#include <commons.hpp>
#include <compute.hpp>
#include <config.hpp>
#include <csv_sym_parser.hpp>
#include <db_handler.hpp>
#include <jobs.hpp>
#include <listener.hpp>
#include <memory>
#include <mutex>
#include <requester.hpp>
#include <sym_handler.hpp>

constexpr int MAX_THREADS = 4;
constexpr int DB_PORT = 33060;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config_file_path>" << std::endl;
        return 1;
    }

    std::atomic<bool> running{true};
    Common::JobQueue jobs{MAX_THREADS};
    std::shared_ptr<Config::Read> info = std::make_shared<Config::Read>(argv[1]);
    std::shared_ptr<Common::book> logbook = std::make_shared<Common::book>();
    std::shared_ptr<Listener> listener = std::make_shared<Listener>(logbook);
    std::shared_ptr<DBHandler> db = std::make_shared<DBHandler>(info->host, info->username, info->password,
                                                                info->database_name, DB_PORT, MAX_THREADS);

    // std::vector<std::string> symbols = Requester::get_top_assets(50);
    std::vector<std::string> symbols = CSVSymParser::parse(info->csv_file_path);

    // subsribe to the top 50 symbols
    for (const std::string &symbol : symbols)
    {
        auto lowercase_symbol = std::make_shared<std::string>(symbol);
        std::transform(lowercase_symbol->begin(), lowercase_symbol->end(), lowercase_symbol->begin(), ::tolower);
        listener->connect("wss://fstream.binance.com/ws/" + *lowercase_symbol + "@trade");
    }

    jobs.enqueue([&listener] { listener->run(); });

    while (running)
    {
        std::this_thread::sleep_for(std::chrono::minutes(1));

        for (const std::pair<const std::string, Common::DataType::Record> &symbol : (*logbook))
        {
            jobs.enqueue([&logbook, symbol = symbol.first, &db, &jobs] {
                std::lock_guard<std::mutex> lock((*logbook)[symbol].mutex);
                const auto &vec = (*logbook)[symbol].data;

                if (vec.empty())
                {
                    return;
                }

                double avg = Common::Compute::Average::minute(vec);
                uint64_t timestamp = vec.back().second;

                jobs.enqueue([&db, symbol, avg, timestamp] {
                    // may include exchange type in the future (switch + enum)
                    std::string lowercase = SymHandler::Binance::transform(symbol);
                    db->insert_to_db(lowercase, avg, timestamp);
                });
            });
        }
    }

    return 0;
}