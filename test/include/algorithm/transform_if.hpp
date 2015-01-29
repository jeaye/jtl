/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/algorithm/transform_if.hpp>
#include <jtl/iterator/back_insert.hpp>

#include <experimental/optional>
#include <vector>

namespace jtl
{
  struct transform_if_test{};
  using transform_if_group = jest::group<transform_if_test>;
  static transform_if_group const transform_if_obj{ "transform_if" };
}

namespace jest
{
  template <> template <>
  void jtl::transform_if_group::test<0>() /* unary */
  {
    std::vector<int> v{ 0, 1, 2, 3, 4 };
    std::vector<std::string> out;
    jtl::alg::transform_if(v.begin(), v.end(), jtl::it::back_inserter(out),
                           [](auto const i)
                             -> std::experimental::optional<std::string>
                           {
                             if(i % 2)
                             { return { std::to_string(i) }; }
                             else
                             { return {}; }
                           });
    expect_equal(out.size(), 2ul);
    expect_equal(out[0], "1");
    expect_equal(out[1], "3");
  }

  template <> template <>
  void jtl::transform_if_group::test<1>() /* binary */
  {
    std::vector<int> v1{ 0, 1, 2, 3, 4 };
    std::vector<int> v2{ 1, 2, 3, 4, 5 };
    std::vector<std::string> out;
    jtl::alg::transform_if(v1.begin(), v1.end(), v2.begin(), 
                           jtl::it::back_inserter(out),
                           [](auto const i1, auto const i2)
                             -> std::experimental::optional<std::string>
                           {
                             if((i1 + i2) % 2)
                             { return { std::to_string(i1 + i2) }; }
                             else
                             { return {}; }
                           });
    expect_equal(out.size(), 5ul);
    for(int i{ 1 }; i < 10; i += 2)
    { expect_equal(out[(i - 1) / 2], std::to_string(i)); }
  }
}
