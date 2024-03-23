#include <jobs.hpp>
#include <config.hpp>
#include <memory>

constexpr int MAX_THREADS = 4;

int main(int argc, char *argv[]) {
    job::queue jobs{MAX_THREADS};
    std::shared_ptr<config> cfg = std::make_shared<config>(argv[1]);
    return 0;
}