/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/algorithm/consume.hpp>
#include <jtl/iterator/back_insert.hpp>
#include <jtl/iterator/stream_delim.hpp>

#include <iterator>
#include <vector>
#include <sstream>

namespace jtl
{
  struct consume_test{};
  using consume_group = jest::group<consume_test>;
  static consume_group const consume_obj{ "consume" };
}

namespace jest
{
  template <> template <>
  void jtl::consume_group::test<0>() /* vector -> vector */
  {
    std::vector<int> in{ 0, 1, 2, 3, 4, 5 };
    std::vector<std::vector<int>> out(3);
    jtl::algorithm::consume<2>(std::begin(in), std::end(in),
                               std::begin(out));
    for(int i{}; i < 3; ++i)
    {
      expect_equal(out[i].size(), 2ul);
      expect_equal(out[i][0], i * 2);
      expect_equal(out[i][1], (i * 2) + 1);
    }
  }

  template <> template <>
  void jtl::consume_group::test<1>() /* vector -> vector (push_back) */
  {
    std::vector<int> in{ 0, 1, 2, 3, 4, 5 };
    std::vector<std::vector<int>> out;
    jtl::algorithm::consume<2>(std::begin(in), std::end(in),
                               jtl::iterator::back_inserter(out));
    for(int i{}; i < 3; ++i)
    {
      expect_equal(out[i].size(), 2ul);
      expect_equal(out[i][0], i * 2);
      expect_equal(out[i][1], (i * 2) + 1);
    }
  }

  template <> template <>
  void jtl::consume_group::test<2>() /* aggregate */
  {
    struct name
    { std::string first, last; };

    std::stringstream ss{ "john|doe|peter|parker" };
    std::vector<name> names;
    jtl::algorithm::consume<2>(jtl::iterator::stream_delim<>{ ss, '|' },
                               jtl::iterator::stream_delim<>{},
                               jtl::iterator::back_inserter(names));
    expect_equal(names[0].first, "john");
    expect_equal(names[0].last, "doe");
    expect_equal(names[1].first, "peter");
    expect_equal(names[1].last, "parker");
  }
}
