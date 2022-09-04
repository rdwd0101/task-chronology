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
            //boost::filesystem::path m_dbPath;
            std::vector<types::DailyRecord> m_records;
            std::shared_ptr<providers::IDatabaseProvider> m_dbProvider;

        public:
            WorklogDBManager(
                std::shared_ptr<providers::IDatabaseProvider> dbProvider);
            void Load(const boost::filesystem::path& path);
            void AddRecord(const types::DailyRecord& record);
            void RemoveRecord(uuid_t recordId);
        };
    }
}