/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  File: test/include/iterator_test/transmute_back_insert.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/iterator/stream_delim.hpp>
#include <jtl/iterator/multi_back_insert.hpp>
#include <jtl/iterator/transmute_back_insert.hpp>

#include <algorithm>

namespace jtl
{
  struct transmute_back_insert_test{};
  using transmute_back_insert_group = jest::group<transmute_back_insert_test>;
  static transmute_back_insert_group const transmute_back_insert_obj
  { "transmute_back_insert" };
}

namespace jest
{
  template <> template <>
  void jtl::transmute_back_insert_group::test<0>() /* explicit */
  {
    std::stringstream ss{ "word0|word1|word2" };
    std::vector<std::vector<char>> out;
    std::transform(jtl::iterator::stream_delim<>{ ss, '|' },
                   jtl::iterator::stream_delim<>{},
                   jtl::iterator::transmute_back_insert<
                     std::vector<std::vector<char>>,
                     std::back_insert_iterator<std::vector<char>>>{ out },
    [](std::string const &s)
    { return s; });
    expect_equal(out.size(), 3ul);
    for(std::size_t i{}; i < out.size(); ++i)
    { expect_equal(std::string(out[i].data(), out[i].size()),
                   "word" + std::to_string(i)); }
  }

  template <> template <>
  void jtl::transmute_back_insert_group::test<1>() /* helper */
  {
    std::stringstream ss{ "word0|word1|word2" };
    std::vector<std::vector<char>> out;
    std::transform(jtl::iterator::stream_delim<>{ ss, '|' },
                   jtl::iterator::stream_delim<>{},
                   jtl::iterator::transmute_back_inserter(out),
    [](std::string const &s)
    { return s; });
    expect_equal(out.size(), 3ul);
    for(std::size_t i{}; i < out.size(); ++i)
    { expect_equal(std::string(out[i].data(), out[i].size()),
                   "word" + std::to_string(i)); }
  }

  template <> template <>
  void jtl::transmute_back_insert_group::test<2>() /* copy */
  {
    std::stringstream ss{ "word0|word1|word2" };
    std::vector<std::vector<char>> out;
    std::copy(jtl::iterator::stream_delim<>{ ss, '|' },
              jtl::iterator::stream_delim<>{},
              jtl::iterator::transmute_back_inserter(out));
    expect_equal(out.size(), 3ul);
    for(std::size_t i{}; i < out.size(); ++i)
    { expect_equal(std::string(out[i].data(), out[i].size()),
                   "word" + std::to_string(i)); }
  }
}
