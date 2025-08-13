#include<avr/io.h>
#include<humidifier.h>
#define MOSFET_PIN PD4

void humidifier_init(void){
    DDRD |= (1<<MOSFET_PIN); //sets the PD4 that is D4 pin as output
    humidifier_off();
}
void humidifier_on(void){
    PORTD |= (1<<MOSFET_PIN); //sets the PD4 pin in port D high that the 4th bit is set high 
}
void humidifier_off(void){
    PORTD &= ~(1<<MOSFET_PIN); //sets the PD4 pin in port D LOW that the 4th bit is set LOW
}