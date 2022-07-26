#pragma once
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>
#include <uuid/uuid.h>

#include "../types/task.h"
#include "BaseDatabaseProviderYaml.h"

namespace chronology
{
    namespace providers
    {
        class WorklogDatabaseProviderYaml : public BaseDatabaseProviderYaml
        {
        private:
            const std::string m_yamlKey = "tasks";

        public:
            virtual ~WorklogDatabaseProviderYaml() {};
            void AddRecord(const types::Task& record);
            void RemoveRecord(uuid_t recordId) override;
        };
    }
}
