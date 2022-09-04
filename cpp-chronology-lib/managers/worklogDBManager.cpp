#include "worklogDBManager.h"
#include <iostream>

chronology::managers::WorklogDBManager::WorklogDBManager(
    const boost::filesystem::path& path)
{
    m_path = path;
    m_dbProvider = std::make_unique<providers::YamlDatabaseProvider>();
}

void chronology::managers::WorklogDBManager::Load()
{
    auto node = m_dbProvider->Load(m_path);
    if (!node["worklog_list"])
    {
        throw std::runtime_error("File with invalid format provided");
    }
    auto list = node["worklog_list"];
    std::cout << "Is sequence: " << list.IsSequence() << std::endl;

    for (auto it=list.begin(); it!=list.end(); ++it)
    {
        auto item = it->as<YAML::Node>();

        // TODO: move this to function
        types::DailyRecord record;
        record.task_name = item["task"].as<std::string>();
        record.description = item["description"].as<std::string>();
        record.hours = item["hours"].as<float>();
        //record.started = item["date"].as<int>();
        records.push_back(record);
    }
}

void chronology::managers::WorklogDBManager::AddRecord(const types::DailyRecord& record)
{
    // TODO: add some checks here also
    records.push_back(record);
}

void chronology::managers::WorklogDBManager::RemoveRecord(uuid_t recordId)
{
    std::remove_if(
        records.begin(),
        records.end(),
        [recordId](const types::DailyRecord& record) { return record.id == recordId; }
    );
}