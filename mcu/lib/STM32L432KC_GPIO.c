// STM32L432KC_GPIO.c
// Source code for GPIO functions

#include "STM32L432KC_GPIO.h"

void pinMode(GPIO_TypeDef * GPIO, int pin, int function) {
    switch(function) {
        case GPIO_INPUT:
            GPIO->MODER &= ~(0b11 << 2*pin);
            break;
        case GPIO_OUTPUT:
            GPIO->MODER |= (0b1 << 2*pin);
            GPIO->MODER &= ~(0b1 << (2*pin+1));
            break;
        case GPIO_ALT:
            GPIO->MODER &= ~(0b1 << 2*pin);
            GPIO->MODER |= (0b1 << (2*pin+1));
            break;
        case GPIO_ANALOG:
            GPIO->MODER |= (0b11 << 2*pin);
            break;
    }
}

int digitalRead(GPIO_TypeDef * GPIO, int pin) {
    return ((GPIO->IDR) >> pin) & 1;
}

void digitalWrite(GPIO_TypeDef * GPIO, int pin, int val) {
    GPIO->ODR |= (1 << pin);
}

void togglePin(GPIO_TypeDef * GPIO, int pin) {
    // Use XOR to toggle
    GPIO->ODR ^= (1 << pin);
}