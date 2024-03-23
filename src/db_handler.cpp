#include <db_handler.hpp>
#include <iostream>

DBHandler::DBHandler(
    const std::string &host,
    const std::string &user,
    const std::string &password,
    const std::string &db_name,
    const int &port) : db_name(db_name)
{
    try
    {
        session = new mysqlx::Session(host, port, user, password, db_name);
        // Check if the database exists
        if (!session->getSchema(db_name).existsInDatabase())
        {
            // If the database does not exist, create it
            session->createSchema(db_name);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to create a database session: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        std::cerr << "An unknown exception was thrown." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

DBHandler::~DBHandler()
{
    delete session;
}

void DBHandler::insert_to_db(const std::string &symbol, const double &price, const u_int64_t &time)
{
    std::lock_guard<std::mutex> lock(mutex);
    try
    {
        // Get the schema
        mysqlx::Schema schema = session->getSchema(db_name);

        // Check if the table exists
        std::string table_name = symbol + "_USDT";
        if (!schema.getTable(table_name).existsInDatabase())
        {
            // If the table does not exist, create it
            std::string create_table_query = "CREATE TABLE " + table_name + " (price DOUBLE, timestamp BIGINT UNSIGNED, PRIMARY KEY (timestamp))";
            session->sql(create_table_query).execute();
        }

        // Get the table
        mysqlx::Table table = schema.getTable(table_name);

        // Insert a new row
        table.insert("price", "timestamp")
            .values(price, time)
            .execute();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to insert trade: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        std::cerr << "An unknown exception was thrown." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}