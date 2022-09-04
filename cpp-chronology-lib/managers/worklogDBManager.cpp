#include "worklogDBManager.h"
#include <iostream>
#include <chrono>

chronology::managers::WorklogDBManager::WorklogDBManager(
    const boost::filesystem::path& path)
{
    m_path = path;
    m_dbProvider = std::make_unique<providers::YamlDatabaseProvider>();
}

void chronology::managers::WorklogDBManager::Load()
{
    m_worklogList = m_dbProvider->Load(m_path);
    if (!m_worklogList["worklog_list"])
    {
        m_worklogList["worklog_list"] = YAML::Node();
    }

    records.clear();
    auto list = m_worklogList["worklog_list"];

    for (auto it=list.begin(); it!=list.end(); ++it)
    {
        auto item = it->as<YAML::Node>();

        // TODO: move this to function
        types::DailyRecord record;
        record.task_name = item["task"].as<std::string>();
        record.description = item["description"].as<std::string>();
        record.hours = item["hours"].as<float>();
        record.date = item["date"].as<std::time_t>();
        records.push_back(record);
    }
}

void chronology::managers::WorklogDBManager::AddRecord(const types::DailyRecord& record)
{
    // TODO: add some checks here also
    YAML::Node item;
    item["task"] = record.task_name;
    item["description"] = record.description;
    item["hours"] = record.hours;
    item["date"] = record.date;

    m_worklogList["worklog_list"].push_back(item);
    m_dbProvider->Save(m_worklogList, m_path);

    //records.push_back(record);
    //Load();
}

void chronology::managers::WorklogDBManager::RemoveRecord(uuid_t recordId)
{
    std::remove_if(
        records.begin(),
        records.end(),
        [recordId](const types::DailyRecord& record) { return record.id == recordId; }
    );
}