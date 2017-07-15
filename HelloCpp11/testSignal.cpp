//#define MAIN
#ifdef MAIN

#include <iostream>
#include <functional>
#include <string>
#include <csignal>

using namespace std;

namespace
{
    volatile std::sig_atomic_t gSignalStatus;
}

void signal_handler(int signal)
{
    gSignalStatus = signal;
}

int main()
{
    cout << "----------------testSignal.cpp-----------------" << endl;
    cout << "test 1" << endl;
    {
        // Install a signal handler
        std::signal(SIGINT, signal_handler);

        std::cout << "SignalValue: " << gSignalStatus << '\n';
        std::cout << "Sending signal " << SIGINT << '\n';
        std::raise(SIGINT);
        std::cout << "SignalValue: " << gSignalStatus << '\n';
    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif