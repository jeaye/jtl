/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  File: test/include/iterator_test/stream_delim.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/iterator/stream_delim.hpp>
#include <jtl/iterator/multi_back_insert.hpp>

#include <algorithm>

namespace jtl
{
  struct stream_delim_test{};
  using stream_delim_group = jest::group<stream_delim_test>;
  static stream_delim_group const stream_delim_obj{ "stream_delim" };
}

namespace jest
{
  template <> template <>
  void jtl::stream_delim_group::test<0>() /* copy */
  {
    std::stringstream ss{ "0\n1\n2\n3" };
    std::vector<std::string> lines;
    std::copy(jtl::iterator::stream_delim<>{ ss },
              jtl::iterator::stream_delim<>{},
              std::back_inserter(lines));
    expect_equal(lines.size(), 4ul);
    for(std::size_t i{}; i < lines.size(); ++i)
    { expect_equal(lines[i], std::to_string(i)); }
  }

  template <> template <>
  void jtl::stream_delim_group::test<1>() /* delim */
  {
    std::stringstream ss{ "0|1|2|3" };
    std::vector<std::string> lines;
    std::copy(jtl::iterator::stream_delim<>{ ss, '|' },
              jtl::iterator::stream_delim<>{},
              std::back_inserter(lines));
    expect_equal(lines.size(), 4ul);
    for(std::size_t i{}; i < lines.size(); ++i)
    { expect_equal(lines[i], std::to_string(i)); }
  }

  template <> template <>
  void jtl::stream_delim_group::test<2>() /* multi_back_inserter */
  {
    std::stringstream ss{ "greed|sloth|wrath|pride|" };
    std::vector<char> chars;
    std::copy(jtl::iterator::stream_delim<>{ ss, '|' },
              jtl::iterator::stream_delim<>{},
              jtl::iterator::multi_back_inserter(chars));
    auto const str(ss.str());
    expect_equal(chars.size(), str.size() - 4);
    for(std::size_t i{}, diff{}; i < str.size(); ++i)
    {
      if(str[i] == '|')
      { ++diff; }
      else
      { expect_equal(str[i], chars[i - diff]); }
    }
  }

  template <> template <>
  void jtl::stream_delim_group::test<3>() /* transform */
  {
    std::stringstream ss{ "meow0\nmeow1\nmeow2\nmeow3\n" };
    std::vector<std::string> lines;
    std::transform(jtl::iterator::stream_delim<>{ ss },
                   jtl::iterator::stream_delim<>{},
                   std::back_inserter(lines),
                   [](std::string const &s)
                   { return "<" + s + ">"; });
    expect_equal(lines.size(), 4ul);
    for(auto const &e : lines)
    { expect_equal(e.size(), 7ul); }
    for(std::size_t i{}; i < lines.size(); ++i)
    { expect_equal(lines[i], "<meow" + std::to_string(i) + ">"); }
  }

  template <> template <>
  void jtl::stream_delim_group::test<4>() /* postfix */
  {
    std::stringstream ss{ "meow0\nmeow1\nmeow2\nmeow3\n" };
    std::size_t i{};
    for(jtl::iterator::stream_delim<> it{ ss }, end{}; it != end; it++, ++i)
    { expect_equal(it->size(), 5ul); }
    expect_equal(i, 4ul);
  }

  template <> template <>
  void jtl::stream_delim_group::test<5>() /* empty */
  {
    std::stringstream ss;
    std::vector<std::string> lines;
    std::copy(jtl::iterator::stream_delim<>{ ss },
              jtl::iterator::stream_delim<>{},
              std::back_inserter(lines));
    expect_equal(lines.size(), 0ul);
  }

  template <> template <>
  void jtl::stream_delim_group::test<6>() /* just line */
  {
    std::stringstream ss{ "\n" };
    std::vector<std::string> lines;
    std::copy(jtl::iterator::stream_delim<>{ ss },
              jtl::iterator::stream_delim<>{},
              std::back_inserter(lines));
    expect_equal(lines.size(), 1ul);
    expect(lines[0].empty());
  }
}
