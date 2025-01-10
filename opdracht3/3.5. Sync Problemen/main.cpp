#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include <string>
// main() runs in its own thread in the OS
I2C i2c(I2C_SDA, I2C_SCL);
Adafruit_SSD1306_I2c oled(i2c, 0x78, 64, 128);

typedef struct {
    string sensor;
    int    value;
} message_t;

MemoryPool<message_t, 16> mpool;
Queue<message_t, 16> queue;

void lichtsensor() {
    AnalogIn ls(A3);
    while(1) {
        message_t *message = mpool.alloc();
        message->sensor = "lichtsensor";
        message->value = ls.read_u16();
        queue.put(message);
        ThisThread::sleep_for(1s);
    }
}
void potmeter() {
    AnalogIn ls(A0);
    while(1) {
        message_t *message = mpool.alloc();
        message->sensor = "potmeter";
        message->value = ls.read_u16();
        queue.put(message);
        ThisThread::sleep_for(1s);
    }
}

void display() {
    int i = 0;
    while(1) {
        osEvent evt = queue.get();
        if (evt.status == osEventMessage) {
            message_t *message = (message_t *)evt.value.p;
            if((i%6 == 0)){
                oled.clearDisplay();
                oled.setTextCursor(0, 0);
            }
            i++;
            oled.printf("%s: %i\n",message->sensor.c_str(), message->value);
            oled.display();
            mpool.free(message);
        }
    }
}

int main()
{
    Thread t1,t2,t3;
    printf("Welkom\n");
    t1.start(lichtsensor);
    t2.start(potmeter);
    t3.start(display);
    oled.printf("Welkom\n");
    oled.display();
    while (true) {}
}