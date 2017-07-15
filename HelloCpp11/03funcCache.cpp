//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <map>
#include <memory>

using namespace std;

// 函数缓存
template <typename R, typename... Args>
std::function<R(Args...)> cache(R(*func) (Args...))
{
    auto result_map = std::make_shared<std::map<std::tuple<Args...>, R>>();

    return ([=](Args... args) {
        std::tuple<Args...> t(args...);
        if (result_map->find(t) == result_map->end())
            (*result_map)[t] = func(args...);

        return (*result_map)[t];
    });
}

template <typename R, typename...  Args>
std::function<R(Args...)> sugar(R(*func)(Args...), bool needClear = false)
{
    using function_type = std::function<R(Args...)>;
    static std::unordered_map<decltype(func), function_type> functor_map;

    if (needClear)
        return functor_map[func] = cache(func);

    if (functor_map.find(func) == functor_map.end())
        functor_map[func] = cache(func);

    return functor_map[func];
}

size_t fibonacci(size_t n)
{
    //return (n < 2) ? n : fibonacci(n - 1) + fibonacci(n - 2);
    return (n < 2) ? n : sugar(fibonacci)(n - 1) + sugar(fibonacci)(n - 2); // 函数缓存, 可以提高几十倍的效率
}

int main()
{
    cout << "test 1: " << endl;
    {
        size_t n = fibonacci(40); // 没有函数缓存要十几秒
        cout << "n = " << n << endl;
    }
    cout << endl;

    //cout << "test 2: " << endl;
    //{
    //    
    //}
    //cout << endl;

    return EXIT_SUCCESS;
}

#endif