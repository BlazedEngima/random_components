#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>

namespace Config::Poster
{

class Read
{
  public:
    std::string API_KEY;
    std::string API_SECRET;

    Read(const std::filesystem::path &filepath)
    {
        std::filesystem::path dir_path = std::filesystem::current_path();
        std::filesystem::path config_path = dir_path / filepath;

        std::ifstream stream(config_path);
        if (!stream.is_open())
        {
            throw std::runtime_error("Could not open config file at path: " + config_path.string());
        }

        nlohmann::json config;
        stream >> config;

        API_KEY = config["API_KEY"];
        API_SECRET = config["API_SECRET"];

        stream.close();
        if (!spdlog::get("logger(config)"))
        {
            spdlog::stdout_color_mt("logger(config)");
        }
        std::shared_ptr<spdlog::logger> logger = spdlog::get("logger(config)");
        logger->info("Config file loaded successfully");
    }
};

} // namespace Config::Poster
