#pragma once

#include <sqlite3.h>

#include <inttypes.h>
#include <string.h>
#include <memory>
#include <filesystem>

namespace chronology
{
    class DatabaseWrapper
    {
    public:
        DatabaseWrapper();
        ~DatabaseWrapper();

        bool open(const std::filesystem::path& path);
        bool prepareQuery(const std::string& query);
        bool bindToQuery(int index, const std::string& value);
        bool bindToQueryInt64(int index, const int64_t value);
        bool bindToQueryReal(int index, const double value);
        bool executeQuery();
        bool executeQuery(const std::string& query);
        bool getQueryResult(const int column, std::string& outResult);
        bool getQueryResultInt64(const int column, int64_t& outResult);
        bool getQueryResultReal(const int column, double& outResult);
        size_t getLastInsertRowid();

        std::string getLastErrorMsg();
        int getLastErrorCode();

    private:
        sqlite3 *m_database;
        sqlite3_stmt *m_statement;
        std::string m_lastErrorDescription;
        int m_lastErrCode;
    };
}