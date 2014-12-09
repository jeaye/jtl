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

  struct tracked_move
  {
    tracked_move() = default;
    tracked_move(tracked_move &&)
    { ++count; }

    tracked_move& operator =(tracked_move &&)
    {
      ++count;
      return *this;
    }

    static std::size_t count;
  };
  std::size_t tracked_move::count{};

  struct tracked_copy
  {
    tracked_copy() = default;
    tracked_copy(tracked_copy const&)
    { ++count; }

    tracked_copy& operator =(tracked_copy const&)
    {
      ++count;
      return *this;
    }

    static std::size_t count;
  };
  std::size_t tracked_copy::count{};

  template <typename T>
  struct tracked_eater
  {
    tracked_eater() = default;
    tracked_eater(tracked_eater const&) = default;
    tracked_eater(tracked_eater &&) = default;

    template <typename T1, typename T2>
    tracked_eater(T1 &&t1, T2 &&t2)
      : first{ std::forward<T1>(t1) }
      , second{ std::forward<T2>(t2) }
    { }

    tracked_eater& operator =(tracked_eater const&) = default;
    tracked_eater& operator =(tracked_eater &&) = default;

    T first, second;
  };
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

  template <> template <>
  void jtl::consume_group::test<3>() /* move */
  {
    std::vector<jtl::tracked_move> in(6);
    std::vector<jtl::tracked_eater<jtl::tracked_move>> out(3);
    jtl::algorithm::consume<2>(std::begin(in), std::end(in), std::begin(out));

    /* First moved into their new home, then that home is moved into the vector. */
    expect_equal(jtl::tracked_move::count, 18ul);
  }

  template <> template <>
  void jtl::consume_group::test<4>() /* copy */
  {
    std::vector<jtl::tracked_copy> in(6);
    std::vector<jtl::tracked_eater<jtl::tracked_copy>> out(3);
    jtl::algorithm::consume_copy<2>(std::begin(in), std::end(in), std::begin(out));

    /* First copied into their new home, then that home is copied into the vector. */
    expect_equal(jtl::tracked_copy::count, 18ul);
  }
}
