/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <iterator>
#include <stdexcept>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace iterator
  {
    template <typename C = char>
    class stream_delim
      : public std::iterator<std::input_iterator_tag, C>
    {
      public:
        using char_type = C;
        using traits_type = std::char_traits<C>;
        using istream_type = std::basic_istream<C, traits_type>;
        using string_type = std::basic_string<C, traits_type>;

        stream_delim() = default;
        stream_delim(istream_type &stream, char_type const d = '\n')
          : stream_{ &stream }
          , delim_{ d }
          , alive_{ std::getline(*stream_, string_, delim_) }
        { }

        string_type& operator *() noexcept
        { return string_; }
        string_type* operator ->() noexcept
        { return &string_; }

        stream_delim& operator ++() noexcept
        {
          if(!alive_)
          { throw std::out_of_range{ "invalid stream_delim iterator" }; }

          alive_ = std::getline(*stream_, string_, delim_);
          return *this;
        }
        stream_delim operator ++(int) noexcept
        {
          if(!alive_)
          { throw std::out_of_range{ "invalid stream_delim iterator" }; }

          auto const copy(*this);
          ++*this;
          return copy;
        }

        friend bool operator ==(stream_delim const &lhs, stream_delim const &rhs)
        { return lhs.alive_ == rhs.alive_; }
        friend bool operator !=(stream_delim const &lhs, stream_delim const &rhs)
        { return !(lhs == rhs); }

      private:
        istream_type *stream_{};
        string_type string_;
        char_type delim_{ '\n' };
        bool alive_{ false };
    };
  }
}
