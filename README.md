# jtl - a spare-tire template library
jtl is a C++14 library which aims to provide an augmentation of the C++ stdlib and boost. It's focused on template meta-programming and achieving a more functional C++.

  * Header only (easy to add to any project)
  * Extensive test suite (using [jest](https://github.com/jeaye/jest), a "sane and minimal C++14 unit test framework")

# Overview
There exists generated documentation \<TODO\> which should suffice as a reference. This overview will link to separate sections in the documentation.

## Namespaces
Most namespaces come with an alias for shorthand access. For example, `jtl::algorithm` can be accessed as `jtl::alg`.

  * [algorithm]() (alg)
    *Algorithms similar to that of \<algorithm\>*
    * [policy]() (pol)
      *Policies which jtl algorithms support*
  * [iterator]() (it)
    *Iterator types similar to that of \<iterator\>*
  * [container]()
    *Containers and container utilities*
  * [trait]()
    *Traits and other meta-functions similar to that of \<type_traits\>*

## A deeper look

### algorithm

  * [consume](), [consume_copy]()
    *Maps N elements of input to one output*  
    ```cpp
    auto const points{ 0, 1, 2, 3, 4, 5 };
    std::vector<triangle> tris(2);
    jtl::alg::consume<3>(points.begin(), points.end(), tris.begin());

    // points has been moved from; use consume_copy to prevent moving
    // tris == { { 0, 1, 2 }, { 3, 4, 5 } }
    ```
  * [transfer]()
    *Similar to std::move: operates based on a transfer policy*  
    ```cpp
    jtl::alg::transfer<jtl::alg::pol::copy>(foo);

    jtl::alg::transfer<jtl::alg::pol::move>(foo);
    ```
  * [move_if]()
    *Transfers with a move policy if true. Otherwise, copies*  
    ```cpp
    jtl::alg::move_if<is_integer<T>::value>(foo);

    jtl::alg::move_if<true>(foo); // equivalent to std::move(foo)
    ```
  * [trim](), [trim_left](), [trim_right]()
    *Trims all trailing/leading vals*
    ```cpp
    std::string s{ "  \t meow\n\t" };
    s.erase(jtl::alg::trim(s.begin(), s.end(), " \t\n"), s.end());

    // s == "meow"

    std::vector<int> v{ 42, 0, 1, 2, 8, 7 };
    v.erase(jtl::alg::trim(v.begin(), v.end(), {42, 7, 8}), v.end());

    // v == { 0, 1, 2 }
    ```
  * [getline]()
    *Follows std::getline but allows multiple delimiters*
    ```cpp
    std::stringstream ss{ "one\ntwo|three four" };
    std::string nums[4];

    jtl::alg::getline(ss, nums[0], "\n| ");
    jtl::alg::getline(ss, nums[1], "\n| ");
    jtl::alg::getline(ss, nums[2], "\n| ");
    jtl::alg::getline(ss, nums[3], "\n| ");
    
    // nums == [ "one", "two", "three", "four" ]
    ```
  * [transform_if]()
    *Follows std::transform but allows skipping of items*
    ```cpp
    std::vector<int> v{ 0, 1, 2, 3, 4 };
    std::vector<std::string> out;
    jtl::alg::transform_if(v.begin(), v.end(), jtl::it::back_inserter(out),
                           [](auto const i)
                             -> std::experimental::optional<std::string>
                           {
                             if(i % 2)
                             { return { std::to_string(i) }; }
                             else
                             { return {}; }
                           });
                           
    // out == { "1", "3" }
    ```

### iterator

  * [stream_delim]()
    *Provides iteration over input streams given a delimiter*
    ```cpp
    std::stringstream ss{ "0\n1\n2\n3" };
    std::vector<std::string> lines;

    std::copy(jtl::iterator::stream_delim<>{ ss }, // default: '\n'
              jtl::iterator::stream_delim<>{},
              std::back_inserter(lines));
    ```
  * [multi_insert](), [multi_back_insert]()
    *Inserts ranges at a time*
    ```cpp
    std::string const s{ "data" };
    std::string out{ "{}" };
    std::transform(s.begin(), s.end(),
                   jtl::iterator::multi_inserter(out, std::next(out.begin())),
    [](char const c)
    { return "[" + std::string{ c } + "]"; });
    
    // out == "{[d][a][t][a]}"
    ```
  * [transmute_back_insert]()
    *Transmutes output of T\<E\> to T2\<E\>*
    ```cpp
    std::stringstream ss{ "w0|w1|w2" };
    std::vector<std::vector<char>> out;
    std::copy(jtl::iterator::stream_delim<>{ ss, '|' },
              jtl::iterator::stream_delim<>{},
              jtl::iterator::transmute_back_inserter(out));
    
    // would normally expect vector<string>, but transmutation
    // allows for other [compatible] container types.
    // out == { { 'w', '0' }, { 'w', '1' }, { 'w', '2' } }
    ```
  * [make_range]()
    *Creates a direct or indirect range of `[begin, end)`*
    ```cpp
    // indirect range on std::vector::const_iterator
    std::vector<int> const v{ 0, 1, 2, 3 };
    for(auto const i : jtl::it::make_range(v.begin(), std::next(v.begin(), 2)))
    { std::cout << i << " "; }
    // output: 0 1

    // direct range on int values
    for(auto const i : jtl::it::make_range(0, 10))
    { std::cout << i << " "; }
    // output: 0 1 2 3 4 5 6 7 8 9
    ```
  * [insert](), [front_insert](), [back_insert]()
    *A drop-in, improved replacement for std::insert_iterator and the like*

### container
  * [make_array]()
    *Builds an std::array, deducing type and arity*

### trait

  * [disable](), [disable_t](), [disable_value](), [disable_value_t]()
    *Unconditionally returns false, consuming all types/values*
    ```cpp
    template <typename T>
    char const* name()
    { static_assert(jtl::trait::disable<T>(), "unsupported type"); }

    template <>
    char const* name<int>()
    { return "int"; }
    ```
  * [is_indirect]()
    *Determines if a type can use operator->*
  * [show]()
    *Fails compilation using the type pack in order to display each type*
    ```cpp
    // Will halt the compiler and output the typenames

    template <typename... Args>
    void what_is_going_on()
    { jtl::trait::show<Args...>(); } 
    ```

# License
jtl is under the MIT open-source license.  
See the `LICENSE` file or http://opensource.org/licenses/MIT
