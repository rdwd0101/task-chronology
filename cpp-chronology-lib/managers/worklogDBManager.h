#pragma once
#include <boost/filesystem.hpp>
#include "../providers/YamlDatabaseProvider.h"
#include "../types/dailyrecord.h"

namespace chronology
{
    namespace managers
    {
        class WorklogDBManager
        {
        public:
            std::vector<types::DailyRecord> records;

        private:    
            std::unique_ptr<providers::YamlDatabaseProvider> m_dbProvider;
            boost::filesystem::path m_path;
            YAML::Node m_worklogList;

        public:
            WorklogDBManager(const boost::filesystem::path& path);
            void Load();
            void AddRecord(const types::DailyRecord& record);
            void RemoveRecord(uuid_t recordId);
        };
    }
}