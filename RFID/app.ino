#include <SPI.h>
#include <MFRC522.h>
#include <Buzzer.h>
#include <EEPROM.h>
#include <RFIDReader.h>
#include <Button.h>

#define button 2  // 버튼 핀
#define RST_PIN 9 // reset핀
#define SS_PIN 10 // SS핀

MFRC522 mfrc(SS_PIN, RST_PIN); // RFID mfrc
Buzzer buzzer(6);
byte myId[4] = {}; // EEPROM에서 읽은 ID 바이트 변수

RFIDReader reader;

int t1, t2; // 인터럽트 발생 시간 저장

void register_id()
{

    t2 = millis(); // 현재 시간 저장

    while ((t2 - t1) < 5000)
    {
        // 버튼을 눌렀을 때 이미 등록되어 있는 카드라면 문구 출력
        if (mfrc.uid.uidByte[0] == myId[0] || mfrc.uid.uidByte[1] == myId[1] || mfrc.uid.uidByte[2] == myId[2] || mfrc.uid.uidByte[3] == myId[3])
        {
            Serial.println("Already registered");
            delay(1000);
            t1 = t2;
            return;
        }
        else
        {
            // 저장되어 있지 않은 ID EEPROM에 저장
            for (int i = 0; i < 4; i++)
            {
                EEPROM.write(i, mfrc.uid.uidByte[i]);
            }
            delay(1000);
            Serial.println("saved!");
            t1 = t2;
            return;
        }
    }
}

void setup()
{
    Serial.begin(115200);
    reader.init();
    mfrc.PCD_Init();
    t1 = millis();
    pinMode(button, INPUT_PULLUP); // 버튼을 INPUT PULL UP
    //reader.clear_id();
    // 필요 시 EEPROM 초기화
    reader.read_id(myId);
}

void loop()
{
    if (!mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial())
    {
        // 태그 접촉이 되지 않았을때 또는 ID가 읽혀지지 않았을때
        delay(500);
        return;
    }

    Serial.print("Card UID:"); // 태그의 ID출력
    // 태그의 ID출력하는 반복문.태그의 ID사이즈(4)까지
    for (byte i = 0; i < 4; i++)
    {
        // mfrc.uid.uidByte[0] ~ mfrc.uid.uidByte[3]까지 출력
        Serial.print(mfrc.uid.uidByte[i]);
        Serial.print(" "); // id 사이의 간격 출력
    }
    Serial.println();

    // INPUL PULL UP 방식
    if (digitalRead(button) == LOW)
    {
        Serial.println("sign up your card");
        register_id();
    }
    else
    {
        reader.read_id(myId); // EEPROM에서 저장된 아이디 읽기

        if (reader.equalId(myId, mfrc.uid.uidByte) == true) // 저장된 ID와 태그가 같으면 통과
        {
            reader.open_door();
            delay(5000);
            reader.close_door(); // 열린 문은 5초 뒤에 자동으로 닫힘
        }

        else
        { // ID가 같지 않을 경우
            reader.not_equal();
        }
    }

    reader.run();
    buzzer.run();
}
