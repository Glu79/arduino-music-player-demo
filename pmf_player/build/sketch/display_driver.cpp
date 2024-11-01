#line 1 "C:\\Users\\rwillekes\\Documents\\Stack\\Documents\\Persoonlijk\\ITM2M\\arduino-music-player-demo\\pmf_player\\display_driver.cpp"
#include "display_driver.h"


uint8_t lumi_cnt = 0;

void setup_disp() {
  //Set pins to outputs
  DDRD = X3|Y2|Y0|X2;
  DDRB = RST|Y1|X0|Y3|X1;
  
  //Timer 0 freeruns at clk I/O /256, CTC mode
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS02);
  TIMSK0 = _BV(OCIE0A);
  OCR0A = TC_UPD;
  OCR0B = TC_RES;

  //Display is updated at 400Hz (compare at +156)
  //For resetting pulse needs to be >250us (compare at +16)
}

//Clear display and/or enable COMPB interrupt if display needs to be written
ISR(TIMER0_COMPA_vect){
  (lumi_cnt < 3)?lumi_cnt++:lumi_cnt=0;

  if (lumi_cnt == 0) PORTD |= RST;
  if (lumi_cnt != 1) {
    TIMSK0 |= _BV(OCIE0B);
  } else TIMSK0 &= ~_BV(OCIE0B);
}

ISR(TIMER0_COMPB_vect){
  PORTD &= ~(RST);
  if (lumi_cnt < 2){
    //lumi_cmp = 3;
  } else if (lumi_cnt == 2){

  } else {  //lumi_cnt == 3

  }
}

/*void set_disp() {
  PORTB = 0;
  PORTD = X1|Y1;
  delay(1000);
  PORTB = RST;
  PORTD = 0;
  _delay_us(minRst);

  PORTB = X2;
  PORTD = Y1;
  delay(500);
  PORTB = RST;
  PORTD = 0;
  _delay_us(minRst);

  PORTB = X2|Y2;
  PORTD = 0;
  delay(250);
  PORTB = RST;
  PORTD = 0;
  _delay_us(minRst);

  PORTB = Y2;
  PORTD = X1;
  delay(100);
  PORTB = RST;
  PORTD = 0;
  _delay_us(minRst);      
}
*/
