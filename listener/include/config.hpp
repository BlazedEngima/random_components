#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <string>

namespace Config::Listener
{

class Read
{
  public:
    std::string host;
    std::string username;
    std::string password;
    std::string database_name;
    std::string csv_file_path;

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

        host = config["host"];
        username = config["username"];
        password = config["password"];
        database_name = config["database_name"];
        csv_file_path = (dir_path / config["csv_file_path"]).string();

        stream.close();
        if (!spdlog::get("logger(config)"))
        {
            spdlog::stdout_color_mt("logger(config)");
        }
        std::shared_ptr<spdlog::logger> logger = spdlog::get("logger(config)");
        logger->info("Config file loaded successfully");
        logger->info("Host: {}", host);
        logger->info("Username: {}", username);
        logger->info("Database name: {}", database_name);
        logger->info("CSV file path: {}", csv_file_path);
    }
};

} // namespace Config::Listener
