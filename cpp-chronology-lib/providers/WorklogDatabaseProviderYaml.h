#pragma once
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>
#include <uuid/uuid.h>

#include "../types/dailyrecord.h"
#include "YamlDatabaseProvider.h"

namespace chronology
{
    namespace providers
    {
        class WorklogDatabaseProviderYaml : public YamlDatabaseProvider
        {
        private:
            const std::string m_yamlKey = "records";

        public:
            virtual ~WorklogDatabaseProviderYaml() {};
            void AddRecord(const types::DailyRecord& record);
            void RemoveRecord(uuid_t recordId);
        };
    }
}
