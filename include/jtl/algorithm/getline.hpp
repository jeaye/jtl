/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <initializer_list>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace algorithm
  {
    /* Follows std::getline exactly, but allows multiple delimiters.
     *
     * Delimiters are specified as a generic collection. You can use strings,
     * initializer_lists, etc. All of the same preconditions, postconditions,
     * and invariants are observed as with std::getline. This is used in
     * <jtl::iterator::stream_delim>.
     *
     * Example:
     * ```cpp
     * std::stringstream ss{ "one\ntwo|three four" };
     * std::string nums[4];

     * expect(jtl::alg::getline(ss, nums[0], "\n| "));
     * expect(jtl::alg::getline(ss, nums[1], "\n| "));
     * expect(jtl::alg::getline(ss, nums[2], "\n| "));
     * expect(jtl::alg::getline(ss, nums[3], "\n| "));
     * 
     * // nums == [ "one", "two", "three", "four" ]
     * ```
     */
    template<typename Char, typename Traits, typename Allocator, typename Ds>
    decltype(auto) getline(std::basic_istream<Char, Traits> &is,
                           std::basic_string<Char, Traits, Allocator> &str,
                           Ds const &delims)
    {
      str.clear();
      while(true)
      {
        auto const ch(is.get());
        if(is.eof())
        {
          is.setstate(is.eofbit);
          return is;
        }
        else if(!is)
        {
          is.setstate(is.failbit);
          return is;
        }

        auto const it(std::find_if(std::begin(delims), std::end(delims),
        [&](auto const &c){ return Traits::eq(c, ch); }));

        if(it != std::end(delims)) /* Hit delim. */
        { return is; }
        else if(str.size() == str.max_size())
        {
          is.setstate(is.failbit);
          return is;
        }
        else
        { str.append(1, ch); }
      }
    }

    /* Convenience wrapper for initializer_lists. */
    template<typename Char, typename Traits, typename Allocator, typename D>
    decltype(auto) getline(std::basic_istream<Char, Traits> &is,
                           std::basic_string<Char, Traits, Allocator> &str,
                           std::initializer_list<D> const &delims)
    {
      return getline<Char, Traits, Allocator,
                     std::initializer_list<D>>(is, str, delims);
    }
  }
}
