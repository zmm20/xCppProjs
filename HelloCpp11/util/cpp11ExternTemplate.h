#pragma once

#include <iostream>

template <typename T>
void fun1(T t) {
#pragma message("fun1 正在编译...")

    std::cout << "fun1" << std::endl;
}
// c++11 外部模板, 用来调高编译效率
// 经测试, 有了该句话之后, "fun1 正在编译..." 只打印了一次, 而 "fun2 正在编译..." 打印了2次
// , 可见下面一句是可以提高编译效率的
extern template void fun1<int>(int);

template <typename T>
void fun2(T t) {
#pragma message("fun2 正在编译...")

    std::cout << "fun2" << std::endl;
}

/*
    http://www.cnblogs.com/lvdongjie/p/4489907.html
    1. 如果外部模板指令出现于一个编译单元中，那么与之对应的显示实例化必须出现于另一个编译单元中或者同一个编译单元的后续代码中。
    2. 外部模板指令不能用于一个静态函数（即文件域函数），但可以用于类静态函数。（注：这一点是显而易见的，因为静态函数没有外部连接属性，不可能在本编译单元之外出现）。
    3. 外部模板指令应用于类的成员，而不是类本身。（注：既然已经作用于类的所有成员了，也就相当于作用于类了）
    4. 外部模板对于内联函数是否有用，没有明确规定，但鼓励编译器实现。
*/
template <typename T>
class ZCpp11ExternTemplateTest1
{
public:
    void test(T x)
    {
        std::cout << "ZCpp11ExternTemplateTest1 test " << std::endl;
    }
};
extern template class ZCpp11ExternTemplateTest1<int>;