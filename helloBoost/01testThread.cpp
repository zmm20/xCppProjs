// ²Î¿¼: http://blog.chinaunix.net/uid-22301538-id-3157496.html
// #define MAIN
#ifdef MAIN

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp> 
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

// test 1
void hello() 
{ 
    std::cout << 
        "Hello world, I''m a thread!" 
        << std::endl; 
}


// test 2
boost::mutex io_mutex;
struct Count 
{ 
    Count(int id) : id(id) { } 

    void operator()() 
    { 
        for (int i = 0; i < 10; ++i) 
        { 
            boost::mutex::scoped_lock 
                lock(io_mutex); 
            std::cout << id << ": " 
                << i << std::endl; 
        } 
    } 

    int id; 
}; 


// test 3, test 4
class HelloWorld
{
public:
    void hello()
    {
        std::cout << "HelloWorld.hello" << std::endl;
    }
    void start()
    {
        boost::function0< void> f =  boost::bind(&HelloWorld::hello,this);
        boost::thread thrd( f );
        thrd.join();
    }

    void hello(const std::string& str)
    {
        std::cout <<str<< std::endl;
    }

};

int main()
{
    cout << "test 1" << endl;
    {
        boost::thread thrd(&hello); 
        thrd.join();
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        boost::thread thrd1(Count(1)); 
        boost::thread thrd2(Count(2)); 
        thrd1.join(); 
        thrd2.join(); 
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        HelloWorld hello;
        hello.start();
    }
    cout << endl;
    
    cout << "test 4" << endl;
    {
        HelloWorld obj;
        boost::thread thrd( boost::bind(&HelloWorld::hello,&obj,"HelloWorld.hello(string)!" ) ) ;
        thrd.join();
    }
    cout << endl;

    return 0;
}
#endif