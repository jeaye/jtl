/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <algorithm>
#include <type_traits>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace algorithm
  {
    /* Follows std::transform but allows skipping of items.
     * 
     * The unary function shall be of compatible type:
     *
     * ```cpp
     * std::experimental::optional<T> (auto const &val)
     * ```
     *
     * The returned optional will determine whether or not the
     * value is used. To skip an item, return an empty optional.
     *
     * Example:
     * ```cpp
     * std::vector<int> const v{ 0, 1, 2, 3, 4 };
     * std::vector<std::string> out;
     * jtl::alg::transform_if(v.begin(), v.end(), jtl::it::back_inserter(out),
     *                        [](auto const i)
     *                          -> std::experimental::optional<std::string>
     *                        {
     *                          if(i % 2)
     *                          { return { std::to_string(i) }; }
     *                          else
     *                          { return {}; }
     *                        });
     *                        
     * // out == { "1", "3" }
     * ```
     */
    template <typename I_It, typename O_It, typename Unary_Func>
    O_It transform_if(I_It const begin, I_It const end,
                      O_It out, Unary_Func const &func)
    {
      for(auto it(begin); it != end; ++it)
      {
        auto const res(func(*it));
        if(res)
        { *out++ = *res; }
      }
      return out;
    }

    /* Similar to the unary version; uses two input ranges and a binary function.
     */
    template <typename I_It1, typename O_It, typename I_It2, typename Binary_Func>
    O_It transform_if(I_It1 const begin1, I_It1 const end1, I_It2 const begin2,
                      O_It out, Binary_Func const &func)
    {
      auto it1(begin1);
      auto it2(begin2);
      for(; it1 != end1; ++it1, ++it2)
      {
        auto const res(func(*it1, *it2));
        if(res)
        { *out++ = *res; }
      }
      return out;
    }
  }
}
