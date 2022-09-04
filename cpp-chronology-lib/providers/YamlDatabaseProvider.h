#pragma once
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>
#include <uuid/uuid.h>

#include "IDatabaseProvider.h"

namespace chronology
{
    namespace providers
    {
        class YamlDatabaseProvider : public IDatabaseProvider
        {
        private:
            YAML::Node m_database;

        public:
            virtual ~YamlDatabaseProvider() {};
            void Load(const boost::filesystem::path& path) override;
            void Save(const boost::filesystem::path& path) override;
        };
    }
}