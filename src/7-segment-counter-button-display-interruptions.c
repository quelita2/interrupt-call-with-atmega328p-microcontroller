#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int counter = 0;

void zero(){
  PORTB = 0b00000111;
  PORTD = 0b11101100;
}

void one(){
  PORTB = 0b00000001;
  PORTD = 0b00101100;
}

void two(){
  PORTB = 0b00001011;
  PORTD = 0b11001100;
}

void three(){
  PORTB = 0b00001011;
  PORTD = 0b01101100;
}

void four(){
  PORTB = 0b00001101;
  PORTD = 0b00101100;
}

void five(){  
  PORTB = 0b00001110;
  PORTD = 0b01101100;
}

void six(){
  PORTB = 0b00001110;
  PORTD = 0b11101100;
}

void seven(){
  PORTB = 0b00000011;
  PORTD = 0b00101100;
}


int main(void) {
  DDRB = 0b00001111;
  DDRD = 0b11110000;
  
  zero(); // starts counter with zero value and enable pull up setting

  EIMSK = 0b00000011; // enable INT0 and INT1 for external interruptions
  EICRA = 0b00001010; // configure INT0 and INT1 to falling endge
  
  sei();
  
  while(1){} // main process
  
  return 0;
}

ISR(INT1_vect) {
 void (*display_num[8])() = { zero, one, two, three, four, five, six, seven };

  if(counter <= 7){
    counter++;
    Serial.print(counter);
    display_num[counter]();  
  }
}

ISR(INT0_vect) {
 zero();
 counter = 0;
}