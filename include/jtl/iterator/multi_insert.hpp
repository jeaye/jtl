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
    /* Similar to <jtl::iterator::insert>, but inserts ranges at a time.
     *
     * When you want to map a range of ranges to a single output, you
     * can use a multi_insert or <jtl::multi_back_insert> iterator.
     *
     * Example:
     * ```cpp
     * // Each transform call returns a std::string, not the normal char
     * std::string const s{ "data" };
     * std::string out{ "{}" };
     * std::transform(s.begin(), s.end(),
     *                jtl::iterator::multi_inserter(out, std::next(out.begin())),
     * [](char const c)
     * { return "[" + std::string{ c } + "]"; });
     * 
     * // out == "{[d][a][t][a]}"
     * ```
     */
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
