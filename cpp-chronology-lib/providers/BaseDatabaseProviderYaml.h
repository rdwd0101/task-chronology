#pragma once
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>
#include <uuid/uuid.h>
#include "IDatabaseProvider.h"

namespace chronology
{
    namespace providers
    {
        class BaseDatabaseProviderYaml : public IDatabaseProvider
        {
        private:
            YAML::Node m_database;

        public:
            virtual ~BaseDatabaseProviderYaml() {};
            void Load(const boost::filesystem::path& path) override;
            void Save(const boost::filesystem::path& path) override;
            
            virtual void RemoveRecord(uuid_t recordId) = 0;
        };
    }
}