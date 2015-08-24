/*
  Traffic Light simulator
 */
 
#include "TrafficLight.h"
#include "Button.h"

int program0[] = { RED, 5000, 
                   RED | YELLOW, 2500,
                   GREEN, 7000,
                   YELLOW, 1500 };

int program1[] = { YELLOW, 1000,
                   OFF, 1000 };

int program2[] = { RED, 1000000 };
int program3[] = { YELLOW, 1000000 };
int program4[] = { GREEN, 1000000 };

#define PROGRAMS_COUNT 5
int* programs[PROGRAMS_COUNT] = { program0, program1, program2, program3, program4 };
int programsLength[PROGRAMS_COUNT] = {   8,        4,        2,        2,        2 };
int currentProgram = 0;

// Attiny85 pins!
//              R  Y  G
TrafficLight trafficLight(0, 1, 2);
Button btn(3, HIGH);

void setup() 
{
  btn.init(&buttonChange);
  trafficLight.init();
  trafficLight.execute(programs[currentProgram], programsLength[currentProgram]);
}

// the loop function runs over and over again forever
void loop() 
{
  btn.loop();
  trafficLight.loop();
}

void buttonChange(byte state)
{
  if(state == LOW)
  {
    currentProgram++;
    if(currentProgram >= PROGRAMS_COUNT) currentProgram = 0;
    trafficLight.execute(programs[currentProgram], programsLength[currentProgram]);
  }
}
