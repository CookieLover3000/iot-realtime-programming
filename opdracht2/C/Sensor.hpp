//
//  Sensor.hpp
//  sensoren
//
//  Created by John Vi on 4/26/19.
//  Copyright © 2019 John Vi. All rights reserved.
//

#ifndef Sensor_hpp
#define Sensor_hpp

#include <stdio.h>
class Buffer;
class Sensor {

private:
    int begin,eind;
    int hoeveel;
    int stand;
    Buffer *buf;
    
public:
    Sensor(int,int,int,Buffer*);
    void genereerdData();
    void aantalTeGenererenData(int);
};
#endif /* Sensor_hpp */
