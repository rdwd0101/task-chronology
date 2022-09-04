#include "worklogDBManager.h"

chronology::managers::WorklogDBManager::WorklogDBManager(
    std::shared_ptr<chronology::providers::IDatabaseProvider> dbProvider)
{
    m_dbProvider = dbProvider;
}

void chronology::managers::WorklogDBManager::Load(const boost::filesystem::path& path)
{
    m_dbProvider->Load(path);
}

void chronology::managers::WorklogDBManager::AddRecord(const types::DailyRecord& record)
{
    // TODO: add some checks here also
    m_records.push_back(record);
}

void chronology::managers::WorklogDBManager::RemoveRecord(uuid_t recordId)
{
    std::remove_if(
        m_records.begin(),
        m_records.end(),
        [recordId](const types::DailyRecord& record) { return record.id == recordId; }
    );
}