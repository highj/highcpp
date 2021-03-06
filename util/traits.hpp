#ifndef __UTIL_HPP__
#define __UTIL_HPP__

namespace highcpp_util {

  template <typename T>
  struct lambda_traits
      : public lambda_traits<decltype(&T::operator())>
  {};
  // For generic types, directly use the result of the signature of its 'operator()'

  template <typename ClassType, typename ReturnType, typename... Args>
  struct lambda_traits<ReturnType(ClassType::*)(Args...) const>
  // we specialize for pointers to member function
  {
      enum { arity = sizeof...(Args) };
      // arity is the number of arguments.

      typedef ReturnType result_type;

      template <size_t i>
      struct arg
      {
          typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
          // the i-th argument is equivalent to the i-th tuple element of a tuple
          // composed of those arguments.
      };
  };

}

#endif // __UTIL_HPP__
