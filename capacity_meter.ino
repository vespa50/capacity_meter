#include <ShiftRegister74HC595.h>

#define numberOfShiftRegisters 2

#define button1 2
#define button2 3
#define button3 4

#define currentsource1 5
#define currentsource2 6

#define serialDataPin 7
#define clockPin 8
#define latchPin 9

#define outputEN 10
#define voltagesens A0

#define minvolt 0.8
#define maxvolt 20
#define maxcur 3


ShiftRegister74HC595<numberOfShiftRegisters> sr(serialDataPin, clockPin, latchPin);
//0-9 A V segmenti abcdefgp
const uint8_t caratteri[16] = {
  B11111100,  //0
  B01100000,  //1
  B11011010,  //2
  B11110010,  //3
  B01110110,  //4
  B10110110,  //5
  B10111110,  //6
  B11100000,  //7
  B11111110,  //8
  B11110110,  //9
  B11101110,  //A
  B01111100,  //V
  B00101110,  //h
  B10011110,  //E
  B00101010,  //n
  B00000000   //blank
};

float set_current = 0;
float stop_voltage = 1;
float capacity = 0;
int time0 = 0;
int state = 0;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

void display(float val, int tipo) {
  uint8_t car[5][2];

  car[0][0] = caratteri[(int)(val / 10)];
  car[0][1] = B00000001;
  car[1][0] = caratteri[(int)((val - (car[0][0] * 10)) / 10)];
  car[1][1] = B00000010;
  car[2][0] = caratteri[(int)((val - (car[0][0] * 10) - car[1][0]) * 10)];
  car[2][1] = B00000100;
  car[3][0] = caratteri[(int)((val - (car[0][0] * 10) - car[1][0] - (car[2][0] / 10)) * 100)];
  car[3][1] = B00001000;
  car[4][1] = B00010000;


  if (tipo == 0) {  //stop_volt
    if (millis() % 1000 < 500) {
      car[4][0] = caratteri[11];
    } else {
      car[4][0] = caratteri[15];
    }
    car[1][0] = car[1][0] | 0x01;
    for (int i = 0; i < 5; i++) {
      sr.setAll(car[1]);
      delay(10);
    }
  } else if (tipo == 1) {  //set_current
    if (millis() % 1000 < 500) {
      car[4][0] = caratteri[10];
    } else {
      car[4][0] = caratteri[15];
    }
    car[1][0] = car[1][0] | 0x01; 
    for (int i = 0; i < 5; i++) {
      sr.setAll(car[1]);
      delay(10);
    }
  } else if (tipo == 2) {  //tempo
    car[4][0] = caratteri[12];
    car[2][0] = car[2][0] | 0x01;
    for (int i = 0; i < 5; i++) {
      sr.setAll(car[1]);
      delay(10);
    }
  } else if (tipo == 3) {  //capacità
    car[4][0] = caratteri[15];
    car[1][0] = car[1][0] | 0x01;
    for (int i = 0; i < 5; i++) {
      sr.setAll(car[1]);
      delay(10);
    }
  } else if (tipo == 4) {  //voltaggio
    car[4][0] = caratteri[11];
    car[2][0] = car[2][0] | 0x01;
    for (int i = 0; i < 5; i++) {
      sr.setAll(car[1]);
      delay(10);
    }
  } else if (tipo == 5) {  //enable
    car[0][0] = caratteri[15];
    car[1][0] = caratteri[13];
    car[2][0] = caratteri[14];
    car[3][0] = caratteri[15];
    car[4][0] = caratteri[15];
    for (int i = 0; i < 5; i++) {
      sr.setAll(car[1]);
      delay(10);
    }
  } else {
    car[0][0] = caratteri[13];
    car[1][0] = caratteri[13];
    car[2][0] = caratteri[13];
    car[3][0] = caratteri[13];
    car[4][0] = caratteri[13];
    for (int i = 0; i < 5; i++) {
      sr.setAll(car[1]);
      delay(10);
    }
  }
}
