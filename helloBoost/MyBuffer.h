#pragma once

#include <boost/thread.hpp>  
#include <stack>  
using std::stack;
using std::cout;
using std::endl;
class MyBuffer
{
private:
    boost::mutex mu; // 条件变量需要配合互斥量  
    boost::condition_variable_any cond_put; // 生产者写入  
    boost::condition_variable_any cond_get; // 消费者读走  

    stack<int> stk;
    int un_read;
    int capacity;

    bool is_full()
    {
        return un_read == capacity;
    }
    bool is_empty()
    {
        return 0 == un_read;
    }

public:
    MyBuffer(size_t capacity) : un_read(0), capacity(capacity)
    {}
    void put(int x)
    {
        boost::mutex::scoped_lock lock(mu); // 这里是读锁的门闩类  
        while (is_full())
        {
            cout << "full waiting..." << endl;
            cond_put.wait(mu);
        }
        stk.push(x);
        ++un_read;

        cond_get.notify_one();
    }
    void get(int *x)
    {
        boost::mutex::scoped_lock lock(mu); // 这里是读锁的门闩类  
        while (is_empty())
        {
            cout << "empty waiting..." << endl;
            cond_get.wait(mu);
        }
        *x = stk.top();
        stk.pop();
        --un_read;

        cond_put.notify_one(); // 通知 51line可以写入了
    }
};