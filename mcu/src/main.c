// main.c
// Play music from the starter file
// Marina Ring
// mring@hmc.edu
// 9/30/24

#include "../lib/STM32L432KC_TIM.h"
#include "../lib/STM32L432KC_RCC.h"
#include "../lib/STM32L432KC_GPIO.h"
#include "../lib/STM32L432KC_FLASH.h"
#include <math.h>

#define SONG_PIN 6

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

const float september[][2] = {
  {370.0, 0.0625}, // F4#, eighth
  {440, 0.0625},   // A4, eighth
  {493.9, 0.0625}, // B4, eighth
  {554.4, 0.0625}, // C5#, eighth
  {554.4, 0.0625}, // C5#, 1/8 + 1/4
  {0, 0.1875},     // rest, 1/8 + 1/4
  {370.0, 0.0625}, // F4#, eighth
  {554.4, 0.0625}, // C5#, eighth
  {659.2, 0.0625}, // E5, eighth
  {740.9, 0.0625}, // F5#, eighth
  {493.9, 0.0625}, // B4, eighth
  {440, 0.125},    // A4, quarter
  {370.0, 0.0625}, // F4#, eighth
  {554.4, 0.1875}, // C5#, 1/8 + 1/4
  {0, 500},        // rest, whole
  {440, 0.0625},   // A4, eighth
  {493.9, 0.0625}, // B4, eighth
  {554.4, 0.0625}, // C5# eighth
  {659.2, 0.0625}, // E5 eighth
  {740.9, 0.0625}, // F5# eighth
  {493.9, 0.0625}, // B4, eighth
  {440, 0.125},    // A4, quarter
  {370.0, 0.0625}, // F4#, eighth
  {554.4, 0.1875}, // C5#, 1/8 + 1/4
  {0, 0.5},        // rest, whole
  {440, 0.0625},   // A4, eighth
  {493.9, 0.0625}, // B4, eighth
  {554.4, 0.0625}, // C5#, eighth
  {659.2, 0.0625}, // E5, eighth
  {740.9, 0.0625}, // F5#, eighth
  {493.9, 0.03125}, // B4, sixteenth
  {554.4, 0.03125}, // C5#, sixteenth,
  {493.9, 0.125},    // B4, quarter
  {440, 0.0625},   // A4, eight
  {493.9, 0.0625}, // B4, eight, 
  {440, 1}        // A4, whole, whole
};

const int test_notes[][2] = {
{220, 3000},
{0, 1000},
{1000, 3000},
{0, 1000},
{220, 3000}
};

int main(void) {
    // Configure flash
    configureFlash();

    // Configure clock
    configureClock();

    // Enable peripheral clocks
    RCC->APB2ENR |= (1 << 17); // TIM16EN
    RCC->APB2ENR |= (1 << 16); // TIM15EN
    RCC->AHB2ENR |= (1 << 0); // GPIOA

    // Set up clock for timers
    // Set APB1, APB2 and AHB prescalers
    RCC->CFGR &= ~(0b111 << 8); // PPRE1, APB1, Clear all bits
    RCC->CFGR &= ~(0b1111 << 4); // HPRE, AHB, Clear all bits
    RCC->CFGR &= ~(0b111 << 11); // PPRE2, APB2, Clear all bits

    // Configure timers 
    initTIM(TIM16, PRESCALER_SOUND); // song frequency timer
    initTIM(TIM15, PRESCALER_DELAY); // rest delay timer

    // Configure pin for frequency output
    pinMode(GPIOA, SONG_PIN, GPIO_ALT);

    // TIM16 can be connected to PA6 by setting AF14
    GPIOA->AFRL &= ~(0b1111 << 4*SONG_PIN); // reset all bits in corresponding GPIOA
    GPIOA->AFRL |= (0b1110 << 4*SONG_PIN); // set corresponding GPIOA for TIM16 (PA6) to AF14 
    GPIOA->OSPEEDR |= (0b11 << 2*SONG_PIN); // set speed to very fast
    

    //set_frequency(TIM16, 220);
    // play music
    for (int i = 0; i < (sizeof(september)/(2*sizeof(float))); i++) {
        
        // get frequency and rest length
        float frequency = september[i][0];
        int delay = september[i][1];

        set_frequency(TIM16, frequency); // set frequency so right note is being played
        delay_millis(TIM15, delay); // wait appropriate duration
    }

    // keep it in this loop until system reset so that it doesn't keep cycling through
    while(1);

    return 0;
}