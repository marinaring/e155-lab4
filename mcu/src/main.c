// main.c
// Play music from the starter file
// Marina Ring
// mring@hmc.edu
// 9/30/24

// TODO: Add #includes
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_GPIO.h"
#include <math.h>

#define SONG_PIN 3

// Fur Elise, E155 Lab 4
// Pitch in Hz, duration in ms
const int notes[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	0}};

int main(void) {

    // Configure Flash
    configureFlash();

    // Configure clock
    configureClock();

    // Configure timers 
    initTIM(TIM15, PRESCALER_SOUND); // song frequency timer
    initTIM(TIM16, PRESCALER_DELAY); // rest delay timer

    // Configure pin for frequency output
    GPIOA->AFRL &= ~(0b1111 << 0); // reset all bits
    GPIOA->AFRL |= (1110 << 8); // set GPIOA Pin 2 to AF14 
    pinMode(GPIOA, SONG_PIN, GPIO_OUTPUT); // set pin mode to output

    // play music
    for (size_t i = 0; i < (sizeof(notes)/(2*sizeof(int))); i++) {
        
        // get frequency and rest length
        int frequency = notes[i][0];
        int delay = notes[i][1];

        set_frequency(TIM15, frequency); // set frequency so right note is being played
        delay_millis(TIM16, delay); // wait appropriate duration
    }

    return 0;
}