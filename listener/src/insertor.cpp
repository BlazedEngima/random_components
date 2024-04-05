#include <insertor.hpp>

namespace Listener::DB
{

void Insertor::insert_to_db(const std::string &symbol, const double price, const uint64_t timestamp)
{
    std::lock_guard<std::mutex> lock(mutex);

    mysqlx::Session *session = sessions.front();
    sessions.pop();
    try
    {
        // Start a transaction
        session->startTransaction();

        // Get the schema
        mysqlx::Schema schema = session->getSchema(db_name);

        // Check if the table exists
        if (!schema.getTable(symbol).existsInDatabase())
        {
            // If the table does not exist, create it
            std::string create_table_query =
                "CREATE TABLE " + symbol + " (price DOUBLE, timestamp BIGINT UNSIGNED, PRIMARY KEY (timestamp))";
            session->sql(create_table_query).execute();
        }

        // Get the table
        mysqlx::Table table = schema.getTable(symbol);

        // Insert a new row
        table.insert("price", "timestamp").values(price, timestamp).execute();

        // Commit the transaction
        session->commit();
    }
    catch (const std::exception &e)
    {
        // Rollback the transaction
        session->rollback();

        logger->error("Failed to insert trade: {}", e.what());

        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        // Rollback the transaction
        session->rollback();

        logger->error("An unknown exception was thrown.");

        std::exit(EXIT_FAILURE);
    }

    // Return the session to the pool
    sessions.push(session);
}

Insertor::Insertor(const std::string &host, const std::string &user, const std::string &password,
                   const std::string &db_name, const int port, const size_t pool_size)
    : Common::DBHandler(host, user, password, db_name, port, pool_size)
{
}

} // namespace Listener::DB