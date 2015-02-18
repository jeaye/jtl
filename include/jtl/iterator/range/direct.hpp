/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <utility>
#include <stdexcept>

namespace jtl
{
  namespace iterator
  {
    namespace range
    {
      template <typename T, typename Begin, typename End = Begin>
      class direct
      {
        public:
          direct() = delete;
          direct(Begin const &begin, End const &end)
            : begin_{ begin }
            , end_{ end }
            , current_{ begin_ }
          { }
          direct(Begin const &begin, End const &end, T const current)
            : begin_{ begin }
            , end_{ end }
            , current_{ current }
          { }

          T& operator *()
          { return current_; }
          T const& operator *() const
          { return current_; }

          T* operator ->()
          { return &current_; }
          T const* operator ->() const
          { return &current_; }

          direct& operator ++()
          {
            if(current_ == end_)
            { throw std::range_error{ "beyond-end iterator" }; }
            ++current_;
            return *this;
          }
          direct& operator ++(int const) const
          {
            auto const copy(*this);
            return ++copy;
          }

          template <typename B, typename E>
          friend bool operator ==(direct<B, E> const &lhs,
                                  direct<B, E> const &rhs);
          template <typename B, typename E>
          friend bool operator !=(direct<B, E> const &lhs,
                                  direct<B, E> const &rhs);

        private:
          Begin begin_;
          End end_;
          T current_;
      };

      template <typename B, typename E = B>
      bool operator ==(direct<B, E> const &lhs, direct<B, E> const &rhs)
      { return lhs.current_ == rhs.current_; }
      template <typename B, typename E = B>
      bool operator !=(direct<B, E> const &lhs, direct<B, E> const &rhs)
      { return lhs.current_ != rhs.current_; }
    }
  }
}
