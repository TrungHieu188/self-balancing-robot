#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"
#include <stdint.h>

void       GPIO       (uint8_t port, uint8_t pinnumber, uint8_t mode, uint8_t submode);
uint8_t    ReadPin    (uint8_t port, uint8_t pinnumber);
uint16_t   ReadPort   (uint8_t port);
void       WritePin   (uint8_t port, uint8_t pinnumber, uint8_t data);
void       WritePort  (uint8_t port, uint16_t data);
void       TogglePin  (uint8_t port, uint8_t pinnumber);
//port

#define PORTA           0
#define PORTB           1
#define PORTC           2


//pin
#define PIN0             0
#define PIN1             1
#define PIN2             2
#define PIN3             3
#define PIN4             4
#define PIN5             5
#define PIN6             6
#define PIN7             7
#define PIN8             8
#define PIN9             9
#define PIN10            10
#define PIN11            11
#define PIN12            12
#define PIN13            13
#define PIN14            14
#define PIN15            15

//mode

#define INPUT           0
#define OUTPUT10        1
#define OUTPUT2         2
#define OUTPUT50        3


//submode

#define ANALOG          0 //input
#define FLOATING        1 //input
#define PUPD            2 //input
#define PP              3 //output
#define OD              4 //output
#define AFOPP           5 //output
#define AFOOD           6 //output




#endif
