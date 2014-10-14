/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  File: test/src/main.cpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#include <jest/jest.hpp>

#include "iterator_test/multi_insert.hpp"

int main()
{
  jest::worker const j{};
  return j();
}
