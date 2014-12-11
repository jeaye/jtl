# jtl - a spare-tire template library
jtl is a C++14 library which aims to provide an augmentation of the C++ stdlib and boost. It's focused on template meta-programming and achieving a more functional C++.

  * Header only (easy to add to any project)
  * Extensive test suite (using [jest](https://github.com/jeaye/jest), a "sane and minimal C++14 unit test framework")

# Overview
There exists generated documentation \<TODO\> which should suffice as a reference. This overview will link to separate sections in the documentation.

## Namespaces
Most namespaces come with an alias for shorthand access. For example, `jtl::algorithm` can be accessed as `jtl::alg`.

  * [algorithm]() (alg)
    *A collection of algorithms similar to that of \<algorithm\>*
  * [iterator]() (it)
    *A collection of iterator types similar to that of \<iterator\>*
  * [trait]()
    *A collection of traits and other meta-functions similar to that of \<type_traits\>*

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

### iterator

  * [stream_delim]()
    *Provides iteration over input streams given a delimiter*
    ```cpp
    std::stringstream ss{ "0\n1\n2\n3" };
    std::vector<std::string> lines;

    std::copy(jtl::iterator::stream_delim<>{ ss },
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
  * [insert](), [front_insert](), [back_insert]()
    *A drop-in, improved replacement for std::insert_iterator and the like*

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
  * [show]()
    *Fails compilation using the type pack in order to display each type*
    ```cpp
    // Will halt the compiler and output the typenames

    template <typename... Args>
    void what_is_going_on()
    { show<Args...>(); } 
    ```

# License
jtl is under the MIT open-source license.  
See the `LICENSE` file or http://opensource.org/licenses/MIT
