#include "Led.h"

// scope 연산자 : Led 클래스의 생성자
// pin(pin)는 멤버변수 pin(매개변수 pin) -> 멤버 변수 초기화
Led::Led(int pin) : pin(pin)
{
    // 지역 변수 -> 멤버 변수 -> 전역 변수
    // 멤버 변수를 표현할 때는 this->
    pinMode(pin, OUTPUT); // 지역 변수(매개 변수)
}

Led::~Led()
{
}

void Led::on()
{
    digitalWrite(pin, HIGH);
}

void Led::off()
{
    digitalWrite(pin, LOW);
}

// digitalRead(pin) : 현재 나가고 있는 신호를 읽음
void Led::toggle()
{
    int v = !digitalRead(pin); // 현재 신호의 반대값을 digitalWrite한다.
    digitalWrite(pin, v);
}

void Led::blink(int delay_time)
{
    toggle();
    if (delay_time > 0)
    {
        delay(delay_time);
    }
}

void Led::setValue(int value)
{
    digitalWrite(pin, value);
}
