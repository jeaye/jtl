/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <utility>
#include <type_traits>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace trait
  {
    namespace detail
    {
      /* Uses substitution failure to determin operator-> support. */
      template <typename T>
      struct is_indirect
      {
        template <typename TT>
        static auto test(int const) ->
          decltype(std::declval<TT&>().operator->(), std::true_type());

        template <typename TT>
        static auto test(...) -> std::false_type;

        static bool constexpr value{ decltype(test<T>(0))::value };
      };
    }

    /* Determines if <T> supports operator-> */
    template <typename T>
    bool constexpr is_indirect()
    { return std::is_pointer<T>::value || detail::is_indirect<T>::value; }
  }
}
