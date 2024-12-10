#include <iostream>
#include <unistd.h>
#include "Timer.h"
#include <sys/wait.h>

using namespace std;

void doeIets(char c, unsigned int tijd, unsigned int aantal, int pipefd_write);
int main()
{

    Timer tm1;
    tm1.Reset();

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {

        close(pipefd[0]);
        doeIets('p', 5, 8, pipefd[1]); // print a wacht 0.5 sec doe het 8 keer
        close(pipefd[1]);
        exit(0);
    }
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[0]);
        doeIets('a', 10, 8, pipefd[1]);
        close(pipefd[1]);
        exit(0);
    }
    pid_t pid3 = fork();
    if (pid3 == 0)
    {
        close(pipefd[0]);
        doeIets('b', 15, 8, pipefd[1]);
        close(pipefd[1]);
        exit(0);
    }

    char buffer;
    close(pipefd[1]);
    while (read(pipefd[0], &buffer, 1) > 0)
    {
        std::cout << buffer;
    }

    close(pipefd[0]);

    while (wait(NULL) > 0)
        ;

    tm1.Stop();
    cout << tm1.deTijd() << "  " << tm1.deNtijd() << endl;

    return 0;
}

void doeIets(char c, unsigned int tijd, unsigned int aantal, int pipefd_write)
{

    for (int i = 0; i < aantal; ++i)
    {
        write(pipefd_write, &c, 1);
        // usleep(100000 * tijd);
    }
    write(pipefd_write, "\n", 1);
}
