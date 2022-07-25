#pragma once
#include <boost/filesystem.hpp>
#include "../providers/IDatabaseProvider.h"
#include "../types/dailyrecord.h"

namespace chronology
{
    namespace managers
    {
        class WorklogDBManager
        {
        private:
            boost::filesystem::path m_dbPath;
            std::vector<types::DailyRecord> m_records;
            std::unique_ptr<providers::IDatabaseProvider> m_dbProvider;

        public:
            WorklogDBManager(const boost::filesystem::path& path, providers::IDatabaseProvider* dbProvider);
        };
    }
}