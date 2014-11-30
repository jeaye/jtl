/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <type_traits>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace algorithm
  {
    namespace detail
    {
      template <std::size_t... Ns, typename B_It, typename O_It>
      B_It consume(B_It begin, O_It out,
                   std::integer_sequence<std::size_t, Ns...> const)
      {
        std::size_t _{}; /* Swallows the pack usage. */
        *out = typename std::iterator_traits<O_It>::value_type
        { (_ += Ns, *begin++)... };
        return begin;
      }
    }

    /* Maps N elements of input to one output.
     *
     * Consumes N elements from the input range to construct one 
     * elements in the output range. Given:
     *
     * ```cpp
     * auto const points{ 0, 1, 2, 3, 4, 5 };
     * std::vector<triangle> output(2);
     * consume<3>(std::begin(input), std::end(input), std::begin(output));
     * ```
     *
     * `output` will be `{ { 0, 1, 2 }, { 3, 4, 5 } }`.
     *
     * Note that normal std::insert and std::back_insert iterators are
     * not compatible with jtl::alg::consume, since their iterator traits are
     * void. Instead, use jtl::it::insert and jtl::it::back_insert, which
     * have an identical interface.
     */
    template <std::size_t N, typename B_It, typename E_It, typename O_It>
    void consume(B_It begin, E_It const end, O_It out)
    {
      static_assert(N, "invalid consume size");

      auto constexpr seq(std::make_index_sequence<N>{});
      while(begin != end)
      { begin = detail::consume(begin, out++, seq); }
    }
  }
}
