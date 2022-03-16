#ifndef LED_H
#define LED_H

#pragma once

#include <Arduino.h>
// 따로 라이브러리를 추가할 때는 include 해줘야함
// 이 때 오리지널 아두이노 라이브러리 폴더를 추가해줘야함
// 파일 -> 현재 작업 영역에 폴더 추가 -> 아두이노의 라이브러리즈

class Led
{
protected:   // 상속을 위해서 protected
    int pin; // 멤버 변수

public:
    Led(int pin); // 생성자
    ~Led();       // 소멸자

    void on();
    void off();
    void toggle();
    void blink(int delay_time = 0);
    void setValue(int value);

private:
};

#endif