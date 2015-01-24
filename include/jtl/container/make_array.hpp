/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <array>
#include <type_traits>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace container
  {
    /* Builds an std::array, deducing type and arity. */
    template <typename... Ts>
    auto constexpr make_array(Ts &&...ts) ->
      std::array<std::decay_t<std::common_type_t<Ts...>>, sizeof...(Ts)>
    { return { std::forward<Ts>(ts)... }; }
  }
}
