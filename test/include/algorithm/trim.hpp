/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/algorithm/trim.hpp>

namespace jtl
{
  struct trim_test{};
  using trim_group = jest::group<trim_test>;
  static trim_group const trim_obj{ "trim" };
}

namespace jest
{
  template <> template <>
  void jtl::trim_group::test<0>() /* string left */
  {
    std::string s{ "   meow" };
    s.erase(jtl::alg::trim_left(s.begin(), s.end(), " "), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<1>() /* string left */
  {
    std::string s{ "meow" };
    s.erase(jtl::alg::trim_left(s.begin(), s.end(), " "), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<2>() /* multiple string left */
  {
    std::string s{ "\t \tmeow" };
    s.erase(jtl::alg::trim_left(s.begin(), s.end(), " \t\n"), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<3>() /* vector left */
  {
    std::vector<int> v{ 42, 0, 1, 2 };
    v.erase(jtl::alg::trim_left(v.begin(), v.end(), {42}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }

  template <> template <>
  void jtl::trim_group::test<4>() /* vector left */
  {
    std::vector<int> v{ 0, 1, 2 };
    v.erase(jtl::alg::trim_left(v.begin(), v.end(), {42}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }

  template <> template <>
  void jtl::trim_group::test<5>() /* multiple vector left */
  {
    std::vector<int> v{ 7, 8, 0, 1, 2 };
    v.erase(jtl::alg::trim_left(v.begin(), v.end(), {42, 7, 8}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }

  template <> template <>
  void jtl::trim_group::test<6>() /* string right */
  {
    std::string s{ "meow   " };
    s.erase(jtl::alg::trim_right(s.begin(), s.end(), " "), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<7>() /* string right */
  {
    std::string s{ "meow" };
    s.erase(jtl::alg::trim_right(s.begin(), s.end(), " "), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<8>() /* multiple string right */
  {
    std::string s{ "meow\t \t" };
    s.erase(jtl::alg::trim_right(s.begin(), s.end(), " \t\n"), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<9>() /* vector right */
  {
    std::vector<int> v{ 0, 1, 2, 42 };
    v.erase(jtl::alg::trim_right(v.begin(), v.end(), {42}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }

  template <> template <>
  void jtl::trim_group::test<10>() /* vector right */
  {
    std::vector<int> v{ 0, 1, 2 };
    v.erase(jtl::alg::trim_right(v.begin(), v.end(), {42}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }

  template <> template <>
  void jtl::trim_group::test<11>() /* multiple vector right */
  {
    std::vector<int> v{ 0, 1, 2, 8, 7 };
    v.erase(jtl::alg::trim_right(v.begin(), v.end(), {42, 7, 8}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }

  template <> template <>
  void jtl::trim_group::test<12>() /* string */
  {
    std::string s{ "  \t meow\n\t" };
    s.erase(jtl::alg::trim(s.begin(), s.end(), " \t\n"), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<13>() /* string */
  {
    std::string s{ "meow" };
    s.erase(jtl::alg::trim(s.begin(), s.end(), " \t\n"), s.end());
    expect_equal(s, "meow");
  }

  template <> template <>
  void jtl::trim_group::test<14>() /* vector */
  {
    std::vector<int> v{ 42, 0, 1, 2, 8, 7 };
    v.erase(jtl::alg::trim(v.begin(), v.end(), {42, 7, 8}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }

  template <> template <>
  void jtl::trim_group::test<15>() /* vector */
  {
    std::vector<int> v{ 0, 1, 2 };
    v.erase(jtl::alg::trim(v.begin(), v.end(), {42, 7, 8}), v.end());
    expect(std::equal(v.begin(), v.end(), std::vector<int>{ 0, 1, 2 }.begin()));
  }
}
