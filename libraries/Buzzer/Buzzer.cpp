#include "Buzzer.h"
Buzzer::Buzzer(int pin) : pin(pin)
{
    state = LOW;
    off_time = 0;
    on_time = 100; // 100ms
    old_time = millis();
    pinMode(pin, OUTPUT);
    bstop = true;
}
void Buzzer::beep(int duration)
{
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
}
void Buzzer::setOffTime(int off_time)
{
    this->off_time = off_time;
    bstop = false;
}

void Buzzer::run()
{
    unsigned long cur, diff;
    if (bstop)
        return;
    cur = millis();        // 현재 시간
    diff = cur - old_time; // 이전 상태변화 시간에서의 시간차
    if (state)
    { // 소리를 출력하고 있는 상태
        if (diff > on_time)
        {                           // 소리 출력 시간이 끝났음
            digitalWrite(pin, LOW); // 소리 끄기
            state = LOW;            // 꺼짐 상태
            old_time = cur;         // 상태 변이 시간 갱신
        }
    }
    else
    { // 소리가 껴져 있는 상태
        if (diff > off_time)
        {                            // 소리 꺼진 시간이 끝났음
            digitalWrite(pin, HIGH); // 소리 켜기
            state = HIGH;            // 켜짐 상태
            old_time = cur;          // 상태 변이 시간 갱신
        }
    }
}