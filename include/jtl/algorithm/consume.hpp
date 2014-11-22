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
