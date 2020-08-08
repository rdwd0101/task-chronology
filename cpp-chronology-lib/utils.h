#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <string>

namespace chronology
{
    namespace utils
    {
        std::string GetUUID();
        void SaveJSON(const boost::property_tree::ptree& pt);
        void LoadJSON(const boost::filesystem::path& path);
    }
}