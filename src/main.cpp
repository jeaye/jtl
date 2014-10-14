#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>

#include "iterator/multi_insert.hpp"

int main()
{
  std::string s{ "jeaye" };
  std::string out{ "name: " };
  std::transform(s.begin(), s.end(), jtl::multi_inserter(out, out.end()),
  [](char const c) -> std::vector<char>
  { return {'[', c, ']'}; });
  //{ return "[" + std::string{c} + "]"; });
  std::cout << out << std::endl;
}