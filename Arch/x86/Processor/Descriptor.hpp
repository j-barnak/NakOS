#pragma once

#include <cstdint>

namespace Processor {

// NOTE: opted to use #pragma pack (push, 1) because GCC doesn't like mixing
// Section 3.4.5 @ "Segment Descriptors" of the Intel Manual
#pragma pack(push, 8)
struct Node
{
    std::uint16_t segment_limit_low;
    std::uint16_t base_address_low;
    std::uint8_t base_address_mid;
    std::uint8_t type : 4;
    std::uint8_t system : 1;
    std::uint8_t descriptor_privilege_level : 1;
    std::uint8_t present : 1;
    std::uint8_t segment_limit_high : 4;
    std::uint8_t available : 1;
    std::uint8_t d_or_b : 1;
    std::uint8_t granularity : 1;
    std::uint8_t base_address_high;
};
#pragma pack(pop)

}// namespace Processor
