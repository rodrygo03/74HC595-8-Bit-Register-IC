#include "IC_74HC595.h"

unsigned short cnt_pin = 9;
unsigned short rst_pin = 8;
unsigned short OE_pin = 2;
unsigned short MR_pin = 4;
unsigned short DS_pin = 7;
unsigned short SHCP_pin = 12;
unsigned short STCP_pin = 13;
double DELAY = 0;
int count = 0;

// using q0-q7 outputs from chip to wire seven segment display 
IC_74HC595 reg(OE_pin, MR_pin, DS_pin, SHCP_pin, STCP_pin, DELAY);

// array to load into register chip
bool* display = new bool[8]{};

void set_display(int currVal)  {
  switch (currVal)  {
    case 0:
      for (int i=0; i<6; i++) {
        display[i] = HIGH;
      }
      return;
    case 1:
      display[1] = HIGH; display[2] = HIGH;
      return;
    case 2:
      display[0] = HIGH; display[1] = HIGH;
      display[3] = HIGH; display[4] = HIGH;
      display[6] = HIGH;
      return;
    case 3:
      for (int i=0; i<4; i++) {
        display[i] = HIGH;
      }
      display[6] = HIGH;
      return;
    case 4:
      display[1] = HIGH; display[2] = HIGH;
      display[5] = HIGH; display[6] = HIGH; 
      return;
    case 5:
      display[0] = HIGH; display[2] = HIGH;
      display[3] = HIGH; display[5] = HIGH;
      display[6] = HIGH;
      return;
    case 6:
      display[0] = HIGH;
      for (int i=2; i<7; i++) {
        display[i] = HIGH;
      }
      return;
    case 7:
      for (int i=0; i<3; i++) {
        display[i] = HIGH;
      }
      return;
    case 8:
      for (int i=0; i<7; i++) {
        display[i] = HIGH;
      }
      return;
    case 9:
      for (int i=0; i<3; i++) {
        display[i] = HIGH;
      }
      display[5] = HIGH; display[6] = HIGH;
      return;
  }
}

void reset_display()  {
  for (int i=0; i<8; i++) {
    display[i] = LOW;
  }
}

void setup() {
  reg.setup();
  reset_display();
  set_display(0);
  reg.load_shiftReg(display, true);
  reg.load_storeReg();
}

void loop() {
  if (count > 9)  {
    count = 0;
  }
  set_display(count);
  reg.load_shiftReg(display, true);
  reg.load_storeReg();
  delay(1000); // second delay
  reset_display();
  count++;
}
