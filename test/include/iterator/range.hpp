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
    jtl::iterator::range::indirect<void*, void*> const r
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
    jtl::iterator::range::indirect<int*, int*> const r
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
  void jtl::direct_range_group::test<0>() /* Container */
  {
    jtl::it::range::detail::direct_container<int, int, int> dc
    { 0, 42 };
    expect_equal(*dc.begin(), 0);
    expect_equal(*dc.end(), 42);

    expect_equal(*(++dc.begin()), 1);
  }

  template <> template <>
  void jtl::direct_range_group::test<1>() /* Range-based for */
  {
    int should_be{};
    for(auto const &i : jtl::it::make_range(0, 3))
    { expect_equal(i, should_be++); }
    expect_equal(should_be, 3);

    for(auto const &i : jtl::it::make_range(should_be, should_be + 5))
    { expect_equal(i, should_be++); }
    expect_equal(should_be, 8);
  }

  template <> template <>
  void jtl::direct_range_group::test<2>() /* Arrays */
  {
    float constexpr arr[]{ 1.11f, 2.22f, 3.33f };
    int index{};
    for(auto const f : jtl::it::make_range(arr))
    { expect_equal(f, arr[index++]); }
  }

  template <> template <>
  void jtl::direct_range_group::test<3>() /* Containers */
  {
    std::vector<float> const vec{ 1.11f, 2.22f, 3.33f };
    int index{};
    for(auto const f : jtl::it::make_range(vec))
    { expect_equal(f, vec[index++]); }
  }
}
