#include "mbed.h"
#include "Adafruit_SSD1306.h"
int main()
{
	int teller=0;
I2C i2c(I2C_SDA, I2C_SCL);
Adafruit_SSD1306_I2c oled(i2c, 0x78,64,128);
while (true) {
oled.clearDisplay();
oled.setTextCursor(0, 0);
oled.printf("De tellerwaarde=%d ", teller++);
oled.display();
ThisThread::sleep_for(1000ms);
}
}