/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <type_traits>

#include <jtl/namespace.hpp>

namespace jtl
{
  namespace algorithm
  {
    namespace policy
    {
      /* Specifies the data transfer format for an algorithm.
       *
       * Example: jtl::alg::consume
       */
      enum class transfer
      {
        /* Represents an algorithm implemented via std::move.
         *
         * Afterward, the source range should be considered moved.
         */
        move,

        /* Represents an algorithm implemented via copy semantics.
         *
         * The source range will be read-only.
         */
        copy
      };
    }
  }
}
