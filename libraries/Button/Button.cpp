#include "Button.h"

// 멤버 초기화 : 생성자에서
Button::Button(int pin) : pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
    callback = NULL;
}

void Button::setCallback(button_callback_t callback)
{
    this->callback = callback; // 멤버변수 = 지역변수
    // 포인터의 멤버
}

// 누른 경우에H, 뗀 경우에L을 리턴
int Button::read()
{
    return !digitalRead(pin);
}

void Button::check()
{
    bool o_sw, n_sw;
    o_sw = read();
    delay(10); // 디바운스를 위한 지연시간
    n_sw = read();

    if (o_sw == 0 && n_sw == 1) // 버튼을 누른 시점
    {
        if (callback != NULL)
        {
            callback();
        }
    }
}

void Button::attachInterrupt(button_callback_t callback, int mode)
{
    ::attachInterrupt(digitalPinToInterrupt(pin), callback, mode);
    t1 = millis();
}

bool Button::debounce()
{
    unsigned long t2 = millis();
    if ((t2 - t1) < 200)
        return false;
    t1 = t2;
    return true;
}
