#ifndef CONFIG_H
#define CONFIG_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

class Config
{
public:
    std::string host;
    std::string username;
    std::string password;
    std::string database_name;
    std::string csv_file_path;

    Config(const std::string &filename)
    {
        std::filesystem::path dir_path = std::filesystem::current_path();
        std::string config_path = (dir_path / filename).string();

        std::ifstream stream(config_path);
        if (!stream.is_open())
        {
            throw std::runtime_error("Could not open config file at path: " + config_path);
        }

        nlohmann::json config;
        stream >> config;

        host = config["host"];
        username = config["username"];
        password = config["password"];
        database_name = config["database_name"];
        csv_file_path = (dir_path / config["csv_file_path"]).string();
    }
};

#endif