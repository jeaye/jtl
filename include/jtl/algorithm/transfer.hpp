#pragma once

#include <jtl/namespace.hpp>
#include <jtl/algorithm/policy/copy.hpp>
#include <jtl/trait/disable.hpp>

namespace jtl
{
  namespace algorithm
  {
    namespace detail
    {
      template <policy::transfer P>
      struct transferrer
      { static_assert(trait::disable_value<decltype(P), P>(), "invalid policy"); };

      template <>
      struct transferrer<policy::transfer::move>
      {
        template <typename T>
        auto operator ()(T &&t)
        { return std::move(t); }
      };

      template <>
      struct transferrer<policy::transfer::copy>
      {
        template <typename T>
        T const& operator ()(T const &t)
        { return t; }
      };

      template <bool B>
      policy::transfer constexpr should_move()
      { return policy::transfer::move; }
      template <>
      policy::transfer constexpr should_move<false>()
      { return policy::transfer::copy; }
    }

    /* Similar to std::move: operates based on a transfer policy.
     *
     * If the policy is <jtl::algorithm::policy::move>, this call has the same
     * effect as std::move. If it's instead <jtl::algorithm::policy::copy>, no
     * moving will be done.
     */
    template <policy::transfer P, typename T>
    auto transfer(T &&t)
    { return detail::transferrer<P>{}(std::forward<T>(t)); }

    /* Transfers with a move policy if <B> is true. Otherwise, copies.  */
    template <bool B, typename T>
    auto move_if(T &&t)
    { return transfer<detail::should_move<B>>(std::forward<T>(t)); }
  }
}
