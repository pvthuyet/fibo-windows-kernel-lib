#pragma once
#include "ke_define.h"

namespace fibo::kernel::Algorithm
{
    template<class T>
    constexpr const T& max(const T& a, const T& b) KE_NOEXCEPT
    {
        return (a < b) ? b : a;
    }

    template<class T>
    constexpr const T& min(const T& a, const T& b) KE_NOEXCEPT
    {
        return (b < a) ? b : a;
    }
}