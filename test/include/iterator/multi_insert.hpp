/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/iterator/multi_insert.hpp>

#include <algorithm>

namespace jtl
{
  struct multi_insert_test{};
  using multi_insert_group = jest::group<multi_insert_test>;
  static multi_insert_group const multi_insert_obj{ "multi_insert" };
}

namespace jest
{
  template <> template <>
  void jtl::multi_insert_group::test<0>() /* transform string */
  {
    std::string const s{ "testing123" };
    std::string out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::multi_inserter(out, out.begin()),
    [](char const c)
    { return "[" + std::string{ c } + "]"; });
    expect_equal(out, "[t][e][s][t][i][n][g][1][2][3]");
  }

  template <> template <>
  void jtl::multi_insert_group::test<1>() /* transform vector */
  {
    std::string const s{ "testing123" };
    std::string out;
    std::transform(s.begin(), s.end(),
                   jtl::iterator::multi_inserter(out, out.begin()),
    [](char const c) -> std::vector<char>
    { return {'[', c, ']'}; });
    expect_equal(out, "[t][e][s][t][i][n][g][1][2][3]");
  }

  template <> template <>
  void jtl::multi_insert_group::test<2>()
  {
    std::vector<std::vector<char>> const v{ { '1', '2' }, { '3', '4' } };
    std::string out;
    std::copy(v.begin(), v.end(),
              jtl::iterator::multi_inserter(out, out.begin()));
    expect_equal(out, "1234");
  }

  template <> template <>
  void jtl::multi_insert_group::test<3>() /* copy */
  {
    std::vector<std::vector<char>> const v{ { '1', '2' }, { '3', '4' } };
    std::string out{ "{}" };
    std::copy(v.begin(), v.end(),
              jtl::iterator::multi_inserter(out, std::next(out.begin())));
    expect_equal(out, "{1234}");
  }
}
