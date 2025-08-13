#include<avr/io.h>
#include<bluetooth.h>

void uart_init(uint8_t ubrr){
    UBRR0H= (ubrr>>8);
    UBRR0L=(ubrr); //baudrate
    UCSR0B=(1<<RXEN0)|(1<<TXEN0); //control register B for switching receiver and transmitter
    UCSR0C=(1<< UCSZ01)|(1<<UCSZ00);//control frame size 

}

char uart_receive(void){
    while (!(UCSR0A & (1<<RXC0))); //to check whether data is received and loop will wait until it is, RXC0 bit is set after data is received
    return UDR0; //returns the data, UDR0 reads data
}

char uart_send(char data){
    while (!(UCSR0A &(1<<UDRE0)));// checks whether ready to send new data, UDRE0 is set if data is ready to be sent 
    UDR0 = data; //
}