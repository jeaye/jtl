/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

#include <jtl/namespace.hpp>
#include <jtl/iterator/range/direct.hpp>
#include <jtl/iterator/range/indirect.hpp>
#include <jtl/trait/is_indirect.hpp>

namespace jtl
{
  namespace iterator
  {
    /* Builds an indirect range of [begin, end).
     * See <jtl::iterator::range::indirect>.
     * 
     * Example:
     * ```cpp
     * std::vector<int> const v{ 0, 1, 2, 3 };
     * for(auto const i : jtl::it::make_range(v.begin(), std::next(v.begin(), 2)))
     * { std::cout << i << " "; }
     *
     * // output: 0 1
     * ```
     */
    template <typename Begin, typename End = Begin>
    auto make_range(Begin &&begin, End &&end,
                    std::enable_if_t<trait::is_indirect<Begin>(), bool> = true)
    {
      return range::indirect<Begin, End>
      { std::forward<Begin>(begin), std::forward<End>(end) };
    }

    /* Builds an direct range of [begin, end).
     * See <jtl::iterator::range::direct>.
     * 
     * Example:
     * ```cpp
     * for(auto const i : jtl::it::make_range(0, 10))
     * { std::cout << i << " "; }
     *
     * // output: 0 1 2 3 4 5 6 7 8 9
     * ```
     */
    template <typename Begin, typename End = Begin>
    auto make_range(Begin const &begin, End const &end,
                    std::enable_if_t<!trait::is_indirect<Begin>(), bool> = true)
    { return range::direct<Begin, End>{ begin, end }; }

    /* Shorthand for building a range to cover a whole container. */
    template <typename Container>
    auto make_range(Container &&c)
    { return make_range(std::begin(c), std::end(c)); }
  }
}
