#include <chrono>
#include "utils.h"

std::string chronology::utils::GenerateUUID()
{
    uuid_t uuid;
    uuid_generate(uuid);
    
    return UUIDtoStr(uuid);
}

std::string chronology::utils::UUIDtoStr(const uuid_t uuid)
{
    char str[37] = {};
    sprintf(str, 
    "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", 
        uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7],
        uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
    );
    return std::string(str);
}
/*
void SaveJSON(const boost::property_tree::ptree& pt)
{
    return;
}

void LoadJSON(const boost::filesystem::path path)
{
    return;
}

void LoadYAML(const boost::filesystem::path path)
{
    YAML::Emitter out;
    out << "Hello, world!";
}

std::chrono::system_clock::time_point GetCurrentTime()
{
    const auto time = std::chrono::system_clock::now();
    return time;
}
*/