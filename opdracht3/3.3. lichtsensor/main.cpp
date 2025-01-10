/*
 * Opdracht 3.3 RealTime Embedded Programming
 */

#include "AnalogIn.h"
#include "mbed.h"
#include "Adafruit_SSD1306.h"

// main() runs in its own thread in the OS
int main()
{
    I2C i2c(I2C_SDA, I2C_SCL);
    Adafruit_SSD1306_I2c oled(i2c, 0x78,64,128);
    AnalogIn lightDetector(A3);



    while (true) {
        oled.clearDisplay();
        oled.setTextCursor(0, 0);
        float light = lightDetector.read();
        oled.printf("light value: %f ", light);
        oled.display();
        ThisThread::sleep_for(1000ms);
    }
}