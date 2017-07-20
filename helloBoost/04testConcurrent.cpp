#define MAIN
#ifdef MAIN

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <string>
#include "MyBuffer.h"
using namespace std;
using namespace boost;

// test 1
// 生产者, 消费者
MyBuffer buf(5);
void producer(int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << "put : " << i << endl;
        buf.put(i);
    }
}
void consumer(int n)
{
    int x;
    for (int i = 0; i < n; ++i)
    {
        buf.get(&x);
        cout << "get : " << x << endl;
    }
}

int main()
{
    cout << "test 1" << endl;
    {
        // 生产者, 消费者
        // http://anzhsoft.iteye.com/blog/2031353
        boost::thread t1(producer, 20);
        boost::thread t2(consumer, 10);
        boost::thread t3(consumer, 10);

        t1.join();
        t2.join();
        t3.join();
    }
    cout << endl;


    cout << "test 2" << endl;
    {
    }
    cout << endl;
}

#endif;