/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  File: include/iterator/multi_insert.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

namespace jtl
{
  template <typename C>
  class multi_insert_iterator
    : public std::iterator<std::output_iterator_tag,
                           typename C::value_type>
  {
    public:
      using value_type = typename C::value_type;

      multi_insert_iterator(C &c, typename C::iterator const i)
        : container_{ c }
        , it_{ i }
      { }

      template <typename T>
      multi_insert_iterator& operator =(T &&c)
      {
        for(auto &&e : c)
        { it_ = std::next(container_.insert(it_, std::forward<decltype(e)>(e))); }
        return *this;
      }

      /* NOP */
      multi_insert_iterator& operator *() noexcept
      { return *this; }
      multi_insert_iterator& operator ++() noexcept
      { return *this; }
      multi_insert_iterator& operator ++(int) noexcept
      { return *this; }

    private:
      C &container_;
      typename C::iterator it_{};
  };

  template <typename C>
  multi_insert_iterator<C> multi_inserter(C &c, typename C::iterator const it)
  { return { c, it }; }
}
