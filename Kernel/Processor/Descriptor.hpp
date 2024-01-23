#pragma once

#include <cstdint>
#include <variant>

namespace Processor {

// Section 3.4.5 @ "Segment Descriptors" of the Intel Manual
struct [[gnu::packed]] Descriptor
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

}// namespace Processor
