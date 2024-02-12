#include "IC_74HC595.h"

// Default constructor assigns pins 2-6, not recommended
IC_74HC595::IC_74HC595(): OE_pin(2), MR_pin(3), DS_pin(4), SHCP_pin(5), STCP_pin(6), DELAY(0) {} 

// Recommended contrsuctor since user defines pins
IC_74HC595::IC_74HC595(unsigned short OE_pin, unsigned short MR_pin, unsigned short DS_pin, 
                       unsigned short SHCP_pin, unsigned short STCP_pin, double DELAY): 
  OE_pin(OE_pin), MR_pin(MR_pin), DS_pin(DS_pin), SHCP_pin(SHCP_pin), STCP_pin(STCP_pin), DELAY(DELAY) {}

// Must be called within setup function in main file
void IC_74HC595::setup()  {
  pinMode(OE_pin, OUTPUT);
  pinMode(MR_pin, OUTPUT);
  pinMode(DS_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);

  digitalWrite(OE_pin, LOW);
  digitalWrite(MR_pin, LOW);
  digitalWrite(DS_pin, LOW);
  digitalWrite(SHCP_pin, LOW);
  digitalWrite(STCP_pin, LOW);

  this->clear_shiftReg();
}

void IC_74HC595::set_delay(double DELAY) {this->DELAY = DELAY;}

/*
  load the shift reg with 8 bit data in array form
  when data is shifted in and then stored, it is backwards in order
  the reverse parameter loads data in backwards order so it stored in the intended order
*/
void IC_74HC595::load_shiftReg(bool* reg, bool reverse=false)  {
  short bit_size = 8;
  digitalWrite(OE_pin, LOW);
  digitalWrite(MR_pin, HIGH);
  digitalWrite(SHCP_pin, LOW);

  if (reverse)  {
    for (short i=bit_size-1; i>=0; i--) {
      digitalWrite(DS_pin, reg[i]); 
      digitalWrite(SHCP_pin, LOW);
      delay(DELAY);
      digitalWrite(SHCP_pin, HIGH);
    }
    digitalWrite(SHCP_pin, LOW);
    return;
  }

  for (short i=0; i<bit_size; i++) {
    digitalWrite(DS_pin, reg[i]);
    digitalWrite(SHCP_pin, LOW); 
    delay(DELAY);
    digitalWrite(SHCP_pin, HIGH);
  }
  digitalWrite(SHCP_pin, LOW);
}

// the store reg is loaded with the current values of the shift reg
void IC_74HC595::load_storeReg() {
  digitalWrite(OE_pin, LOW);
  digitalWrite(MR_pin, HIGH);
  digitalWrite(STCP_pin, LOW);
  delay(DELAY);
  digitalWrite(STCP_pin, HIGH);
  digitalWrite(STCP_pin, LOW);
}

void IC_74HC595::clear_shiftReg()  {
  digitalWrite(MR_pin, HIGH);
  digitalWrite(MR_pin, LOW);
  delay(DELAY);
  digitalWrite(MR_pin, HIGH);
}

/* the current values of shift reg are moved to the store reg,
   the shift reg is cleared */
void IC_74HC595::move_shift_to_store() {
  digitalWrite(OE_pin, LOW);
  digitalWrite(STCP_pin, LOW);
  delay(DELAY);
  digitalWrite(STCP_pin, HIGH);
  digitalWrite(STCP_pin, LOW);
  digitalWrite(MR_pin, LOW);
}

void IC_74HC595::push_shiftReg(bool val=LOW)  {
  digitalWrite(OE_pin, LOW);
  digitalWrite(MR_pin, HIGH);
  digitalWrite(DS_pin, val);
  digitalWrite(SHCP_pin, LOW);
  delay(DELAY);
  digitalWrite(SHCP_pin, HIGH);
  digitalWrite(SHCP_pin, LOW);
}

void IC_74HC595::load_store_then_push_shift(bool val=LOW) {
  digitalWrite(OE_pin, LOW);
  digitalWrite(MR_pin, HIGH);
  digitalWrite(STCP_pin, LOW);
  delay(DELAY);
  digitalWrite(STCP_pin, HIGH);
  digitalWrite(STCP_pin, LOW);

  digitalWrite(DS_pin, val);
  digitalWrite(SHCP_pin, LOW);
  delay(DELAY);
  digitalWrite(SHCP_pin, HIGH);
  digitalWrite(SHCP_pin, LOW);
}