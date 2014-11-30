/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace trait
  {
    /* Unconditionally returns false, consuming all types.
     *
     * Use this when you need to defer an assertion to
     * instantiation time, since the value is dependent
     * on the type(s). **Specialization is not permitted.**
     *
     * Example:
     * ```cpp
     * template <typename T>
     * std::string name()
     * { static_assert(jtl::trait::disable<T>(), "unsupported type"); }
     * template <>
     * std::string name<int>()
     * { return "int"; }
     * ```
     */
    template <typename... Ts>
    bool constexpr disable()
    { return false; }

    /* Works the same as jtl::trait::disable, using a type instead.
     *
     * The value held in this type will unconditionally be false
     * for any type. **Specialization is not permitted.**
     */
    template <typename... Ts>
    struct disable_t
    { static bool constexpr const value{ false }; };

    template <typename... Ts>
    constexpr void show()
    { static_assert(disable<Ts...>(), "jtl::trait::show"); }
  }
}
