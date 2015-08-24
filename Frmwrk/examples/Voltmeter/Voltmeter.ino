#include "ShiftRegister.h"

const byte empty = B11111111;
const byte point = B11110111;
const byte minus = B01111111;
const byte t_char = B00111100;
const byte h_char = B00101010;

byte digit[10][2] = {
  {0, B10001000},
  {1, B11101011},
  {2, B01001100},
  {3, B01001001},
  {4, B00101011},
  {5, B00011001},
  {6, B00011000},
  {7, B11001011},
  {8, B00001000},
  {9, B00001001}
};

#define CLOCK_PIN 0
#define LATCH_PIN 1
#define DATA_PIN  2
#define VOLTAGE_PIN 3


// ShiftRegister(SH_CP, ST_CP, DS, INVERSE BITS)
ShiftRegister sr(CLOCK_PIN, LATCH_PIN, DATA_PIN, false);

void setup() {
  // put your setup code here, to run once:
  pinMode(VOLTAGE_PIN, INPUT);
  //Serial.begin(9600);
  sr.init();
  
  sr.open();
  sr.writeByte(minus);
  sr.writeByte(minus);
  sr.writeByte(minus);
  sr.close();
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = analogRead(VOLTAGE_PIN);
  float voltage = ((float)v*5)/313;
  //Serial.println(voltage);
  printRegister(voltage);
  //printRegister(minus);
  //printRegister(minus);
  //printRegister(minus);
  delay(400);
}

void printRegister(float v)
{
  sr.open();
  if(v < 1)
  {
    sr.writeByte(digit[0][1] & point);
    sr.writeByte(digit[((int)(v * 10)) % 10][1]);
    sr.writeByte(digit[((int)(v * 100)) % 10][1]);
  }
  else if(v < 10)
  {
    sr.writeByte(digit[((int)v) % 10][1] & point);
    sr.writeByte(digit[((int)(v * 10)) % 10][1]);
    sr.writeByte(digit[((int)(v * 100)) % 10][1]);
  }
  else if(v < 100)
  {
    sr.writeByte(digit[((int)v / 10) % 10][1]);
    sr.writeByte(digit[((int)v) % 10][1] & point);
    sr.writeByte(digit[((int)(v * 10)) % 10][1]);
  }
  else
  {
    sr.writeByte(digit[((int)v / 100) % 10][1]);
    sr.writeByte(digit[((int)v / 10) % 10][1]);
    sr.writeByte(digit[((int)v) % 10][1] & point);
  }
  sr.close();
}
