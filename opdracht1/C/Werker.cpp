#include "Werker.h"
#include <iostream>

std::queue<char> Werker::_queue;

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
    for(int i; i < a; i++)
    {
        _queue.push(c);
    }
}

void Werker::haalIets()
{
    while(!_queue.empty()) {
        std::cout << _queue.front() << std::endl;
        _queue.pop();
    }
}