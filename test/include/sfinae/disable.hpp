/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/sfinae/disable.hpp>

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
      if(!jtl::sfinae::disable<void>())
      { throw std::runtime_error{ "this is good" }; }
    });
  }

  template <> template <>
  void jtl::disable_group::test<1>() /* constexpr */
  {
    jtl::constexpr_test<jtl::sfinae::disable<std::string>()> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<2>() /* variadic */
  {
    jtl::constexpr_test<jtl::sfinae::disable<std::string, bool, int>()> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<3>() /* type */
  {
    std::vector<jtl::sfinae::disable_t<int>> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<4>() /* type constexpr */
  {
    jtl::constexpr_test<jtl::sfinae::disable_t<std::string>::value> _;
    static_cast<void>(_);
  }

  template <> template <>
  void jtl::disable_group::test<5>() /* type variadic */
  {
    std::vector<jtl::sfinae::disable_t<int, void, float, std::string>> _;
    static_cast<void>(_);
  }
}
