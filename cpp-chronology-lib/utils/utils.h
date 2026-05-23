#pragma once
#include <boost/uuid/uuid.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <uuid/uuid.h>

namespace chronology
{
    namespace utils
    {
        std::string GenerateUUID();
        std::string UUIDtoStr(const uuid_t uuid);
        /*
        void SaveJSONToFile(const boost::property_tree::ptree& pt);
        void LoadJSONFromFile(const boost::filesystem::path& path);
        */
    }
}