/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/iterator/range.hpp>

#include <algorithm>

namespace jtl
{
  struct indirect_range_test{};
  using indirect_range_group = jest::group<indirect_range_test>;
  static indirect_range_group const indirect_range_obj{ "indirect_range" };

  struct direct_range_test{};
  using direct_range_group = jest::group<direct_range_test>;
  static direct_range_group const direct_range_obj{ "direct_range" };
}

namespace jest
{
  template <> template <>
  void jtl::indirect_range_group::test<0>() /* Construction */
  {
    jtl::iterator::detail::indirect_range<void*, void*> const r
    { nullptr, nullptr };

    expect_equal(r.begin(), nullptr);
    expect_equal(r.cbegin(), nullptr);
    expect_equal(r.end(), nullptr);
    expect_equal(r.cend(), nullptr);
  }

  template <> template <>
  void jtl::indirect_range_group::test<1>() /* Move construction */
  {
    int *begin{}, *end{};
    jtl::iterator::detail::indirect_range<int*, int*> const r
    { std::move(begin), std::move(end) };

    expect_equal(r.begin(), nullptr);
    expect_equal(r.cbegin(), nullptr);
    expect_equal(r.end(), nullptr);
    expect_equal(r.cend(), nullptr);
  }

  template <> template <>
  void jtl::indirect_range_group::test<2>() /* Algorithms */
  {
    auto const arr{ 0, 1, 2 };

    int should_be{};
    for(auto const &i : jtl::it::make_range(std::begin(arr), std::end(arr)))
    { expect_equal(i, should_be++); }
  }

  template <> template <>
  void jtl::direct_range_group::test<0>() /* Construction */
  {
    jtl::iterator::detail::direct_range<int, int> const r{ 0, 42 };

    expect_equal(*r.begin(), 0);
    expect_equal(*r.cbegin(), 0);
    expect_equal(*r.end(), 42);
    expect_equal(*r.cend(), 42);
  }

  template <> template <>
  void jtl::direct_range_group::test<1>() /* Move construction */
  {
    int begin{}, end{ 42 };
    jtl::iterator::detail::direct_range<int, int> const r
    { std::move(begin), std::move(end) };

    expect_equal(*r.begin(), 0);
    expect_equal(*r.cbegin(), 0);
    expect_equal(*r.end(), 42);
    expect_equal(*r.cend(), 42);
  }

  template <> template <>
  void jtl::direct_range_group::test<2>() /* Algorithms */
  {
    int should_be{};
    for(auto const &i : jtl::it::make_range(0, 3))
    { expect_equal(i, should_be++); }
  }
}
