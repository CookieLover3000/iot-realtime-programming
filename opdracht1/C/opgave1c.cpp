#include <iostream>
#include <unistd.h>
#include "Timer.h"
#include <sys/wait.h>
#include <thread>

using namespace std;

void doeIets(char c, unsigned int tijd, unsigned int aantal);
int main()
{

    Timer tm1;
    tm1.Reset();

    thread thread1(doeIets, 'p', 5, 8);
    thread thread2(doeIets, 'a', 10, 8);
    thread thread3(doeIets, 'b', 15, 8);
    thread thread4(doeIets, 'c', 20, 8);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    tm1.Stop();
    cout << tm1.deTijd() << "  " << tm1.deNtijd() << endl;

    return 0;
}

void doeIets(char c, unsigned int tijd, unsigned int aantal)
{

    for (int i = 0; i < aantal; ++i)
    {
        cout << c << flush; // flush leeg output buffer (print direct)
        // usleep(100000 * tijd);
    }
    cout << endl;
}
