#include<avr/io.h>
#include<button.h>

#define BUTTON_PIN PD2

void button_init(void){
    DDRD &= ~(1<<BUTTON_PIN);
    PORTD |= (1<<BUTTON_PIN);
}

uint8_t button_state(void){
    return !(PIND & (1<<BUTTON_PIN));
}