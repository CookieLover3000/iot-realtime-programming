#ifndef WERKER_H
#define WERKER_H

#pragma once

#include <iostream>
#include <queue>


class Werker
{
public:
    Werker();
    ~Werker();
    void plaatsIets(char c, int a);
    void haalIets();

private:
    static std::queue<char> _queue;
};

#endif