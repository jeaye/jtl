/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  File: include/iterator/transmute.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

namespace jtl
{
  namespace iterator
  {
    /* Transmutes output of T<E> to T2<E>.
     *
     * The transmute output iterator will allow for outputting
     * into a container different from what the algorithm intended.
     * 
     * Example:
     * ```cpp
     * std::stringstream ss{ "w0|w1|w2" };
     * std::vector<std::vector<char>> out;
     * std::copy(jtl::iterator::stream_delim<>{ ss, '|' },
     *           jtl::iterator::stream_delim<>{},
     *           jtl::iterator::transmute_back_inserter(out));
     * 
     * // would normally expect vector<string>, but transmutation
     * // allows for other [compatible] container types.
     * // out == { { 'w', '0' }, { 'w', '1' }, { 'w', '2' } }
     * ```
     */
    template <typename C, typename It>
    class transmute
      : public std::iterator<std::output_iterator_tag,
          typename std::iterator_traits
          <
            decltype(std::begin(std::declval<C&>()))
          >::value_type>
    {
      public:
        using iterator = decltype(std::begin(std::declval<C&>()));
        using value_type = typename std::iterator_traits<iterator>::value_type;

        transmute() = delete;
        transmute(C &c)
          : container_{ c }
        { }

        template <typename T>
        transmute& operator =(T &&c)
        {
          value_type v;
          std::copy(std::begin(c), std::end(c), It(v));
          container_.emplace_back(std::move(v));
          return *this;
        }

        /* NOP */
        transmute& operator *() noexcept
        { return *this; }
        transmute& operator ++() noexcept
        { return *this; }
        transmute& operator ++(int) noexcept
        { return *this; }

      private:
        C &container_;
    };

    /* Creates a <jtl::iterator::transmute> iterator. */
    template <typename C>
    transmute<C, std::back_insert_iterator<
      typename std::iterator_traits<
        decltype(std::begin(std::declval<C&>()))>::value_type>>
      transmute_back_inserter(C &c)
    { return { c }; }
  }
}
