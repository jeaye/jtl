/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace iterator
  {
    template <typename C>
    class multi_insert
      : public std::iterator<std::output_iterator_tag,
                             typename C::value_type>
    {
      public:
        using value_type = typename C::value_type;

        multi_insert() = delete;
        multi_insert(C &c, typename C::iterator const i)
          : container_{ c }
          , it_{ i }
        { }

        template <typename T>
        multi_insert& operator =(T &&c)
        {
          for(auto &&e : c)
          { it_ = std::next(container_.insert(it_,
                            std::forward<decltype(e)>(e))); }
          return *this;
        }

        /* NOP */
        multi_insert& operator *() noexcept
        { return *this; }
        multi_insert& operator ++() noexcept
        { return *this; }
        multi_insert& operator ++(int) noexcept
        { return *this; }

      private:
        C &container_;
        typename C::iterator it_{};
    };

    template <typename C>
    multi_insert<C> multi_inserter(C &c, typename C::iterator const it)
    { return { c, it }; }
  }
}
