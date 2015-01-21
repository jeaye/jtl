/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <utility>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace iterator
  {
    namespace range
    {
      /* Provides container-like access to a range of direct iterators.
       *
       * Direct iterators are non-pointer values which do not provide
       * operator->; this is determined using <jtl::trait::is_indirect>.
       * 
       * Example direct iterator: int
       */
      template <typename Begin, typename End = Begin>
      class direct
      {
        public:
          direct() = delete;
          direct(Begin const &begin, End const &end)
            : begin_{ begin }
            , end_{ end }
          { }
          direct(Begin &&begin, End &&end)
            : begin_{ std::move(begin) }
            , end_{ std::move(end) }
          { }

          Begin* begin()
          { return &begin_; }
          Begin const* begin() const
          { return &begin_; }
          Begin const* cbegin() const
          { return &begin_; }

          Begin* end()
          { return &end_; }
          Begin const* end() const
          { return &end_; }
          Begin const* cend() const
          { return &end_; }

        private:
          Begin begin_;
          End end_;
      };
    }
  }
}
