#include "WorklogDatabaseProviderYaml.h"

void chronology::providers::WorklogDatabaseProviderYaml::AddRecord(const types::DailyRecord& record)
{
    // TODO: add some checks here also
    //m_records.push_back(record);
}

void chronology::providers::WorklogDatabaseProviderYaml::RemoveRecord(uuid_t recordId)
{
    /*
    std::remove_if(
        m_records.begin(),
        m_records.end(),
        [recordId](const types::DailyRecord& record) { return record.id == recordId; }
    );
    */
}