#include "AnalogIn.h"
#include "DigitalOut.h"
#include "Watchdog.h"
#include "mbed.h"
#include "Thread.h"

float light;

bool crash;

Mutex m1;

void lightDetect() {
    AnalogIn lightDetector(A3);
    Watchdog &watchdog = Watchdog::get_instance();

    while (true) {
        m1.lock();
        light = lightDetector.read();
        m1.unlock();
        printf("light value: %f\n", light);

        if(crash)
            while(1){}
        watchdog.kick();

        ThisThread::sleep_for(100ms);
    }
}

void ledControl() {
    DigitalOut led(D2);
    Watchdog &watchdog = Watchdog::get_instance();


    while(1) {

        m1.lock();
        if(light < 0.3f)
            led.write(1);
        else
            led.write(0);
        m1.unlock();
        if(crash)
            while(1){}
        watchdog.kick();

        ThisThread::sleep_for(100ms);

    }
}

void crashThread() {
    ThisThread::sleep_for(5s);
    crash = true;
    printf("Crashing!\n");
}

// main() runs in its own thread in the OS
int main() {

    Watchdog &watchdog = Watchdog::get_instance();
    watchdog.start(5000);

    Thread t1, t2, t3;
    t1.start(lightDetect);
    t2.start(ledControl);
    t3.start(crashThread);
    while(1){
    }
}