#pragma once
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>
#include <uuid/uuid.h>

#include "IDatabaseProvider.h"

namespace chronology
{
    namespace providers
    {
        class YamlDatabaseProvider
        {
        private:
            YAML::Node m_database;

        public:
            //virtual ~YamlDatabaseProvider() {};
            YAML::Node Load(const boost::filesystem::path& path);
            void Save(YAML::Node data, const boost::filesystem::path& path);
        };
    }
}