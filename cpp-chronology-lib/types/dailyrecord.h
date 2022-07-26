#pragma once
#include <chrono>
#include <string>
#include <uuid/uuid.h>

namespace chronology
{
    namespace types
    {
        struct DailyRecord
        {
            uuid_t id;
            //uuid_t task_id;
            std::string task_name;
            std::chrono::system_clock::time_point started;
            float hours;
            std::string description;
        };
    }
}