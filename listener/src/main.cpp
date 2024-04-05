#include <atomic>
#include <commons.hpp>
#include <compute.hpp>
#include <config.hpp>
#include <csv_sym_parser.hpp>
#include <exchanges.hpp>
#include <insertor.hpp>
#include <jobs.hpp>
#include <listener.hpp>
#include <memory>
#include <mutex>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <string>
#include <sym_handler.hpp>

constexpr int MAX_THREADS = 4;
constexpr int DB_PORT = 33060;

int main(int argc, char *argv[])
{
    if (!spdlog::get("logger(listener)"))
    {
        spdlog::stdout_color_mt("logger(listener)");
    }
    std::shared_ptr<spdlog::logger> logger = spdlog::get("logger(listener)");
    if (argc != 2)
    {
        logger->error("Usage: {} <config_file_path>", argv[0]);
        return 1;
    }

    std::atomic<bool> running{true};
    Common::Tools::JobQueue jobs{MAX_THREADS};
    std::shared_ptr<Config::Listener::Read> info = std::make_shared<Config::Listener::Read>(argv[1]);
    std::shared_ptr<Common::book> logbook = std::make_shared<Common::book>();
    std::shared_ptr<Components::Listener> listener = std::make_shared<Components::Listener>(logbook);
    std::shared_ptr<Listener::DB::Insertor> db = std::make_shared<Listener::DB::Insertor>(
        info->host, info->username, info->password, info->database_name, DB_PORT, MAX_THREADS);

    std::vector<std::string> symbols = Config::Listener::CSVSymParser::parse(info->csv_file_path);

    // subsribe to the top 50 symbols
    for (const std::string &symbol : symbols)
    {
        std::shared_ptr<std::string> lowercase_symbol = std::make_shared<std::string>(symbol);
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
                    std::string lowercase = Listener::Handler::Symbol::Binance::transform(symbol);
                    db->insert_to_db(lowercase, avg, timestamp);
                });
            });
        }
    }

    return 0;
}