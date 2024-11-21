#include <iostream>
#include <unistd.h>
#include "Timer.h"
#include <sys/wait.h>

using namespace std;

void doeIets(char c, unsigned int tijd, unsigned int aantal);
int main()
{

    Timer tm1;
    tm1.Reset();

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        doeIets('p', 5, 8); // print a wacht 0.5 sec doe het 8 keer
        exit(0);
    }
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        doeIets('a', 10, 8);
        exit(0);
    }
    pid_t pid3 = fork();
    if (pid3 == 0)
    {
        doeIets('b', 15, 8);
        exit(0);
    }
    doeIets('c', 5, 8);

    while (wait(NULL) > 0)
        ;
    
    tm1.Stop();
    cout << tm1.deTijd() << "  " << tm1.deNtijd() << endl;

    return 0;
}

void doeIets(char c, unsigned int tijd, unsigned int aantal)
{

    for (int i = 0; i < aantal; ++i)
    {
        cout << c << flush; // flush leeg output buffer (print direct)
        usleep(100000 * tijd);
    }
    cout << endl;
}
