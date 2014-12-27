/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <algorithm>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace algorithm
  {
    /* Copies one range to another, splitting elements if needed.
     *
     * split and split_if work on containers of containers. For example,
     * a std::vector<std::string>. The <predicate> provided to split_if
     * should return an iterator to the current element's split point. If
     * the element should not be split, the end iterator for the element
     * must be returned.
     * 
     * Example:
     * ```cpp
     * std::vector<std::string> strs{ "1 2", "3 4" };
     * std::vector<std::string> out;
     * jtl::alg::split_if(strs.begin(), strs.end(), std::back_inserter(out),
     *                    [](auto const &s)
     *                    { return std::find(s.begin(), s.end(), ' '); });
     * 
     * // out == { "1", "2", "3", "4" }
     * ```
     */
    template <typename In_It, typename Out_It, typename F>
    void split_if(In_It const begin, In_It const end, Out_It out,
                  F const &predicate)
    {
      std::for_each(begin, end, [&](auto const &elem)
      {
        auto const it(predicate(elem));
        if(it == std::end(elem))
        { *out++ = elem; }
        else
        {
          *out++ = { std::begin(elem), it };
          *out++ = { std::next(it), std::end(elem) };
        }
      });
    }

    /* Operates similar to <jtl::algorithm::split_if> but searches for a value.
     *
     * This is a convenience wrapper for split_if which searches for <val>
     * within each container element.
     * 
     * Example:
     * ```cpp
     * std::vector<std::string> strs{ "1", "2|3", "4" };
     * std::vector<std::string> out;
     * jtl::alg::split(strs.begin(), strs.end(), std::back_inserter(out), '|');
     * 
     * // out == { "1", "2", "3", "4" }
     * ```
     */
    template <typename In_It, typename Out_It, typename V>
    void split(In_It const begin, In_It const end, Out_It out, V const &val)
    {
      return split_if(begin, end, out, [&](auto const &e)
                      { return std::find(std::begin(e), std::end(e), val); });
    }
  }
}
