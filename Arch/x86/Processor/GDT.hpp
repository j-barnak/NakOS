#pragma once

#include "Array.hpp"
#include "Lib/Array.hpp"
#include "Processor/Descriptor.hpp"
#include <cstddef>
#include <cstdint>

namespace Processor {

// TODO: The base and limit are messed up. Switch them
struct [[gnu::packed]] GDTR
{
    std::uint16_t limit;
    void *base;
};

template<std::uint8_t Size>
class Descriptors
{
  public:
    Descriptors(const GDTR &gdtr);
    void load_descriptor_entry(Node entry, std::ptrdiff_t index);

  private:
    // clang-format off
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
    // clang-format on

    GDTR m_gdtr;
    Lib::Array<Node, 8> *m_gdt;

    void load_gtdr();
};

template<std::uint8_t Size>
Processor::Descriptors<Size>::Descriptors(const Processor::GDTR &gdtr) : m_gdtr { gdtr }
{
    load_gtdr();
    m_gdt = static_cast<Processor::Descriptors<Size>::Node *>(m_gdtr.base);
}

template<std::uint8_t Size>
void Processor::Descriptors<Size>::load_gtdr()
{
    asm volatile(
        "cli;"
        "lgdtl %0;"
        "sti;" ::"m"(m_gdtr));
}

// template<std::uint8_t Size>
// void Processor::Descriptors<Size>::load_descriptor_entry(const Processor::Descriptors<Size> Node &entry, std::ptrdiff_t index)
// {}
template<std::uint8_t Size>
void Descriptors<Size>::load_descriptor_entry(Descriptors<Size>::Node node, std::ptrdiff_t t)
{}


}// namespace Processor
