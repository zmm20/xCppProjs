#define MAIN
#ifdef MAIN

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread_pool.hpp>
#include <string>
#include <functional>
#include "MyBuffer.h"
#include "RWData.h"
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


// test 2
// 共享锁
void writer(RWData& d)
{
    for (int i = 0; i < 20; ++i)
    {
        this_thread::sleep(posix_time::millisec(10));
        d.write();
    }
}

void reader(RWData& d, mutex& io_mu)
{
    int x;

    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep(posix_time::millisec(5));
        d.read(x);
        mutex::scoped_lock lock(io_mu);
        std::cout << "reader:" << x << std::endl;
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
        // http://blog.csdn.net/hh794362661/article/details/46540221
        RWData d;
        thread_group pool;
        mutex io_mu;

        pool.create_thread(bind(reader, boost::ref(d), boost::ref(io_mu)));
        pool.create_thread(bind(reader, boost::ref(d), boost::ref(io_mu)));
        pool.create_thread(bind(reader, boost::ref(d), boost::ref(io_mu)));
        pool.create_thread(bind(reader, boost::ref(d), boost::ref(io_mu)));
        pool.create_thread(bind(writer, boost::ref(d)));
        pool.create_thread(bind(writer, boost::ref(d)));

        pool.join_all();
    }
    cout << endl;
}

#endif;