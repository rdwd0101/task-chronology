#include <chrono>
#include "utils.h"

std::string chronology::utils::GetUUID()
{
    return std::string();
}

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
