/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

namespace jtl
{
  namespace iterator
  {
    template <typename C>
    class back_insert
      : public std::iterator<std::output_iterator_tag,
                             typename C::value_type>
    {
      public:
        using value_type = typename C::value_type;

        back_insert(C &c)
          : container_{ c }
        { }

        template <typename T>
        back_insert& operator =(T &&c)
        {
          container_.push_back(c);
          return *this;
        }

        /* NOP */
        back_insert& operator *() noexcept
        { return *this; }
        back_insert& operator ++() noexcept
        { return *this; }
        back_insert& operator ++(int) noexcept
        { return *this; }

      private:
        C &container_;
    };

    template <typename C>
    back_insert<C> back_inserter(C &c)
    { return { c }; }
  }
}
