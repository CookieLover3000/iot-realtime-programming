#include "mbed.h"
#define AANTAL 100
Queue<int, 3> opslagRij;
Thread v1, v2, o1;
MemoryPool<int,100> mpool;
void telop() {
    int som = 0;
    while (true) {
        for (int i = 0; i < AANTAL; i++) {
            int *getalP;
            opslagRij.try_get_for(Kernel::wait_for_u32_forever, &getalP);
            som += *getalP;
            ThisThread::sleep_for(20ms);
            mpool.free(getalP);
        }
        printf("getal in optel=%d\n", som);
    }
}
int main() {
    o1.start(telop);
    int som = 0;
    while (true) {
        for (int i = 0; i < AANTAL; i++) {
        int *data = mpool.alloc();
        *data = i;
        opslagRij.try_put_for(Kernel::wait_for_u32_forever, data);
        som += i;
        }
        printf("getal in main=%d\n", som);
    }
}