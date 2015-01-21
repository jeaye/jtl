/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>

#include <jtl/namespace.hpp>
#include <jtl/trait/is_indirect.hpp>

namespace jtl
{
  namespace iterator
  {
    namespace detail
    {
      template <typename Begin, typename End = Begin>
      class indirect_range
      {
        public:
          indirect_range() = delete;
          indirect_range(Begin const &begin, End const &end)
            : begin_{ begin }
            , end_{ end }
          { }
          indirect_range(Begin &&begin, End &&end)
            : begin_{ std::move(begin) }
            , end_{ std::move(end) }
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

      template <typename Begin, typename End = Begin>
      class direct_range
      {
        public:
          direct_range() = delete;
          direct_range(Begin const &begin, End const &end)
            : begin_{ begin }
            , end_{ end }
          { }
          direct_range(Begin &&begin, End &&end)
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

    template <typename Begin, typename End = Begin>
    auto make_range(Begin &&begin, End &&end,
                    std::enable_if_t<trait::is_indirect<Begin>(), bool> = true)
    {
      return detail::indirect_range<Begin, End>
      { std::forward<Begin>(begin), std::forward<End>(end) };
    }

    template <typename Begin, typename End = Begin>
    auto make_range(Begin &&begin, End &&end,
                    std::enable_if_t<!trait::is_indirect<Begin>(), bool> = true)
    {
      return detail::direct_range<Begin, End>
      { std::forward<Begin>(begin), std::forward<End>(end) };
    }

    template <typename Container>
    auto make_range(Container &&c)
    { return make_range(std::begin(c), std::end(c)); }
  }
}
