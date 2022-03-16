#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <Arduino.h>

// 매개변수 없는 void 함수에 대한 포인터를 button_callback_t로 정의(매개변수 정보)
typedef void (*button_callback_t)();
// typedef : 별칭할 때 쓴다, 복잡한 구조를 단순화시킬 수 있다

class Button
{
protected:
    int pin;
    button_callback_t callback; // callback 함수에 대한 포인터
    // void (*callback)(); 과 같다.
    unsigned long t1;

public:
    Button(int pin);
    void setCallback(button_callback_t callback);
    int read();
    void check();
    void attachInterrupt(button_callback_t callback, int mode);
    bool debounce();

private:
};

#endif