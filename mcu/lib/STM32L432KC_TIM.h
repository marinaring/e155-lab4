// STM32L432KC_RCC.h
// Header for RCC functions

#ifndef STM32L4_TIM15_H
#define STM32L4_TIM15_H

#include <stdint.h>
#include <math.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////
#define __IO volatile

// Base addresses
#define TIM15_BASE (0x40014000UL) // base address of TIM15
#define TIM16_BASE (0x40014400UL) // base address of TIM16

// Clock configuration
#define CLOCK_SPEED 80 // Clock speed in MHz
#define PRESCALER_DELAY 1999 // The prescaler used for the delay timer
#define PRESCALER_SOUND 699 // The prescaler used for the sound frequency timer

// Timer configuration
#define DUTY_CYCLE 0.5 // duty cycle for the sounds we play

/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR1;            /*!< TIM15 control register 1,                                  Address offset: 0x00 */
  __IO uint32_t CR2;            /*!< TIM15 control register 2,                                  Address offset: 0x04 */
  __IO uint32_t SMCR;           /*!< TIM15 slave mode control register,                         Address offset: 0x08 */
  __IO uint32_t DIER;           /*!< TIM15 DMA/interrupt enable register,                       Address offset: 0x0C */
  __IO uint32_t SR;             /*!< TIM15 status register,                                     Address offset: 0x10 */
  __IO uint32_t EGR;            /*!< TIM15 event generation register,                           Address offset: 0x14 */
  __IO uint32_t CCMR1;   /*!< TIM15 capture/compare mode register 1, output mode,        Address offset: 0x18 */
  uint32_t      RESERVED0;    /*!< TIM15 capture/compare mode register 1, input mode,         Address offset: 0x1C */
  __IO uint32_t CCER;           /*!< TIM15 capture/compare enable register,                     Address offset: 0x20 */
  __IO uint32_t CNT;            /*!< TIM15 counter,                                             Address offset: 0x24 */
  __IO uint32_t PSC;            /*!< TIM15 prescaler,                                           Address offset: 0x28 */
  __IO uint32_t ARR;            /*!< TIM15 auto-reload register,                                Address offset: 0x2C */
  __IO uint32_t RCR;            /*!< TIM15 repetition counter register,                         Address offset: 0x30 */
  __IO uint32_t CCR1;           /*!< TIM15 capture/compare register 1,                          Address offset: 0x34 */
  __IO uint32_t CCR2;           /*!< TIM15 capture/compare register 2,                          Address offset: 0x38 */
  uint32_t      RESERVED1;      /*!< Reserved,                                                  Address offset: 0x3C */
  uint32_t      RESERVED2;      /*!< Reserved,                                                  Address offset: 0x40 */
  __IO uint32_t BDTR;           /*!< TIM15 break and dead-time register,                        Address offset: 0x44 */
  __IO uint32_t DCR;            /*!< TIM15 DMA control register,                                Address offset: 0x48 */
  __IO uint32_t DMAR;           /*!< TIM15 DMA address for full transfer,                       Address offset: 0x4C */
  __IO uint32_t OR1;            /*!< TIM15 option register 1,                                   Address offset: 0x50 */
  __IO uint32_t RESERVED3;      /*!< RCC APB1 peripheral clocks enable register 2,              Address offset: 0x54 */
  uint32_t      RESERVED4;      /*!< Reserved,                                                  Address offset: 0x58 */
  __IO uint32_t RESERVED5;      /*!< Reserved,                                                  Address offset: 0x5C */
  __IO uint32_t OR2;            /*!< TIM15 option register 2,                                   Address offset: 0x60 */
} TIM_TypeDef;

#define TIM15 ((TIM_TypeDef *) TIM15_BASE)
#define TIM16 ((TIM_TypeDef *) TIM16_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM(TIM_TypeDef * TIM, uint32_t prescaler);
void delay_millis(TIM_TypeDef * TIM, uint32_t ms);
void set_frequency(TIM_TypeDef * TIM, uint32_t freq);

#endif