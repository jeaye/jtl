/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/container/make_array.hpp>

#include <algorithm>

namespace jtl
{
  struct make_array_test{};
  using make_array_group = jest::group<make_array_test>;
  static make_array_group const make_array_obj{ "make_array" };
}

namespace jest
{
  template <> template <>
  void jtl::make_array_group::test<0>() /* Basic */
  {
    auto constexpr arr(jtl::cont::make_array(1, 2, 3));
    expect(std::is_same<decltype(arr)::value_type, int>::value);
    expect_equal(arr.size(), 3ul);
  }

  template <> template <>
  void jtl::make_array_group::test<1>() /* Common type */
  {
    auto constexpr arr(jtl::cont::make_array(1, 'c', 3));
    expect(std::is_same<decltype(arr)::value_type, int>::value);
    expect_equal(arr.size(), 3ul);
  }

  template <> template <>
  void jtl::make_array_group::test<2>() /* C strings */
  {
    auto constexpr arr(jtl::cont::make_array("1", "2", "34"));
    expect(std::is_same<decltype(arr)::value_type, char const*>::value);
    expect_equal(arr.size(), 3ul);
  }

  template <> template <>
  void jtl::make_array_group::test<3>() /* C++ strings */
  {
    auto arr(jtl::cont::make_array(std::string{ "1" }, "2"));
    expect(std::is_same<decltype(arr)::value_type, std::string>::value);
    expect_equal(arr.size(), 2ul);
  }
}
