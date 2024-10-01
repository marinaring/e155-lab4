// main.c
// Play music from the starter file
// Marina Ring
// mring@hmc.edu
// 9/30/24

// TODO: Add #includes
#include "STM32L432KC_TIM.h"
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

    // Configure timers (declare)
    initTIM(TIM15, 999); // song frequency timer
    initTIM(TIM16, 19999); // rest delay timer

    // Turn on clock to GPIOB
    RCC->AHB2ENR |= (1 << 1);

    // Set LED_PIN as output
    pinMode(SONG_PIN, GPIO_OUTPUT);

    // play music
    for (size_t i = 0; i < (sizeof(notes)/(2*sizeof(int))); i++) {
        
        // get frequency and rest length
        int frequency = notes[i][0];
        int rest = notes[i][1];

        // if frequency is zero, then don't play anything
        if (frequency == 0) {
            TIM15->

        }
        else {
            // calculate number of clock cycles for auto reload and CCRN
            int

            // set auto reload and CCRN

            // delay appropriate amount
        }

        
    }

    return 0;
}