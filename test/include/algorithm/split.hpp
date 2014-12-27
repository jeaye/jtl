/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/algorithm/split.hpp>

namespace jtl
{
  struct split_test{};
  using split_group = jest::group<split_test>;
  static split_group const split_obj{ "split" };
}

namespace jest
{
  template <> template <>
  void jtl::split_group::test<0>() /* split_if */
  {
    std::vector<std::string> strs{ "1 2", "3 4" };
    std::vector<std::string> out;
    jtl::alg::split_if(strs.begin(), strs.end(), std::back_inserter(out),
                       [](auto const &s)
                       { return std::find(s.begin(), s.end(), ' '); });
    expect(std::equal(out.begin(), out.end(),
           std::vector<std::string>{ "1", "2", "3", "4" }.begin()));
  }

  template <> template <>
  void jtl::split_group::test<1>() /* no split_if */
  {
    std::vector<std::string> strs{ "12", "34" };
    std::vector<std::string> out;
    jtl::alg::split_if(strs.begin(), strs.end(), std::back_inserter(out),
                       [](auto const &s)
                       { return std::find(s.begin(), s.end(), ' '); });
    expect(std::equal(out.begin(), out.end(),
           std::vector<std::string>{ "12", "34" }.begin()));
  }

  template <> template <>
  void jtl::split_group::test<2>() /* split_if | delim */
  {
    std::vector<std::string> strs{ "1", "2|3", "4" };
    std::vector<std::string> out;
    jtl::alg::split_if(strs.begin(), strs.end(), std::back_inserter(out),
                       [](auto const &s)
                       { return std::find(s.begin(), s.end(), '|'); });
    expect(std::equal(out.begin(), out.end(),
           std::vector<std::string>{ "1", "2", "3", "4" }.begin()));
  }

  template <> template <>
  void jtl::split_group::test<3>() /* split */
  {
    std::vector<std::string> strs{ "1", "2|3", "4" };
    std::vector<std::string> out;
    jtl::alg::split(strs.begin(), strs.end(), std::back_inserter(out), '|');
    expect(std::equal(out.begin(), out.end(),
           std::vector<std::string>{ "1", "2", "3", "4" }.begin()));
  }
}
