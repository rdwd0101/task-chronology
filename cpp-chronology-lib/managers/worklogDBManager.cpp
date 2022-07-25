#include "worklogDBManager.h"

chronology::managers::WorklogDBManager::WorklogDBManager(const boost::filesystem::path& path,
    providers::IDatabaseProvider* dbProvider)
    : m_dbPath(path)
{
    m_dbProvider.reset(dbProvider);
}