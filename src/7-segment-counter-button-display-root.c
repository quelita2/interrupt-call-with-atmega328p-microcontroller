#include <util/delay.h>

unsigned const int A = 9; // B
unsigned const int B = 8; // B
unsigned const int C = 5; // D
unsigned const int D = 6; // D
unsigned const int E = 7; // B
unsigned const int F = 10;// B
unsigned const int G = 11;// B
unsigned const int H = 4; // D

unsigned const int PIN_BUTTON_COUTER = 3;
unsigned const int PIN_BUTTON_RESET = 2;

unsigned int STATE_BUTTON_COUTER = 0;
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

int main(void){
  Serial.begin(9600);
  DDRD = 0b11110000;
  DDRB = 0b00001111;
  
  zero(); // start display with zero;
  
  void (*display_num[8])() = {zero, one, two, three, four, five, six, seven};

  int enable_count = 1;
  
  while(1){
    if((!(PIND & 0x08) && counter < 7) && enable_count == 1){ 
      counter++;
      Serial.print(counter);
      display_num[counter]();
      enable_count = 0;
    }else if((PIND & 0x08)){
      enable_count = 1;
    }
    
    if(!(PIND & 0x04)){
      zero();
      counter = 0;
    }
  }
  
  return 0;
}