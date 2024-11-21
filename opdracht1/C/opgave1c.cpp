#include <iostream>
#include <unistd.h>
#include "Timer.h"
#include <sys/wait.h>
#include "Werker.h" 
#include <thread>

int main()
{
    Timer tm1;
    Werker w1;

    tm1.Reset();

    std::thread thread1(&Werker::plaatsIets, w1, 'a', 5);
    std::thread thread2(&Werker::plaatsIets, w1, 'b', 5);
    std::thread thread3(&Werker::plaatsIets, w1, 'c', 5);
    std::thread thread4(&Werker::haalIets, w1);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    tm1.Stop();
    std::cout << tm1.deTijd() << "  " << tm1.deNtijd() << std::endl;

    return 0;
}