#include "YamlDatabaseProvider.h"
#include <error.h>

YAML::Node chronology::providers::YamlDatabaseProvider::Load(const boost::filesystem::path& path)
{
    if (path.empty())
    {
        throw new std::runtime_error("Provided path is empty or does not exist");
    }
    return YAML::LoadFile(path.string());
    /*
    if (m_database["lastLogin"]) {

    }
    for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
  std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() << "\n";
    }
    */
}

void chronology::providers::YamlDatabaseProvider::Save(YAML::Node data, const boost::filesystem::path& path)
{
    if (data.IsNull())
    {
        return;
    }
    if (path.empty())
    {
        return;
    }
    if (!boost::filesystem::exists(path))
    {
        return;
    }

    std::ofstream fout(path.string());
    fout << data;
}
