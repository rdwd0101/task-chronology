#include "WorklogDb.h"
#include <cstdio>

chronology::WorklogDb::WorklogDb()
{
}

void chronology::WorklogDb::load(const std::filesystem::path& path)
{
    _database.open(path);

    if (!createTable())
    {
        throw new std::runtime_error("Cannot create table: " + _database.getLastErrorMsg());
    }
}

bool chronology::WorklogDb::createTable()
{
    _database.prepareQuery("CREATE TABLE IF NOT EXISTS WORKLOG(UUID TEXT NOT NULL PRIMARY KEY, NAME TEXT NOT NULL, DATE INTEGER NOT NULL, HOURS REAL NOT NULL, DESCRIPTION TEXT NOT NULL);");

    return _database.executeQuery();
}

void chronology::WorklogDb::add(
        const types::DailyRecord& item
        )
{
    _database.beginTransaction();

    _database.prepareQuery("INSERT INTO WORKLOG VALUES(?, ?, ?, ?, ?);");
    _database.bindToQuery(0, item.uuid);
    _database.bindToQuery(1, item.task_name);
    _database.bindToQueryInt64(2, item.date);
    _database.bindToQueryReal(3, item.hours);
    _database.bindToQuery(4, item.description);

    if (!_database.executeQuery())
    {
        _database.rollbackTransaction();
        throw new std::runtime_error("Cannot execute query: " + _database.getLastErrorMsg());
    }

    _database.commitTransaction();
}

void chronology::WorklogDb::remove(
        const std::string& uuid
        )
{
    _database.beginTransaction();

    _database.prepareQuery("DELETE FROM WORKLOG WHERE UUID=?;");
    _database.bindToQuery(0, uuid);

    if (!_database.executeQuery())
    {
        _database.rollbackTransaction();
        fprintf(stderr, "WorklogDb remove error: %s\n", _database.getLastErrorMsg().c_str());
        return;
    }

    _database.commitTransaction();
}

bool chronology::WorklogDb::get(
        const std::string& uuid,
        types::DailyRecord& outItem
        )
{
    _database.prepareQuery("SELECT NAME, DATE, HOURS, DESCRIPTION FROM WORKLOG WHERE UUID=?;");
    _database.bindToQuery(0, uuid);

    _database.executeQuery();

    if (!_database.getQueryResult(0, outItem.task_name) ||
        !_database.getQueryResultInt64(1, outItem.date) ||
        !_database.getQueryResultReal(2, outItem.hours) ||
        !_database.getQueryResult(3, outItem.description))
    {
        return false;
    }

    return true;
}

void chronology::WorklogDb::updateName(const std::string& uuid, const std::string& newName)
{
    _database.beginTransaction();

    _database.prepareQuery("UPDATE WORKLOG SET NAME=? WHERE UUID=?;");
    _database.bindToQuery(0, newName);
    _database.bindToQuery(1, uuid);
    if (!_database.executeQuery())
    {
        _database.rollbackTransaction();
        throw new std::runtime_error("Cannot execute query: " + _database.getLastErrorMsg());
    }

    _database.commitTransaction();
}

void chronology::WorklogDb::updateHours(const std::string& uuid, const double hours)
{
    _database.beginTransaction();

    _database.prepareQuery("UPDATE WORKLOG SET HOURS=? WHERE UUID=?;");
    _database.bindToQueryReal(0, hours);
    _database.bindToQuery(1, uuid);
    if (!_database.executeQuery())
    {
        _database.rollbackTransaction();
        throw new std::runtime_error("Cannot execute query: " + _database.getLastErrorMsg());
    }

    _database.commitTransaction();
}

void chronology::WorklogDb::updateDescription(const std::string& uuid, const std::string& newDescription)
{
    _database.beginTransaction();

    _database.prepareQuery("UPDATE WORKLOG SET DESCRIPTION=? WHERE UUID=?;");
    _database.bindToQuery(0, newDescription);
    _database.bindToQuery(1, uuid);
    if (!_database.executeQuery())
    {
        _database.rollbackTransaction();
        throw new std::runtime_error("Cannot execute query: " + _database.getLastErrorMsg());
    }

    _database.commitTransaction();
}

void chronology::WorklogDb::updateDate(const std::string& uuid, const std::time_t newDate)
{
    _database.beginTransaction();

    _database.prepareQuery("UPDATE WORKLOG SET DATE=? WHERE UUID=?;");
    _database.bindToQueryInt64(0, newDate);
    _database.bindToQuery(1, uuid);
    if (!_database.executeQuery())
    {
        _database.rollbackTransaction();
        throw new std::runtime_error("Cannot execute query: " + _database.getLastErrorMsg());
    }

    _database.commitTransaction();
}


bool chronology::WorklogDb::requestAllItems()
{
    if (!_database.prepareQuery("SELECT * FROM WORKLOG ORDER BY ROWID;"))
    {
        throw new std::runtime_error("Cannot execute query: " + _database.getLastErrorMsg());
    }

    _is_under_query_execution = true;
    return true;
}

bool chronology::WorklogDb::getItemStep(types::DailyRecord& item)
{
    _database.executeQuery();

    bool uuidStat = _database.getQueryResult(0, item.uuid);
    bool nameStat = _database.getQueryResult(1, item.task_name);
    bool dateStat = _database.getQueryResultInt64(2, item.date);
    bool hoursStat = _database.getQueryResultReal(3, item.hours);
    bool descStat = _database.getQueryResult(4, item.description);

    bool result = uuidStat && nameStat && dateStat && hoursStat && descStat;
    if (!result)
    {
        _is_under_query_execution = false;
        return result;
    }
    
    return result;
}
