//
//  Buffer.cpp
//  sensoren
//
//  Created by John Vi on 4/26/19.
//  Copyright © 2019 John Vi. All rights reserved.
//

#include "Buffer.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

void Buffer::zetInBuf(int d) {
    leeg.acquire();
    m1.lock();
    opslag[in++]=d;
    std::cout << teller << " in" << std::endl;
    in %=GROOTTE;
    teller++;
    m1.unlock();

    vol.release();
}

int Buffer::haalUitBuf() {
    vol.acquire();
    int waarde;
    m1.lock();
    waarde=opslag[out++];
    std::cout << teller << " uit" << std::endl;
    out %=GROOTTE;
    teller--;
    m1.unlock();
    leeg.release();
    return waarde;
}
