#include "Werker.h"
#include <iostream>

Werker::Werker()
{
    std::cout << "We zijn lekker een werker aan het maken hoor!" << std::endl;
}

Werker::~Werker()
{
    std::cout << "Doei werkertje!!" << std::endl;
}

void Werker::plaatsIets(char c, int a)
{
    for (int i; i < a; i++)
    {
        _queue.push(c);
    }
}

void Werker::haalIets(int aantal)
{
    for (int i = 0; i < aantal; i++)
    {
        if (!_queue.empty())
        {
            std::cout << _queue.front() << std::endl;
            _queue.pop();
        }
    }
}