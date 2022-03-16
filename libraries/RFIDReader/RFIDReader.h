#ifndef RFIDREADER_H
#define RFIDREADER_H

#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <Minicom.h>
#include <Led.h>
#include <Buzzer.h>

#define button 2
#define RST_PIN 9 // reset핀은 9번으로 설정
#define SS_PIN 10 // SS핀은 10번으로 설정

const int servo_pin = 5;
const int buzzer_pin = 6;
const int OPEN = true;
const int CLOSE = false;

class RFIDReader
{
protected:
    MiniCom com;
    Led leds[2] = {Led(7), Led(3)};

    Servo myServo;

    bool door_state;

public:
    RFIDReader();
    void init();
    void open_door();
    void run();
    void close_door();
    bool equalId(byte *id1, byte *id2);
    void read_id(byte *id);
    void clear_id();
    void not_equal();
};

#endif