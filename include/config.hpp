#ifndef CONFIG_H
#define CONFIG_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

class config
{
public:
    std::string host;
    std::string username;
    std::string password;
    std::string database_name;

    config(const std::string &filename)
    {
        std::filesystem::path dir_path = std::filesystem::current_path();
        std::string config_path = (dir_path / filename).string();

        std::ifstream stream(config_path);
        if (!stream.is_open())
        {
            throw std::runtime_error("Could not open config file at path: " + config_path);
        }

        nlohmann::json data;
        stream >> data;

        host = data["host"];
        username = data["username"];
        password = data["password"];
        database_name = data["database_name"];
    }
};

#endif