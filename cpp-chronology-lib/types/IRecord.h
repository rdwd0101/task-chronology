#pragma once
#include <uuid/uuid.h>

namespace chronology
{
    namespace types
    {
        struct IRecord
        {
            uuid_t id;
        };
    }
}
