// STM32L432KC_TIM.c
// Source code for TIM functions

#include "STM32L432KC_TIM.h"
#include <math.h>
#include <stdio.h>

void initTIM(TIM_TypeDef * TIM, uint32_t prescaler) {
    
    // main output disable
    TIM->BDTR &= ~(1 << 15); // MOE, disable to prevent weird stuff while we change things

    // disable slave mode by turning all slave mode bits to zero in SMCR
    TIM->SMCR &= ~(0b111 << 0); // 0, 1, 2
    TIM->SMCR &= ~(1 << 16); // 16

    // set prescaler value
    TIM->PSC &= ~(0b1111111111111111 << 0); // PSC, reset all bits to 0
    TIM->PSC |= (prescaler << 0); // PSC, set prescaler value equal to inputted parameter

    // reset auto reload
    TIM->ARR &= ~(0b1111111111111111 << 0); // reset all bits

    // Make sure that the capture/compare channel is configured as an output
    TIM->CCMR1_OUTPUT &= ~(0b11 << 0); // CC1S = '00'

    // PWM output compare 1 mode
    // active when CNT < CCMR1 and inactive otherwise
    TIM->CCMR1_OUTPUT &= ~(0b111 << 4); // reset bits 6:4
    TIM->CCMR1_OUTPUT &= ~(1 << 16); // reset bit 16
    TIM->CCMR1_OUTPUT |= (0b100 << 4); // set bits 6:4
    TIM->CCMR1_OUTPUT |= (0b1 << 16); // set bit 16

    // enable preloaded register for comparison, we want to be able to change on update event
    TIM->CCMR1_OUTPUT |= (1 << 3); // OC1PE
    
    // enable capture/compare 1 output
    TIM->CCER |= (1 << 0); // CC1E
    TIM->CCER |= (1 << 2); // CC1NE (complementary output enable)
    TIM->CCER |= (1 << 1); // CC1P, active high polarity
    // the OC1N signal depends on MOE, OSSI, OSSR, OIS1, OIS1N, CC1E
    
    // generate update in order to reinitialize the counter
    // we don't want the counter to start at some unknown value
    TIM->EGR |= (1 << 0); // UG, set bit 0

    // enable counter
    TIM->CR1 |= (1 << 7); // enable use of shadow registers
    TIM->CR1 |= (1 << 0); // CEN

    // main output enable
    TIM->BDTR |= (1 << 15); // MOE, set to 1 to enable OC and OCN outputs
}


void delay_millis(TIM_TypeDef * TIM, uint32_t ms) {
    
    // calculate number of clock cycles it takes to get to 1 ms
    // based on a prescaler value of 19999, it takes 4 clock cycles to get to 1 ms
    // we can calculate arbritrary time in milliseconds using the number of clock cycles in 1 ms
    
    uint32_t clock_cycles_ms = round((CLOCK_SPEED * 0.001 * pow(10, 6))/(PRESCALER_DELAY + 1));
    uint32_t clock_cycles_delay = 4 * ms;

    // the counter is compared to CCR1
    // we need to set it to the appropriate number of milliseconds
    TIM->CCR1 &= ~(0b1111111111111111 << 0); // reset all bits
    TIM->CCR1 |= (clock_cycles_delay << 0); // set to calculated value

    // the counter resets once it reaches the auto reload value.
    // set auto reload value to appropriate number of milliseconds
    TIM->ARR &= ~(0b1111111111111111 << 0); // reset all bits
    TIM->ARR |= (clock_cycles_delay << 0); // set to calculated value

    // generate update in order to reinitialize the counter
    // we don't want the counter to start at some unknown value
    TIM->EGR |= (1 << 0); // UG, set bit 0

    // now we need to wait until we reach CNT = CCRN, this triggers bit 1 of the status register
    while((TIM->SR >> 1 & 1) == 0);

    return;
}


void set_frequency(TIM_TypeDef * TIM, uint32_t freq) {
    
    // if frequency is zero, then don't play anything
    if (freq == 0) {
        // disable counter so that nothing happens
        TIM->CR1 &= ~(1 << 0); // CEN
    }
    else {    
        // calculate number of clock cycles it takes to output desired frequency
        uint32_t clock_cycles = round((CLOCK_SPEED * pow(10, 6))/(freq * (PRESCALER_SOUND + 1)));
        // calculate when to switch off based on duty cycle
        uint32_t toggle_point = round(clock_cycles * DUTY_CYCLE);

        // the counter is compared to CCR1
        // we switch the signal off when it reaches the toggle point
        TIM->CCR1 &= ~(0b1111111111111111 << 0); // reset all bits
        TIM->CCR1 |= (toggle_point << 0); // set to calculated value

        // the counter resets once it reaches the auto reload value.
        // we turn the signal back on when it reaches the auto reload value
        TIM->ARR &= ~(0b1111111111111111 << 0); // reset all bits
        TIM->ARR |= (clock_cycles << 0); // set to calculated value

        // generate update in order to reinitialize the counter
        // we don't want the counter to start at some unknown value
        TIM->EGR |= (1 << 0); // UG, set bit 0

        // make sure counter is enabled
        TIM->CR1 |= (1 << 0); // CEN
    }

    return;
}