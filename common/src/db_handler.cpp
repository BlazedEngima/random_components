#include <db_handler.hpp>

namespace Common
{

DBHandler::DBHandler(const std::string &host, const std::string &user, const std::string &password,
                     const std::string &db_name, const int port, const size_t pool_size)
    : db_name(db_name)
{
    if (!spdlog::get("logger(DB)"))
    {
        spdlog::stdout_color_mt("logger(DB)");
    }
    logger = spdlog::get("logger(DB)");

    try
    {
        for (size_t i = 0; i < pool_size; ++i)
        {
            mysqlx::Session *session = new mysqlx::Session(host, port, user, password, db_name);

            if (!session->getSchema(db_name).existsInDatabase())
            {
                session->createSchema(db_name);
            }

            sessions.push(session);
        }
    }
    catch (const std::exception &e)
    {
        logger->error("Failed to create a database session: {}", e.what());

        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        logger->error("An unknown exception was thrown.");

        std::exit(EXIT_FAILURE);
    }
}

DBHandler::~DBHandler()
{
    while (!sessions.empty())
    {
        delete sessions.front();
        sessions.pop();
    }
}

} // namespace Common