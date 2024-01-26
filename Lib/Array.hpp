#pragma once

#include <memory>

namespace Lib {

template<typename T, std::size_t N>
struct Array
{
    T __array[N];
    T &operator[](std::ptrdiff_t index);
    Array() = delete;
    T *begin();
    T *end();
    constexpr T *cbegin();
    constexpr T *cend();
};


template<typename T, std::size_t N>
T &Array<T, N>::operator[](std::ptrdiff_t index)
{
    return __array[index];
}

template<typename T, std::size_t N>
T *Array<T, N>::begin()
{
    return &__array[0];
}

template<typename T, std::size_t N>
T *Array<T, N>::end()
{
    return &__array[N];
}

template<typename T, std::size_t N>
constexpr T *Array<T, N>::cbegin()
{
    return &__array[0];
}

template<typename T, std::size_t N>
constexpr T *Array<T, N>::cend()
{
    return &__array[N];
}

}// namespace Lib
