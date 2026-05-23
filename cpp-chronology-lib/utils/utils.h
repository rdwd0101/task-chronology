#pragma once
#include <string>
#include <uuid/uuid.h>

namespace chronology
{
    namespace utils
    {
        std::string GenerateUUID();
        std::string UUIDtoStr(const uuid_t uuid);
    }
}