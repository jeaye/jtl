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
#include <jtl/algorithm/transfer.hpp>

namespace jtl
{
  namespace algorithm
  {
    namespace detail
    {
      template <policy::transfer P, std::size_t... Ns, typename B_It, typename O_It>
      B_It consume(B_It begin, O_It out,
                   std::integer_sequence<std::size_t, Ns...> const)
      {
        *out = std::move(typename std::iterator_traits<O_It>::value_type
        { (static_cast<void>(Ns), transfer<P>(*begin++))... });
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
     * std::vector<triangle> tris(2);
     * consume<3>(points.begin(), points.end(), tris.begin());
     * 
     * // points has been moved from; use consume_copy to prevent moving
     * // tris == { { 0, 1, 2 }, { 3, 4, 5 } }
     * ```
     * 
     * Transfer will follow the Policy, which defaults to
     * <jtl::algorithm::policy::transfer::move> but may be specified as
     * <jtl::algorithm::policy::transfer::copy>.
     *
     * Note that normal std::insert and std::back_insert iterators are
     * not compatible with <jtl::algorithm::consume>, since their iterator
     * traits are void. Instead, use <jtl::iterator::insert> and
     * <jtl::iterator::back_insert>, which have identical usage.
     */
    template <std::size_t N, policy::transfer Policy = policy::transfer::move,
              typename B_It, typename E_It, typename O_It>
    void consume(B_It begin, E_It const end, O_It out)
    {
      static_assert(N, "invalid consume size");

      auto constexpr seq(std::make_index_sequence<N>{});
      while(begin != end)
      { begin = detail::consume<Policy>(begin, out++, seq); }
    }

    /* Shorthand for specifying a copy policy to <jtl::algorithm::consume>.
     *
     * See <jtl::algorithm::consume>.
     */
    template <std::size_t N, typename B_It, typename E_It, typename O_It>
    void consume_copy(B_It begin, E_It const end, O_It out)
    { return consume<N, policy::transfer::copy>(begin, end, out); }
  }
}
