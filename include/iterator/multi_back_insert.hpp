/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  File: include/iterator/multi_back_insert.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

namespace jtl
{
  template <typename C>
  class multi_back_insert_iterator
    : public std::iterator<std::output_iterator_tag,
                           typename C::value_type>
  {
    public:
      using value_type = typename C::value_type;

      multi_back_insert_iterator(C &c)
        : container_{ c }
      { }

      template <typename T>
      multi_back_insert_iterator& operator =(T &&c)
      {
        std::copy(std::begin(c), std::end(c), std::back_inserter(container_));
        return *this;
      }

      /* NOP */
      multi_back_insert_iterator& operator *() noexcept
      { return *this; }
      multi_back_insert_iterator& operator ++() noexcept
      { return *this; }
      multi_back_insert_iterator& operator ++(int) noexcept
      { return *this; }

    private:
      C &container_;
  };

  template <typename C>
  multi_back_insert_iterator<C> multi_back_inserter(C &c)
  { return { c }; }
}
