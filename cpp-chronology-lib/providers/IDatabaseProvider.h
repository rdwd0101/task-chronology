#pragma once
#include <boost/filesystem.hpp>

namespace chronology
{
    namespace providers
    {
        class IDatabaseProvider
        {
        public:
            virtual ~IDatabaseProvider() {};
            virtual void Load(const boost::filesystem::path& path) = 0;
            virtual void Save(const boost::filesystem::path& path) = 0;
        };
    }
}