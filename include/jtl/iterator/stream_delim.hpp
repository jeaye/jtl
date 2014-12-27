/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <algorithm>
#include <string>
#include <iterator>
#include <stdexcept>
#include <initializer_list>

#include <jtl/namespace.hpp>
#include <jtl/algorithm/getline.hpp>

namespace jtl
{
  namespace iterator
  {
    /* Provides iteration over input streams given a delimiter.
     *
     * Similar to std::getline, stream_delim allows one to iterate
     * through an input stream using a delimiter, which defaults to
     * '\n'.
     * 
     * The stream_delim template is parameterized on the char type;
     * it should be compatible with any input stream using the same char
     * type.
     *
     * A default-constructed stream_delim iterator represents the
     * end of the range.
     * 
     * Example:
     * ```cpp
     * std::stringstream ss{ "0\n1\n2\n3" };
     * std::vector<std::string> lines;
     * std::copy(jtl::iterator::stream_delim<>{ ss },
     *           jtl::iterator::stream_delim<>{},
     *           std::back_inserter(lines));
     * ```
     */
    template <typename C = char>
    class stream_delim
      : public std::iterator<std::input_iterator_tag, C>
    {
      public:
        using char_type = C;
        using traits_type = std::char_traits<C>;
        using istream_type = std::basic_istream<C, traits_type>;
        using string_type = std::basic_string<C, traits_type>;
        using delims_type = string_type;

        stream_delim() = default;
        
        /* Constructs a new iterator using the input stream and delimiter.
         *
         * The delimiter defaults to '\n' but can be any valid value
         * of the char type.
         */
        stream_delim(istream_type &stream, char_type const d = '\n')
          : stream_{ &stream }
          , delims_{ d }
          , alive_
            { static_cast<bool>(jtl::alg::getline(*stream_, string_, delims_)) }
        { }

        /* Constructs a new iterator using the input stream and multiple delimiters.
         *
         * The delimiter defaults to "\n" but can be any valid container
         * compatible with the char type (such as a std::vector<char>).
         */
        template <typename Ds = char const[2]>
        stream_delim(istream_type &stream, Ds const &delims = "\n")
          : stream_{ &stream }
        {
          std::copy(std::begin(delims), std::end(delims),
                    std::back_inserter(delims_));
          alive_ = jtl::alg::getline(*stream_, string_, delims_);
        }

        string_type& operator *() noexcept
        { return string_; }
        string_type* operator ->() noexcept
        { return &string_; }

        stream_delim& operator ++() noexcept
        {
          if(!alive_)
          { throw std::out_of_range{ "invalid stream_delim iterator" }; }

          alive_ = static_cast<bool>(jtl::alg::getline(*stream_, string_, delims_));
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
        delims_type delims_{ "\n" };
        bool alive_{ false };
    };
  }
}
