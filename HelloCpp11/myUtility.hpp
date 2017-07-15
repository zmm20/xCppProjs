#pragma once

#include <iostream>
#include <utility>

// ¥Ú”° pair
template <typename T1, typename T2>
std::ostream& operator <<(std::ostream& os, std::pair<T1, T2> p)
{
    os << "[" << p.first << ", " << p.second << "]";
    return os;
}



// ¥Ú”°tuple
template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE
{
    static void print(std::ostream& strm, const std::tuple<Args...>& t)
    {
        strm << std::get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
        PRINT_TUPLE<IDX + 1, MAX, Args...>::print(strm, t);
    }
};
// partial specialization to end the recursion
template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...>
{
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {
    }
};

// output operator for tuples
template <typename... Args>
std::ostream& operator << (std::ostream& strm,
    const std::tuple<Args...>& t)
{
    strm << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(strm, t);
    return strm << "]";
}