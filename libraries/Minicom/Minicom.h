#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleTimer.h>

class MiniCom
{
protected:
    long serial_bps;       // Serial 속도
    LiquidCrystal_I2C lcd; // 1602 LCD
    SimpleTimer timer;     // 타이머
    bool no_lcd;           // LCD 사용 여부

public:
    MiniCom(long serial_bps = 115200, int lcd_addr = 0x27);
    void setNoLcd() { no_lcd = true; };
    void init();
    void run();

    // LCD 제어
    void onLCD(){ lcd.backlight(); }
    void offLCD(){ lcd.noBacklight(); }

    // 타이머 제어
    int setInterval(unsigned long interval, timer_callback f);
    SimpleTimer &getTimer() { return timer; }

    // LCD 출력 지원 메서드(helper 함수)
    void print(int row, const char *pMsg); //문자열만 출력
    void print(int row, String title, int value);
    void print(int row, String title1, int value1, String title2, int value2);
    void print(int row, String title, double value);
    void print(int row, String title1, double value1, String title2, double value2);
};