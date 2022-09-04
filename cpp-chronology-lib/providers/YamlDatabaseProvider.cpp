#include "YamlDatabaseProvider.h"
#include <error.h>
#include <iostream>

YAML::Node chronology::providers::YamlDatabaseProvider::Load(const boost::filesystem::path& path)
{
    if (path.empty())
    {
        throw new std::runtime_error("Provided path is empty or does not exist");
    }

    auto abs_path = boost::filesystem::system_complete(path);
    std::cout << "abs file path: " << abs_path.c_str() << std::endl;
    if (!boost::filesystem::exists(abs_path))
    {
        YAML::Node node;
        return node;
    }

    return YAML::LoadFile(path.string());
}

void chronology::providers::YamlDatabaseProvider::Save(YAML::Node data, const boost::filesystem::path& path)
{
    if (data.IsNull())
    {
        std::cout << "invalid data" << std::endl;
        throw new std::runtime_error("Provided data is empty");
    }
    if (path.empty())
    {
        std::cout << "invalid path (empty)" << std::endl;
        throw new std::runtime_error("Provided [path is empty");
    }
    auto abs_path = boost::filesystem::system_complete(path);

    std::ofstream fout(abs_path.string());
    fout << data;
}
