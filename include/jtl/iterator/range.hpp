/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>
#include <type_traits>

#include <jtl/namespace.hpp>
#include <jtl/iterator/range/detail/direct_container.hpp>
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
      return range::indirect<std::decay_t<Begin>, std::decay_t<End>>
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
    {
      return range::detail::direct_container
      <std::decay_t<Begin>, std::decay_t<End>>
      { begin, end };
    }

    /* Shorthand for building a range to cover a whole container. */
    template <typename C>
    auto make_range(C const &c, decltype(std::begin(c)) = {})
    { return make_range(std::begin(c), std::end(c)); }

    /* Shorthand for building a range of [V{}, v). */
    template <typename V>
    std::enable_if_t
    <
      std::is_integral
      <
        std::decay_t<V>
      >::value,
      range::detail::direct_container<V, V>
    > make_range(V const &v)
    { return range::detail::direct_container<V, V>{ V{}, v }; }
  }
}
