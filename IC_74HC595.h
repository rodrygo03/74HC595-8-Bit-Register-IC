# ifndef IC_74HC595_H
# define IC_74HC595_H

class IC_74HC595 {
/*
  Consist of two registers:
    data passes through the shift reg and is stored in the store reg
  Delay: acts as the clock period for the registers
  PINS:
    SHCP_pin: shift register clock
    STCP_pin: storage register clock
    DS: serial input to shift register
    (OE)': enable parallel data output
    (MR)': master reset; clear shift register
    ...see datasheet                  
*/
  unsigned short OE_pin;
  unsigned short MR_pin;
  unsigned short DS_pin;
  unsigned short SHCP_pin;
  unsigned short STCP_pin;
  double DELAY; 

  public:
    IC_74HC595();
    IC_74HC595(unsigned short OE_pin, unsigned short MR_pin, unsigned short DS_pin, unsigned short SHCP_pin, unsigned short STCP_pin, double DELAY);
    void clear_shiftReg(); 
    void load_shiftReg(bool* reg, bool reverse=false); 
    void load_store_then_push_shift(bool val=LOW);
    void load_storeReg();
    void move_shift_to_store(); 
    void push_shiftReg(bool val=LOW); 
    void setup(); 
    void set_delay(double DELAY);                              
};

# endif
