// STM32L432KC_RCC.h
// Header for RCC functions

#ifndef STM32L4_TIM15_H
#define STM32L4_TIM15_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TMI15_BASE (0x40021000UL) // base address of RCC

// PLL
#define PLLSRC_HSI 0
#define PLLSRC_HSE 1

// Clock configuration
#define SW_HSI  0
#define SW_HSE  1
#define SW_PLL  2

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
  __IO uint32_t CCMR1_OUTPUT;   /*!< TIM15 capture/compare mode register 1, output mode,        Address offset: 0x18 */
  __IO uint32_t CCMR1_INPUT;    /*!< TIM15 capture/compare mode register 1, input mode,         Address offset: 0x1C */
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

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM(TIM_TypeDef * TIM15);
void delay_millis(TIM_TypeDef * TIM15, uint32_t ms);

#endif