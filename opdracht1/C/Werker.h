#ifndef WERKER_H
#define WERKER_H

#pragma once

#include <iostream>
#include <queue>
#include <mutex>


class Werker
{
public:
    Werker();
    ~Werker();
    void plaatsIets(char c, int a);
    void haalIets(int);

private:
    static inline std::queue<char> _queue;
    static inline std::mutex mtx;
};

#endif