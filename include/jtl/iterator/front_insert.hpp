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
    /* A drop-in replacement for std::front_insert_iterator.
     * 
     * The insert iterators in the stdlib are flawed in that
     * their iterator_traits use only void types. Until this
     * is resolved, such iterators will be in jtl.
     */
    template <typename C>
    class front_insert
      : public std::iterator<std::output_iterator_tag,
          typename std::iterator_traits
          <
            decltype(std::begin(std::declval<C&>()))
          >::value_type>
    {
      public:
        using iterator = decltype(std::begin(std::declval<C&>()));
        using value_type = typename std::iterator_traits<iterator>::value_type;

        front_insert() = delete;
        front_insert(C &c)
          : container_{ c }
          , it_{ std::begin(c) }
        { }

        template <typename T>
        front_insert& operator =(T &&c)
        {
          it_ = container_.insert(it_, std::forward<T>(c));
          ++it_;
          return *this;
        }

        /* NOP */
        front_insert& operator *() noexcept
        { return *this; }
        front_insert& operator ++() noexcept
        { return *this; }
        front_insert& operator ++(int) noexcept
        { return *this; }

      private:
        C &container_;
        iterator it_{};
    };

    /* A drop-in replacement for std::front_inserter.
     *
     * Compliments <jtl::iterator::front_insert>.
     */
    template <typename C>
    front_insert<C> front_inserter(C &c)
    { return { c }; }
  }
}
