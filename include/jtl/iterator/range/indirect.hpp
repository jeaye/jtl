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
      /* Provides container-like access to a range of indirect iterators.
       *
       * Indirect iterators are either pointers or values which support
       * operator->; this is determined using <jtl::trait::is_indirect>.
       * 
       * Example indirect iterator: int*, std::string::iterator
       */
      template <typename Begin, typename End = Begin>
      class indirect
      {
        public:
          indirect() = delete;
          indirect(Begin const &begin, End const &end)
            : begin_{ begin }
            , end_{ end }
          { }

          Begin begin()
          { return begin_; }
          Begin const begin() const
          { return begin_; }
          Begin const cbegin() const
          { return begin_; }

          Begin end()
          { return end_; }
          Begin const end() const
          { return end_; }
          Begin const cend() const
          { return end_; }

        private:
          Begin begin_;
          End end_;
      };
    }
  }
}
