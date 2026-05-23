#pragma once

#include "DatabaseWrapper.h"

#include "../types/dailyrecord.h"

#include <filesystem>

namespace chronology
{
    class WorklogDb
    {
    private:
        bool createTable();

    public:
        WorklogDb();

        void load(const std::filesystem::path& path);

        int getLastIndex();
        
        void add(const types::DailyRecord& item);
        void remove(const std::string& uuid);
        bool get(const std::string& uuid, types::DailyRecord& outItem);

        void updateName(const std::string& uuid, const std::string& newName);
        void updateHours(const std::string& uuid, const double hours);
        void updateDescription(const std::string& uuid, const std::string& newDescription);
        void updateDate(const std::string& uuid, const std::time_t newDate);

        bool requestAllItems();
        bool getItemStep(types::DailyRecord& item);

    private:
        DatabaseWrapper _database;
        bool _is_under_query_execution = false;
    };
}