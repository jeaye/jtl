/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#include <jest/jest.hpp>

#include "sfinae/disable.hpp"

int main()
{
  jest::worker const j{};
  return j();
}
