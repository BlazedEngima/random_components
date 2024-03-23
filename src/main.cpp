#include <jobs.hpp>
#include <datatype.hpp>
#include <config.hpp>
#include <listener.hpp>
#include <memory>

constexpr int MAX_THREADS = 4;

int main(int argc, char *argv[])
{
    Job::Queue jobs{MAX_THREADS};
    std::shared_ptr<Config> config = std::make_shared<Config>(argv[1]);
    std::shared_ptr<book> logbook = std::make_shared<book>();
    Listener listener = Listener(logbook);
    listener.connect("wss://fstream.binance.com/ws/btcusdt@trade");
    return 0;
}