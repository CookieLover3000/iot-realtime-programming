//
//  verwerker.hpp
//  sensoren
//
//  Created by John Vi on 4/26/19.
//  Copyright © 2019 John Vi. All rights reserved.
//

#ifndef verwerker_hpp
#define verwerker_hpp

#include <stdio.h>
#include <vector>
#include <atomic>

using namespace std;

class Buffer;
class Verwerker {
public:
    Verwerker(Buffer*,int);
    void verwerkData();
    void zetUit();
    int hetResultaat()const;
    void aantalTeLezenData(int);
    vector<int> deTussenstanden() const;
private:
    inline static vector<int> tussenstanden;
    int hoeveel;
    Buffer *buf;
    inline static atomic<int> result = 0;
    bool status;
    mutex m1;
};
#endif /* verwerker_hpp */
