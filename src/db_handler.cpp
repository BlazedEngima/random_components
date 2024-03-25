#include <db_handler.hpp>
#include <sym_handler.hpp>
#include <iostream>
#include <sstream>

DBHandler::DBHandler(
    const std::string &host,
    const std::string &user,
    const std::string &password,
    const std::string &db_name,
    const int &port,
    const size_t &pool_size) : db_name(db_name)
{
    try
    {
        // Initialize the session pool
        for (size_t i = 0; i < pool_size; ++i)
        {
            mysqlx::Session *session = new mysqlx::Session(host, port, user, password, db_name);
            // Check if the database exists
            if (!session->getSchema(db_name).existsInDatabase())
            {
                // If the database does not exist, create it
                session->createSchema(db_name);
            }
            sessions.push(session);
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
    while (!sessions.empty())
    {
        delete sessions.front();
        sessions.pop();
    }
}

// may include exchange type in the future (switch + enum)
void DBHandler::insert_to_db(const std::string &symbol, const double &price, const u_int64_t &time)
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

        // Get the lowercase symbol
        std::string lowercase_symbol = SymHandler::Binance::transform(symbol);

        // Check if the table exists
        std::stringstream ss;
        ss << lowercase_symbol << "_usdt_futures";
        if (!schema.getTable(ss.str()).existsInDatabase())
        {
            // If the table does not exist, create it
            std::string create_table_query = "CREATE TABLE " + ss.str() + " (price DOUBLE, timestamp BIGINT UNSIGNED, PRIMARY KEY (timestamp))";
            session->sql(create_table_query).execute();
        }

        // Get the table
        mysqlx::Table table = schema.getTable(ss.str());

        // Insert a new row
        table.insert("price", "timestamp")
            .values(price, time)
            .execute();

        // Commit the transaction
        session->commit();
    }
    catch (const std::exception &e)
    {
        // Rollback the transaction
        session->rollback();
        std::cerr << "Failed to insert trade: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        // Rollback the transaction
        session->rollback();
        std::cerr << "An unknown exception was thrown." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Return the session to the pool
    sessions.push(session);
}