#include <mutex>
#include <mysqlx/devapi/result.h>
#include <mysqlx/xdevapi.h>
#include <reader.hpp>
#include <vector>

namespace Poster::DB
{

std::vector<mysqlx::Row> Reader::read(const std::string &table_name)
{
    std::lock_guard<std::mutex> lock(mutex);
    mysqlx::Session *session = sessions.front();
    sessions.pop();

    std::vector<mysqlx::Row> events;

    try
    {
        session->startTransaction();
        mysqlx::Schema schema = session->getSchema(db_name);

        // Check if the table exists
        if (!schema.getTable(table_name).existsInDatabase())
        {
            // If the table does not exist, create it
            logger->error("Table {} does not exist.", table_name);
            std::exit(EXIT_FAILURE);
        }

        // Lock the table
        session->sql("LOCK TABLES " + table_name + " WRITE").execute();

        mysqlx::Table table = schema.getTable(table_name);
        mysqlx::RowResult results = table.select().execute();
        events = results.fetchAll();

        session->sql("TRUNCATE TABLE " + table_name).execute(); // Truncate the table (delete all rows)

        // Unlock the table
        session->sql("UNLOCK TABLES").execute();

        session->commit();
    }
    catch (const std::exception &e)
    {
        session->rollback();
        logger->error("Failed to read from table: {}", e.what());
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        session->rollback();
        logger->error("An unknown exception was thrown.");
        std::exit(EXIT_FAILURE);
    }

    sessions.push(session);

    return events;
};

} // namespace Poster::DB