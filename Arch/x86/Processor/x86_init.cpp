#include "Processor/Descriptor.hpp"
#include "Processor/GDT.hpp"

auto gdt = Processor::GDT<8> { Processor::GDTR {} };

static void load_desriptors()
{
    auto null_descriptor = Processor::Descriptor {};

    // clang-format off
    auto some_descriptor = Processor::Descriptor {
        .segment_limit_low           = 111,
        .base_address_low            = 0,
        .base_address_mid            = 0,
        .type                        = 0,
        .system                      = 0,
        .descriptor_privilege_level  = 0,
        .present                     = 0,
        .segment_limit_high          = 0,
        .available                   = 0,
        .d_or_b                      = 0,
        .granularity                 = 0,
        .base_address_high           = 222
    };
    // clang-format on

    gdt.push_descriptor_entry(null_descriptor);
    gdt.push_descriptor_entry(some_descriptor);
}

void gdt_init()
{
    load_desriptors();
}
