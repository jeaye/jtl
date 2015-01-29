/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing at:
    http://opensource.org/licenses/MIT

  Author: Jesse 'Jeaye' Wilkerson
*/

#include <jest/jest.hpp>

#include "algorithm/consume.hpp"
#include "algorithm/trim.hpp"
#include "algorithm/split.hpp"
#include "algorithm/getline.hpp"
#include "algorithm/transform_if.hpp"

int main()
{
  jest::worker const j{};
  return j();
}
