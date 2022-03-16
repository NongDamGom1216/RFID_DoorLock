#pragma once
#include <Arduino.h>

class Buzzer
{
protected:
    int pin;                // 핀번호
    int state;              // 소리 출력 상태
    int on_time;            // 소리를 내야하는 시간 간격
    int off_time;           // 꺼져야 할 시간 간격
    unsigned long old_time; // 이전 상태 변화 시간
    bool bstop;
public:
    Buzzer(int pin);
    void beep(int duration=50); // 1회 경보음
    void stop()
    {
        bstop = true;
        digitalWrite(pin, LOW);
    }
    void setOffTime(int off_time);
    void run();
};