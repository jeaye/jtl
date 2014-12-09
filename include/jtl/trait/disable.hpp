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
     * char const* name()
     * { static_assert(jtl::trait::disable<T>(), "unsupported type"); }
     * template <>
     * char const* name<int>()
     * { return "int"; }
     * ```
     */
    template <typename... Ts>
    bool constexpr disable()
    { return false; }

    /* Works the same as <jtl::trait::disable>, using a type instead.
     *
     * The value held in this type will unconditionally be false
     * for any type. **Specialization is not permitted.**
     */
    template <typename... Ts>
    struct disable_t
    { static bool constexpr const value{ false }; };

    /* Works the same as <jtl::trait::disable>, but depends on values.
     *
     * This allows disabling based on paramaterized values.
     * for any type or value. **Specialization is not permitted.**
     * 
     * Example:
     * ```cpp
     * template <int N>
     * void dance()
     * { static_assert(jtl::trait::disable_value<int, N>(), "We're closed"); }
     * ```
     */
    template <typename T, T V>
    bool constexpr disable_value()
    { return false; }

    /* Works the same as <jtl::trait::disable_value>, using a type instead.
     *
     * The value held in this type will unconditionally be false
     * for any type or value. **Specialization is not permitted.**
     */
    template <typename T, T V>
    struct disable_value_t
    { static bool constexpr const value{ false }; };

    /* Fails compilation using the type pack in order to display each type.
     *
     * The compiler error will likely include the instantiation of this
     * function, listing each type in the pack. You can search your compiler's
     * output for "jtl::trait::show" which should bring you close.
     */
    template <typename... Ts>
    void constexpr show()
    { static_assert(disable<Ts...>(), "jtl::trait::show"); }
  }
}
