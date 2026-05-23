#pragma once
#include <chrono>
#include <string>

namespace chronology
{
    namespace types
    {
        struct DailyRecord
        {
            std::string uuid;
            //uuid_t task_id;
            std::string task_name;
            std::time_t date;
            double hours;
            std::string description;
        };
    }
}