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
    /* A drop-in replacement for std::back_insert_iterator.
     * 
     * The insert iterators in the stdlib are flawed in that
     * their iterator_traits use only void types. Until this
     * is resolved, such iterators will be in jtl.
     */
    template <typename C>
    class back_insert
      : public std::iterator<std::output_iterator_tag,
          typename std::iterator_traits
          <
            decltype(std::begin(std::declval<C&>()))
          >::value_type>
    {
      public:
        using iterator = decltype(std::begin(std::declval<C&>()));
        using value_type = typename std::iterator_traits<iterator>::value_type;

        back_insert() = delete;
        back_insert(C &c)
          : container_{ c }
        { }

        template <typename T>
        back_insert& operator =(T &&c)
        {
          container_.push_back(std::forward<T>(c));
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

    /* A drop-in replacement for std::back_inserter.
     *
     * Compliments <jtl::iterator::back_insert>.
     */
    template <typename C>
    back_insert<C> back_inserter(C &c)
    { return { c }; }
  }
}
