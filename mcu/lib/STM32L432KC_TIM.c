// STM32L432KC_TIM.c
// Source code for TIM functions

#include "STM32L432KC_TIM.h"

void initTIM() {
    
    // do I need to wait for the CC1OF flag? Bit 0 of the status register (SR)
    // do I need to wait for the UIF flag? Bit 0 of the status register (SR)
    // Main output enable (MOE) set to 1 for OC and OCN outputs , bit 15 < 1
    // CCR1 bits 15:0 capture/compare 1 value, the value that will be compared to the counter
    // PSC, bits 15:0 prescaler value, counter clock frequency (CK_CNT) is equal to f_CK_PSC/(PSC[15:0] + 1)
    // CCER, bit 0, 1: OC1 signal is output on the corresponding output pin 
    // CCMR1, OC1M: 0011, toggle OC1REF when TIM_CNT  = TIM_CCR1
    // 

    // OCxM bits in the TIMx_CCMR define output compare mode
    // CCxP bit in the TIMx_CCER defines output polarity

    // 1. set the counter clock (internal, external, prescaler)
    // 2. write the desired data in the TIMx_ARR and TIMx_CCRx registers
    // 3. set the CCxIE bit if an interrupt request is to be generated
    // 4. set the output mode. 
    // Write OCxM = 011 to toggle OCx output pin when CNT matches CCRx
    // Write OCxPE = 0 to disable preload register
    // Write CCxP = 0 to select active high polarity
    // Write CCxE = 1 to enable the output
    // 5. Enable the counter by setting the CEN bit in the TIMx_CR1 register


    // ?? should I disable the timer first

    // disable slave mode by turning all slave mode bits to zero in SMCR
    TIM15->SMCR &= ~(0b111 << 0); // 0, 1, 2
    TIM15->SMCR &= ~(1 << 16); // 16

    // LOCK level 3 has been programmed 
    TIM15->BDTR

    // Make sure that the capture/compare channel is configured as an output
    TIM15->CCMR1_OUTPUT &= ~(0b11 << 0); // set CC1S = '00'

    // toggle output compare 1 mode
    TIM15->CCMR1_OUTPUT &= ~(0b111 << 4); // reset bits 6:4
    TIM15->CCMR1_OUTPUT &= ~(1 << 16); // reset bit 16
    TIM15->CCMR1_OUTPUT |= (0b011 << 4); // set bits 6:4

    // disable preloaded register for comparison, we want to load in our own value
    TIM15->CCMR1_OUTPUT &= ~(1 << 3); // bit 3, OC1PE

    // Set output polarity
    TIM15->CCER 

    
    // enable counter by setting bit 0 (CEN) to 1
    TIM15->CR1 |= (1 << 0);
    
}

