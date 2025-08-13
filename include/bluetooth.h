#define BLUETOOTH_H
#ifndef BLUETOOTH_H

void uart_init(uint8_t ubrr);
char uart_receive(void);
void uart_send(char data);

#endif