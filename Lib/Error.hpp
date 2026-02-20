#pragma once

namespace {

// Purposely de-reference a nullptr to induce a crash
inline void crash()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wundef"
    int *_uniqe_crash_ptr = nullptr;
    *_uniqe_crash_ptr;
#pragma GCC diagnostic pop
}

#define TODO()   \
    do {         \
        crash(); \
    } while (0)

} // namespace
