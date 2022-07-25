#pragma once
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>

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
            void Load(const boost::filesystem::path& path);
            void Save(const boost::filesystem::path& path);
        };
    }
}