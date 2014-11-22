/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

namespace jtl
{
  namespace trait
  {
    template <typename... Ts>
    bool constexpr disable()
    { return false; }

    template <typename... Ts>
    struct disable_t
    { static bool constexpr const value{ false }; };
  }
}
