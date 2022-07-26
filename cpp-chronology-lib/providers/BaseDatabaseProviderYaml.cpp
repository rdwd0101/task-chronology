#include "BaseDatabaseProviderYaml.h"

void chronology::providers::BaseDatabaseProviderYaml::Load(const boost::filesystem::path& path)
{
    if (path.empty())
    {
        return;
    }
    if (!boost::filesystem::exists(path))
    {
        return;
    }
    m_database = YAML::LoadFile(path.string());
}

void chronology::providers::BaseDatabaseProviderYaml::Save(const boost::filesystem::path& path)
{
    if (m_database.IsNull())
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
    fout << m_database;
}
