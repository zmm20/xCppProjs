//#define MAIN
#ifdef MAIN

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
using namespace std;



void func(shared_ptr<int> sp)
{
    cout << "inside func: " << sp.use_count() << endl;
}


class FileDeleter
{
private:
    std::string filename;
public:
    FileDeleter(const std::string& fn)
        : filename(fn) {
    }
    void operator () (std::ofstream* fp) {
        cout << "file close..." << endl;
        fp->close(); // close.file
        std::remove(filename.c_str()); // delete file
    }
};

// 下面是linux 下的例子
//class SharedMemoryDetacher
//{
//public:
//    void operator () (int* p) {
//        std::cout << "unlink /tmp1234" << std::endl;
//        if (shm_unlink("/tmp1234") != 0) {
//            std::cerr << "OOPS: shm_unlink() failed" << std::endl;
//        }
//    }
//};
//std::shared_ptr<int> getSharedIntMemory(int num)
//{
//    void* mem;
//    int shmfd = shm_open("/tmp1234", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
//    if (shmfd < 0) {
//        throw std::string(strerror(errno));
//    }
//    if (ftruncate(shmfd, num * sizeof(int)) == -1) {
//        throw std::string(strerror(errno));
//    }
//    mem = mmap(nullptr, num * sizeof(int), PROT_READ | PROT_WRITE,
//        MAP_SHARED, shmfd, 0);
//    if (mem == MAP_FAILED) {
//        throw std::string(strerror(errno));
//    }
//    return std::shared_ptr<int>(static_cast<int*>(mem),
//        SharedMemoryDetacher());
//}
int main()
{
    cout << "test 1" << endl;
    {
        // two shared pointers representing two persons by their name
        shared_ptr<string> pNico(new string("nico"));
        shared_ptr<string> pJutta(new string("jutta"));
        // capitalize person names
        (*pNico)[0] = 'N';
        pJutta->replace(0, 1, "J");
        // put them multiple times in a container
        vector<shared_ptr<string>> whoMadeCoffee;
        whoMadeCoffee.push_back(pJutta);
        whoMadeCoffee.push_back(pJutta);
        whoMadeCoffee.push_back(pNico);
        whoMadeCoffee.push_back(pJutta);
        whoMadeCoffee.push_back(pNico);

        // print all elements
        for (auto ptr : whoMadeCoffee) {
            cout << *ptr << " ";
        }
        cout << endl;
        // overwrite a name again
        *pNico = "Nicolai";
        // print all elements again
        for (auto ptr : whoMadeCoffee) {
            cout << *ptr << " ";
        }
        cout << endl;
        // print some internal data
        cout << "use_count: " << whoMadeCoffee[0].use_count() << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        int* p = new int;

        cout << "in main.." << endl;
        shared_ptr<int> sp1(p
            , [](int* p) {
            cout << "delete" << endl;
            delete p;
        });
        //shared_ptr<int> sp2(p); // ERROR: two shared pointers manage allocated int
        shared_ptr<int> sp2(sp1); // OK
        cout << sp1.use_count() << endl;

        func(sp2);
        cout << "in main.." << endl;
        cout << sp1.use_count() << endl;
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"),
            FileDeleter("tmpfile.txt"));
    }
    cout << endl;
    
    //cout << "test 4" << endl;
    //{
    //    // get and attach shared memory for 100 ints:
    //    std::shared_ptr<int> smp(getSharedIntMemory(100));
    //    // init the shared memory
    //    for (int i = 0; i<100; ++i) {
    //        smp.get()[i] = i * 42;
    //    }
    //    // deal with shared memory somewhere else:
    //    ...
    //        std::cout << "<return>" << std::endl;
    //    std::cin.get();
    //    // release shared memory here:
    //    smp.reset();
    //}
    //cout << endl;

    cout << "test 5" << endl;
    {
        // 注意: shared_ptr 只提供了 operator * 和 operator -> , 指针运算和 operator [] 都未提供
        shared_ptr<int> pInt(new int(5));
        shared_ptr<string> pStr = make_shared<string>("hello world");

        pInt.get()[0] = 4;
        cout << *pInt << endl;
        // 同上
        (&*pInt)[0] = 6;
        cout << *pInt << endl;

        (*pStr)[0] = 'H';
        cout << *pStr << endl;
    }
    cout << endl;
}
#endif