#include "RFIDReader.h"

// 생성자
RFIDReader::RFIDReader()
{
    bool door_state = CLOSE;
}

// 기본 설정 초기화
void RFIDReader::init() 
{
    com.init();
    Serial.begin(115200);
    com.print(0, "[[RFID Door]]");
    com.print(1, "Waiting");
    myServo.attach(servo_pin);
    SPI.begin();
}

// 등록된 태그가 아닐 경우 2초 간 LED를 켰다 끔
void RFIDReader::not_equal()
{
    Buzzer buzzer(6);
    Serial.println("Not Equal");
    com.print(1, "Not Equal");
    leds[1].on();
    buzzer.beep(2000);
    leds[1].off();
    com.print(1, "Waiting");
}

// 맞는 태그라면 짧은 부저음과 함께 서브 모터로 문을 열어 줌
void RFIDReader::open_door()
{
    Buzzer buzzer(6);
    door_state = OPEN;
    Serial.println("Equal");
    com.print(1, "Equal");
    myServo.write(0);
    leds[0].on();
    buzzer.beep(100);
}

void RFIDReader::run()
{
    com.run();
}

void RFIDReader::close_door()
{
    door_state = CLOSE;
    leds[0].off();
    myServo.write(90);
    com.print(1, "Waiting");
}

// ID의 일치 여부 함수
bool RFIDReader::equalId(byte *id1, byte *id2)
{
    for (byte i = 0; i < 4; i++)
    {
        if (id1[i] != id2[i])
        {
            return false;
        }
    }
    return true;
}

// EEPROM에 저장된 ID를 읽는 함수
void RFIDReader::read_id(byte *id)
{
    
    for (int i = 0; i < 4; i++)
    {
        id[i] = EEPROM.read(i);

    }
}

// EEPROM에 저장된 ID를 초기화하는 함수
void RFIDReader::clear_id()
{
    // EEPROM 초기화
    for (int i = 0; i < 4; i++)
    {
        EEPROM.write(i, 0);
    }
}