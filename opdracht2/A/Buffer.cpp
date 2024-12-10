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
    while (teller == GROOTTE);
    m1.lock();
    opslag[in++]=d;
    in %=GROOTTE;
    teller++;
    m1.unlock();
}

int Buffer::haalUitBuf() {
    int waarde;
    while(teller==0);
    m1.lock();
    waarde=opslag[out++];
    out %=GROOTTE;
    teller--;
    m1.unlock();
    return waarde;
}
