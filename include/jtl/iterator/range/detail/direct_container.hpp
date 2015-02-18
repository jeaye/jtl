/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <utility>
#include <stdexcept>

#include <jtl/namespace.hpp>
#include <jtl/iterator/range/direct.hpp>

namespace jtl
{
  namespace iterator
  {
    namespace range
    {
      namespace detail
      {
        /* Provides container-like access to a range of direct iterators.
         *
         * Direct iterators are non-pointer values which do not provide
         * operator->; this is determined using <jtl::trait::is_indirect>.
         * 
         * Example direct iterator: int
         */
        template <typename T, typename Begin, typename End = Begin>
        class direct_container
        {
          public:
            using iterator = direct<T, Begin, End>;
            using const_iterator = direct<T, Begin, End>;

            /* TODO: step */
            direct_container() = delete;
            direct_container(Begin const &begin, End const &end)
              : begin_{ begin }
              , end_{ end }
            { }

            iterator begin()
            { return { begin_, end_, begin_ }; }
            const_iterator begin() const
            { return { begin_, end_, begin_ }; }

            iterator end()
            { return { begin_, end_, end_ }; }
            const_iterator end() const
            { return { begin_, end_, end_ }; }

          private:
            Begin begin_;
            End end_;
        };
      }
    }
  }
}
