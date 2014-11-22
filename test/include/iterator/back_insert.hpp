/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/iterator/back_insert.hpp>

#include <algorithm>

namespace jtl
{
  struct back_insert_test{};
  using back_insert_group = jest::group<back_insert_test>;
  static back_insert_group const back_insert_obj{ "back_insert" };
}

namespace jest
{
  template <> template <>
  void jtl::back_insert_group::test<0>() /* transform string */
  {
    std::string const s{ "testing123" };
    std::string out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::back_inserter(out),
                   [](char const c)
                   { return std::toupper(c); });
    expect_equal(out, "TESTING123");
  }

  template <> template <>
  void jtl::back_insert_group::test<1>() /* transform vector */
  {
    std::string const s{ "testing123" };
    std::vector<char> out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::back_inserter(out),
                   [](char const c)
                   { return std::toupper(c); });
    expect_equal(std::string{out.data(), out.size()}, "TESTING123");
  }

  template <> template <>
  void jtl::back_insert_group::test<2>() /* vector -> vector */
  {
    std::vector<std::string> const v{ "2", "3", "4" };
    std::vector<std::string> out{ "0", "1" };
    std::copy(v.begin(), v.end(),
              jtl::iterator::back_inserter(out));
    expect_equal(out.size(), 5ul);
    for(std::size_t i{}; i < 5; ++i)
    { expect_equal(out[i], std::to_string(i)); }
  }
}
