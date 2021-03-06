/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/trait/disable.hpp>

#include <string>
#include <vector>
#include <stdexcept>

namespace jtl
{
  struct disable_test{};
  using disable_group = jest::group<disable_test>;
  static disable_group const disable_obj{ "disable" };

  template <bool B>
  struct constexpr_test
  { static_assert(!B, "B should always be false; we're disabling"); };
}

namespace jest
{
  template <> template <>
  void jtl::disable_group::test<0>() /* return false */
  {
    expect_exception<std::runtime_error>([]
    {
      if(!jtl::trait::disable<void>())
      { throw std::runtime_error{ "this is good" }; }
    });
  }

  template <> template <>
  void jtl::disable_group::test<1>() /* constexpr */
  {
    jtl::constexpr_test<jtl::trait::disable<std::string>()> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<2>() /* variadic */
  {
    jtl::constexpr_test<jtl::trait::disable<std::string, bool, int>()> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<3>() /* type */
  {
    std::vector<jtl::trait::disable_t<int>> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<4>() /* type constexpr */
  {
    jtl::constexpr_test<jtl::trait::disable_t<std::string>::value> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<5>() /* type variadic */
  {
    std::vector<jtl::trait::disable_t<int, void, float, std::string>> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<6>() /* value */
  {
    jtl::constexpr_test<jtl::trait::disable_value<int, 0>()> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<7>() /* value type */
  {
    jtl::constexpr_test<jtl::trait::disable_value_t<int, 0>::value> _;
    static_cast<void>(_);
  }
}
