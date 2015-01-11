/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <jest/jest.hpp>

#include <jtl/algorithm/getline.hpp>

namespace jtl
{
  struct getline_test{};
  using getline_group = jest::group<getline_test>;
  static getline_group const getline_obj{ "getline" };
}

namespace jest
{
  template <> template <>
  void jtl::getline_group::test<0>() /* normal */
  {
    std::stringstream ss{ "one\ntwo|three four" };
    std::string line;

    expect(static_cast<bool>(jtl::alg::getline(ss, line, "\n| ")));
    expect_equal(line, "one");

    expect(static_cast<bool>(jtl::alg::getline(ss, line, "\n| ")));
    expect_equal(line, "two");

    expect(static_cast<bool>(jtl::alg::getline(ss, line, "\n| ")));
    expect_equal(line, "three");

    expect(static_cast<bool>(jtl::alg::getline(ss, line, "\n| ")));
    expect_equal(line, "four");

    expect(!static_cast<bool>(jtl::alg::getline(ss, line, "\n| ")));
    expect_equal(line, "");
    expect(ss.eof());
  }

  template <> template <>
  void jtl::getline_group::test<1>() /* eofbit */
  {
    std::stringstream ss{ "" };
    std::string line;
    jtl::alg::getline(ss, line, "\n");
    expect_equal(line, "");
    expect(ss.eof());
  }

  template <> template <>
  void jtl::getline_group::test<2>() /* failbit after */
  {
    std::stringstream ss{ "nogood" };
    std::string line;
    ss.setstate(ss.failbit);
    jtl::alg::getline(ss, line, "\n");
    expect_equal(line, "");
    expect(ss.fail());
  }

  template <> template <>
  void jtl::getline_group::test<3>() /* failbit before */
  {
    std::stringstream ss{ "nogood" };
    std::string line;
    ss.setstate(ss.failbit);
    jtl::alg::getline(ss, line, "\n");
    expect_equal(line, "");
    expect(ss.fail());
  }

  template <> template <>
  void jtl::getline_group::test<4>() /* max_size */
  try
  {
    std::string line;
    std::string input(line.max_size(), 'x');
    std::stringstream ss{ input };
    jtl::alg::getline(ss, line, "\n");
    expect_equal(line, "");
    expect(ss.fail());
  }
  /* The test machine may not have enough memory for this test. */
  catch(std::bad_alloc const&)
  { std::cerr << "skipping: (insufficient memory)" << std::endl; }

  template <> template <>
  void jtl::getline_group::test<5>() /* default delim */
  {
    std::stringstream ss{ "line0\nline1" };
    std::string line;
    jtl::alg::getline(ss, line);
  }
}
