/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <initializer_list>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace algorithm
  {
    /* Trims all starting vals until the first non-val. */
    template <typename It, typename V>
    It trim_left(It const begin, It const end, V const &vals)
    {
      bool done{};
      return std::remove_if(begin, end, [&](auto const &e)
      {
        return !done &&
          !(done = !(std::find(std::begin(vals), std::end(vals), e)
                   != std::end(vals)));
      });
    }
    template <typename It, typename V>
    It trim_left(It const begin, It const end,
                 std::initializer_list<V> const &vals)
    { return trim_left<It, std::initializer_list<V>>(begin, end, vals); }

    /* Trims all trailing vals. */
    template <typename It, typename V>
    It trim_right(It const begin, It const end, V const &vals)
    {
      It it{ std::next(end, -1) };
      while(std::find(std::begin(vals), std::end(vals), *it) != std::end(vals)
            && it != begin)
      { --it; }
      return it == begin ? end : std::next(it);
    }
    template <typename It, typename V>
    It trim_right(It const begin, It const end,
                  std::initializer_list<V> const &vals)
    { return trim_right<It, std::initializer_list<V>>(begin, end, vals); }

    /* Trims all trailing and leading vals. */
    template <typename It, typename V>
    It trim(It const begin, It const end, V const &vals)
    { return trim_right(begin, trim_left(begin, end, vals), vals); }
    template <typename It, typename V>
    It trim(It const begin, It const end,
            std::initializer_list<V> const &vals)
    { return trim<It, std::initializer_list<V>>(begin, end, vals); }
  }
}
