#include "DatabaseWrapper.h"

chronology::DatabaseWrapper::DatabaseWrapper()
{}

chronology::DatabaseWrapper::~DatabaseWrapper()
{
    if (this->m_database)
    {
        sqlite3_close(this->m_database);
    }
}

bool chronology::DatabaseWrapper::open(const std::filesystem::path& path)
{
    // assume that path is valid
    if (sqlite3_open(path.c_str(), &this->m_database) == SQLITE_OK)
    {
        sqlite3_prepare_v2(this->m_database, "PRAGMA foreign_keys;", -1, &this->m_statement, 0);
        return true;
    }
    else
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));

        return false;
    }
}

bool chronology::DatabaseWrapper::prepareQuery(const std::string& query)
{
    // first, finalize previous statement
    if (sqlite3_finalize(this->m_statement) == SQLITE_MISUSE)
    {
        return false;
    }

    if (sqlite3_prepare_v2(this->m_database, query.c_str(), -1, &this->m_statement, 0) == SQLITE_OK)
    {   
        return true;
    }
    else
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));

        fprintf(stderr, "DatabaseWrapper prepare query error: %s\n", sqlite3_errmsg(this->m_database));
        return false;
    }
}

bool chronology::DatabaseWrapper::bindToQuery(
        int index,
        const std::string& value
        )
{
    int stat = sqlite3_bind_text(this->m_statement, ++index, value.c_str(), value.size(), NULL);

    if (stat == SQLITE_OK)
    {
        return true;
    }
    else
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));

        fprintf(stderr, "DatabaseWrapper bind error: %s\n", sqlite3_errmsg(this->m_database));
        return false;
    }
}

bool chronology::DatabaseWrapper::bindToQueryInt64(
        int index,
        const int64_t value
        )
{
    int stat = sqlite3_bind_int64(this->m_statement, ++index, value);

    if (stat == SQLITE_OK)
    {
        return true;
    }
    else
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));

        fprintf(stderr, "DatabaseWrapper bind error: %s\n", sqlite3_errmsg(this->m_database));
        return false;
    }
}

bool chronology::DatabaseWrapper::bindToQueryReal(
        int index,
        const double value
        )
{
    int stat = sqlite3_bind_double(this->m_statement, ++index, value);

    if (stat == SQLITE_OK)
    {
        return true;
    }
    else
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));

        fprintf(stderr, "DatabaseWrapper bind error: %s\n", sqlite3_errmsg(this->m_database));
        return false;
    }
}

bool chronology::DatabaseWrapper::executeQuery()
{
    //fprintf(stderr, "Executing query: %s\n", sqlite3_expanded_sql(this->m_statement));
    switch (sqlite3_step(this->m_statement))
    {
        case SQLITE_ROW:
            return true;
            break;
        case SQLITE_DONE:
            return true;
            break;
        default:
            m_lastErrCode = sqlite3_errcode(this->m_database);
            m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));

            fprintf(stderr, "DatabaseWrapper execute error: %s\n", sqlite3_errmsg(this->m_database));
            return false;
            break;
    }
}

bool chronology::DatabaseWrapper::executeQuery(const std::string& query)
{
    this->prepareQuery(query);
    return this->executeQuery();
}

bool chronology::DatabaseWrapper::getQueryResult(const int column, std::string& outResult)
{
    const unsigned char* databaseItem = sqlite3_column_text(this->m_statement, column);
    int bytes = sqlite3_column_bytes(this->m_statement, column);
    int errorCode = sqlite3_errcode(this->m_database);

    if (errorCode != SQLITE_OK && errorCode != SQLITE_ROW)
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));

        fprintf(stderr, "DatabaseWrapper get query error: %d (%s)\n", m_lastErrCode, m_lastErrorDescription.c_str());
        return false;
    }

    outResult.assign(databaseItem, databaseItem + bytes);
    return true;
}

bool chronology::DatabaseWrapper::getQueryResultInt64(const int column, int64_t& outResult)
{
    int64_t result = sqlite3_column_int64(this->m_statement, column);
    int errorCode = sqlite3_errcode(this->m_database);

    if (errorCode != SQLITE_OK && errorCode != SQLITE_ROW)
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));
        
        fprintf(stderr, "DatabaseWrapper get query error: %d (%s)\n", errorCode, sqlite3_errmsg(this->m_database));
        return false;
    }

    outResult = result;
    return true;
}

bool chronology::DatabaseWrapper::getQueryResultReal(const int column, double& outResult)
{
    double result = sqlite3_column_double(this->m_statement, column);
    int errorCode = sqlite3_errcode(this->m_database);

    if (errorCode != SQLITE_OK && errorCode != SQLITE_ROW)
    {
        m_lastErrCode = sqlite3_errcode(this->m_database);
        m_lastErrorDescription = std::string(sqlite3_errmsg(this->m_database));
        
        fprintf(stderr, "DatabaseWrapper get query error: %d (%s)\n", errorCode, sqlite3_errmsg(this->m_database));
        return false;
    }

    outResult = result;
    return true;
}

size_t chronology::DatabaseWrapper::getLastInsertRowid()
{
    return sqlite3_last_insert_rowid(this->m_database);
}

std::string chronology::DatabaseWrapper::getLastErrorMsg()
{
    return this->m_lastErrorDescription;
}

int chronology::DatabaseWrapper::getLastErrorCode()
{
    return this->m_lastErrCode;
}