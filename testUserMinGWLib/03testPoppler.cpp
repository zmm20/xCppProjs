#define MAIN
#ifdef MAIN

#include <iostream>

#include <memory>
#include <thread>
#include <chrono>
#include <cstdio>
#include <MyPoppler.h>
#include <unordered_map>

#pragma comment(lib, "libMyPopplerd.dll.a")
using namespace std;

int main(int argc, char *argv[])
{
    std::string imgPath(R"(test\test.pdf)");
    
    int id = MyPoppler::pdfOpen(imgPath.data());
    cout << "pdf id: " << id << endl;

    int pages = MyPoppler::pdfPages(id);
    cout << "pages = " << pages << endl;

    return EXIT_SUCCESS;
}


#endif
