#include<avr/io.h>
#include<util/delay.h>
#include<humidifier.h>
#include<bluetooth.h>
#include<button.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define ubrr ((F_CPU/BAUD)/16) -1

int main(void){
    humidifier_init();
    uart_init(ubrr);
    button_init();
    uint8_t state=0; //humidifier state 
    while(1){
        if(button_state()){
            _delay_ms(200);//debouncing the button press(to cancel out oscillation)
            state=!state;//not gate
            if(state){
                humidifier_on();
            }
            else{
                humidifier_off();
            }
        }
        if(UCSR0A & (1<<RXC0)){//checks if a byte is received
            char cmd = uart_receive(); //cmd stores the value of received data
            if(cmd == '1'){
                state=1;
                humidifier_on();
            }
            else if(cmd=='0'){
                state==0;
                humidifier_off();
            }
        }
    }    
}

