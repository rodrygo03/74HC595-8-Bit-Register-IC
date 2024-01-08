#include "IC_74HC595.h"

// using LEDs to test output 
unsigned short OE_pin = 2;
unsigned short MR_pin = 4;
unsigned short DS_pin = 7;
unsigned short SHCP_pin = 12;
unsigned short STCP_pin = 13;
double DELAY = 0;
IC_74HC595 reg(OE_pin, MR_pin, DS_pin, SHCP_pin, STCP_pin, DELAY);

bool* data1 = new bool[8] {HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW};
bool* data2 = new bool[8] {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
bool* data3 = new bool[8] {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH};
bool* data4 = new bool[8] {LOW, LOW, HIGH, HIGH, LOW, HIGH, LOW, LOW};

void shift_to_store_test1(bool* data)  {
  reg.load_shiftReg(data);
  reg.load_storeReg();
  delay(3000);
  reg.clear_shiftReg();
}

void shift_to_store_test2(bool* data) {
  reg.load_shiftReg(data);
  reg.move_shift_to_store();
  delay(3000);
}

void push_to_shift_to_store_test1() {
  for (int i=0; i<8; i++) {
    reg.push_shiftReg(HIGH);
  }
  reg.load_storeReg();
  delay(3000);
  reg.clear_shiftReg();
}

void push_to_shift_to_store_test2() {
  bool* temp = new bool[8]  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
  reg.push_shiftReg(HIGH);
  reg.move_shift_to_store();
  delay(3000);
}

void load_to_shift_load_store_push_shift1(bool* data) {
  reg.load_shiftReg(data, true);
  //reg.load_store_then_push_shift(HIGH);
  delay(1000);
  reg.move_shift_to_store();
  delay(3000);
}

void load_to_shift_load_store_push_shift2(bool* data) {
  reg.load_shiftReg(data, true);
  //reg.load_store_then_push_shift();
  delay(1000);
  reg.load_storeReg();
  delay(3000);
  reg.clear_shiftReg();
}

void setup()  {
  reg.setup();
}

void loop() {
  shift_to_store_test1(data1);
  shift_to_store_test2(data1);
  push_to_shift_to_store_test1();
  push_to_shift_to_store_test2();
  load_to_shift_load_store_push_shift1(data2);
  load_to_shift_load_store_push_shift2(data2);

  reg.set_delay(0.050); 

  shift_to_store_test1(data3);
  shift_to_store_test2(data3);
  push_to_shift_to_store_test1();
  push_to_shift_to_store_test2();
  load_to_shift_load_store_push_shift1(data4);
  load_to_shift_load_store_push_shift2(data4);
}
