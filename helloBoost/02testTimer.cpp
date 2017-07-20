//#define MAIN
#ifdef MAIN

#include <boost/asio.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp> 
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace std;

// test 2
void print(const boost::system::error_code& /*e*/)  
{  
    std::cout << "02 Hello, world!\n";  
}

// test 3
void print3(const boost::system::error_code& e,  
           boost::asio::deadline_timer* t)  
{  
    cout<<"ddd"<<endl;
    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));  
    t->async_wait(boost::bind(print3,boost::asio::placeholders::error,t));  
}  

int main()
{
    cout << "test 1" << endl;
    {
        boost::asio::io_service io;  
        boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));  

        timer.wait();  
        std::cout << "01 Hello, world!" << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        boost::asio::io_service io;  
        boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));

        timer.async_wait(&print);  
        io.run();
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        boost::asio::io_service io;  
        boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
        t.async_wait(boost::bind(print3, boost::asio::placeholders::error, &t));
        io.run();
    }
    cout << endl;

    return 0;
}
#endif