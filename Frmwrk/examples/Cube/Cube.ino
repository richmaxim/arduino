#include "ShiftRegister.h"

#define cubeSize 4

byte cube[] = { B11111111, B11111111, B11111111, B11111111 };
byte off[] = { B00000000, B00000000, B00000000, B00000000 };

byte rightSide[] = { B00000001, B11000000, B11100000, B01110000 };
byte centerVSide[] = { B00000010, B00100101, B00010010, B10001001 };
byte leftSide[] = { B00000100, B00011010, B00001101, B00000110 };

byte topSide[] = { B00000000, B00000000, B00000001, B11111111 };
byte centerHSide[] = { B00000000, B0000011, B11111110, B00000000 };
byte bottomSide[] = { B00000111, B11111100, B00000000, B00000000 };

byte diagRT2LBSide[] = { B00000100, B00011001, B00010010, B01110000 };

// ShiftRegister(SH_CP, ST_CP, DS, INVERSE BITS)
ShiftRegister sr(0, 1, 2, true);

void setup() {

  sr.init();
  
  showCube(off);  
  
  randomSeed(millis());
  
  //showCube(diagRT2LBSide);
}

int frameDelay = 200;

void loop() 
{
  //rotateCenterSides();
  rain();
}

void showCube(byte* c)
{
  sr.open();
  sr.writeBytes(c, cubeSize);
  sr.close();
}

void rotateCenterSides()
{
  showCube(centerVSide);
  delay(frameDelay);
  showCube(centerHSide);
  delay(frameDelay);
}

void rotateSides()
{
  showCube(topSide);
  delay(frameDelay);
  showCube(rightSide);
  delay(frameDelay);
  showCube(bottomSide);
  delay(frameDelay);
  showCube(leftSide);
  delay(frameDelay);
}

byte rainDrops[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte rainDropBits[] = { 0, 0, 0, 0 };

void rain()
{
  for(size_t i=0;i<4;i++) rainDropBits[i] = 0;

  for(size_t i=0;i<9;i++)
  {
    if(rainDrops[i] < 0) rainDrops[i]=rainDrops[i]+1;
    if(rainDrops[i] > 0) rainDrops[i]+=9;
    if(rainDrops[i] == 0 && random(1024)%2 == 0) rainDrops[i] = i+1;
    if(rainDrops[i] > 9*5+i) rainDrops[i]=0;

    if(rainDrops[i] == 0 || rainDrops[i] > 27) continue;
    size_t byteIndex = (rainDrops[i] - 1) / 8;
    size_t bitIndex = (rainDrops[i] - 1) % 8;
    rainDropBits[3 - byteIndex] |= 1 << (bitIndex);
  }
   
  showCube(rainDropBits);
  delay(frameDelay);
}

