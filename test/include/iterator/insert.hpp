/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/iterator/insert.hpp>

#include <algorithm>

namespace jtl
{
  struct insert_test{};
  using insert_group = jest::group<insert_test>;
  static insert_group const insert_obj{ "insert" };
}

namespace jest
{
  template <> template <>
  void jtl::insert_group::test<0>() /* (begin) transform string */
  {
    std::string const s{ "testing123" };
    std::string out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::inserter(out, out.begin()),
                   [](char const c)
                   { return std::toupper(c); });
    expect_equal(out, "TESTING123");
  }

  template <> template <>
  void jtl::insert_group::test<1>() /* (begin) transform vector */
  {
    std::string const s{ "testing123" };
    std::vector<char> out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::inserter(out, out.begin()),
                   [](char const c)
                   { return std::toupper(c); });
    expect_equal(std::string{out.data(), out.size()}, "TESTING123");
  }

  template <> template <>
  void jtl::insert_group::test<2>() /* (begin) vector -> vector */
  {
    std::vector<std::string> const v{ "0", "1", "2" };
    std::vector<std::string> out{ "3", "4" };
    std::copy(v.begin(), v.end(),
              jtl::iterator::inserter(out, out.begin()));
    expect_equal(out.size(), 5ul);
    for(std::size_t i{}; i < 5; ++i)
    { expect_equal(out[i], std::to_string(i)); }
  }

  template <> template <>
  void jtl::insert_group::test<3>() /* (end) transform string */
  {
    std::string const s{ "testing123" };
    std::string out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::inserter(out, out.end()),
                   [](char const c)
                   { return std::toupper(c); });
    expect_equal(out, "TESTING123");
  }

  template <> template <>
  void jtl::insert_group::test<4>() /* (end) transform vector */
  {
    std::string const s{ "testing123" };
    std::vector<char> out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::inserter(out, out.end()),
                   [](char const c)
                   { return std::toupper(c); });
    expect_equal(std::string{out.data(), out.size()}, "TESTING123");
  }

  template <> template <>
  void jtl::insert_group::test<5>() /* (end) vector -> vector */
  {
    std::vector<std::string> const v{ "2", "3", "4" };
    std::vector<std::string> out{ "0", "1" };
    std::copy(v.begin(), v.end(),
              jtl::iterator::inserter(out, out.end()));
    expect_equal(out.size(), 5ul);
    for(std::size_t i{}; i < 5; ++i)
    { expect_equal(out[i], std::to_string(i)); }
  }
}
