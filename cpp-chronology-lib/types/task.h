#pragma once
#include <uuid/uuid.h>
#include <string>
#include <chrono>

namespace chronology
{
    namespace types
    {
        struct Task
        {
            uuid_t id;
            std::chrono::system_clock::time_point started;
            std::string name;
        };
    }
}