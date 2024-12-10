
#include "Buffer.hpp"
#include "Sensor.hpp"
#include <stdlib.h>


void Sensor::genereerdData()
{
    unsigned int rd = (rand() % 2000) + 1;
    std::this_thread::sleep_for(std::chrono::nanoseconds(rd));

    stand = 0;
    int h = hoeveel;
    while (h--)
    {
        int x = stand++;
        if (stand > eind)
            stand = begin;
        buf->zetInBuf(x);
    }
}
void Sensor::aantalTeGenererenData(int d)
{
    hoeveel = d;
}

Sensor::Sensor(int b, int e, int h, Buffer *bf) : begin(b), eind(e), hoeveel(h), stand(0), buf(bf)
{
}
