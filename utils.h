#pragma once
#include <array>
#include <utility>

template<typename T, typename Head, typename... Args>
struct IsOneOfImpl
{
  static bool check(T&& t, Head&& h, Args&&... args)
  {
    return IsOneOfImpl<T,Head>::check(std::forward<T>(t),std::forward<Head>(h)) ||
        IsOneOfImpl<T, Args...>::check(std::forward<T>(t), std::forward<Args>(args)...);
  }
};
template<typename T, typename Last>
struct IsOneOfImpl<T, Last>
{
  static bool check(T&& t, Last&& l)
  {
    return (std::forward<T>(t) == std::forward<Last>(l));
  }
};
template<typename T, typename Head, typename... Args>
bool isOneOf(T&& t, Head&& h,  Args&&... args)
{
  return IsOneOfImpl<T, Head, Args...>::check(std::forward<T>(t),
                                              std::forward<Head>(h),
                                              std::forward<Args>(args)...);
}

template<typename Container, typename KeyT>
bool contains(Container const& c, KeyT const& key)
{
    return std::find(std::begin(c), std::end(c), key) != std::end(c);
}
template<typename Container, typename Pred>
bool contains_if(Container const& c, Pred pred)
{
    return std::find_if(std::begin(c), std::end(c), pred) != std::end(c);
}

template<typename T, size_t... Numbers>
struct NumbersSequence
{
  std::array<T, sizeof...(Numbers)> numbers{{T(Numbers)...}};
};

template<typename T, size_t N, size_t... Tail>
struct GenerateSequence : GenerateSequence<T, N-1, N-1, Tail...>{};
template<typename T, size_t... Numbers>
struct GenerateSequence<T, 0, Numbers...>
{
  typedef NumbersSequence<T, Numbers...> type;
};
template<typename T, size_t NumElements>
std::array<T, NumElements> createArray()
{
  return typename GenerateSequence<T, NumElements>::type().numbers;
}
