/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for STMicroelectronics STM32 Nucleo64-F411RE board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_NUCLEO64_F411RE
#define BOARD_NAME                  "BlackPill WeAct F411CEU6"

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                25000000U
#endif

//#define STM32_HSE_BYPASS

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F411xE

#undef MODODEBUG

/*
 * IO pins assignments.
 */

#define GPIOA_PIN0                   0U
#define GPIOA_ADC                    1U
#define GPIOA_TX2                    2U
#define GPIOA_RX2                    3U
#define GPIOA_W25Q16_CS              4U
#define GPIOA_SPI1_SCK               5U
#define GPIOA_SPI1_MISO              6U
#define GPIOA_SPI1_MOSI              7U
#define GPIOA_TXRX1                  8U
#define GPIOA_TX1                    9U
#define GPIOA_RX1                   10U
#define GPIOA_TX6                   11U
#define GPIOA_RX6                   12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_OSCILADOR             15U

#define GPIOB_TXRX2                   0U
#define GPIOB_ENHM10                 1U
#define GPIOB_STHM10                 2U
#define GPIOB_I2C2SDA                3U
#define GPIOB_PIN4                   4U
#define GPIOB_PIN5                   5U
#define GPIOB_SENSOR                 6U
#define GPIOB_PIN7                   7U
#define GPIOB_PIN8                   8U
#define GPIOB_PIN9                   9U
#define GPIOB_I2C2SCL               10U
#define GPIOB_PIN11                 11U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_RELE2                 15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_LED_RELE1             13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.8
 */
#define LINE_ADC                    PAL_LINE(GPIOA, GPIOA_ADC)
#define LINE_TX2                    PAL_LINE(GPIOA, GPIOA_TX2)
#define LINE_RX2                    PAL_LINE(GPIOA, GPIOA_RX2)
#define LINE_W25Q16_CS              PAL_LINE(GPIOA, GPIOA_W25Q16_CS)
#define LINE_W25Q16_CLK             PAL_LINE(GPIOA, GPIOA_SPI1_SCK)
#define LINE_W25Q16_MISO            PAL_LINE(GPIOA, GPIOA_SPI1_MISO)
#define LINE_W25Q16_MOSI            PAL_LINE(GPIOA, GPIOA_SPI1_MOSI)
#define LINE_TX1                    PAL_LINE(GPIOA, GPIOA_TX1)
#define LINE_RX1                    PAL_LINE(GPIOA, GPIOA_RX1)
#define LINE_TXRX1                  PAL_LINE(GPIOA, GPIOA_TXRX1)
#define LINE_TX6                    PAL_LINE(GPIOA, GPIOA_TX6)
#define LINE_RX6                    PAL_LINE(GPIOA, GPIOA_RX6)
#define LINE_OSCILADOR              PAL_LINE(GPIOA, GPIOA_OSCILADOR)

#define LINE_SENSOR                 PAL_LINE(GPIOB, GPIOB_SENSOR)
#define LINE_TXRX2                  PAL_LINE(GPIOB, GPIOB_TXRX2)
#define LINE_ENHM10                 PAL_LINE(GPIOB, GPIOB_ENHM10)
#define LINE_STHM10                 PAL_LINE(GPIOB, GPIOB_STHM10)
#define LINE_I2C2SDA                PAL_LINE(GPIOB, GPIOB_I2C2SDA)
#define LINE_I2C2SCL                PAL_LINE(GPIOB, GPIOB_I2C2SCL)

#define LINE_LED_RELE1              PAL_LINE(GPIOC, GPIOC_LED_RELE1)
#define LINE_RELE2                  PAL_LINE(GPIOB, GPIOB_RELE2)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))


/*
 * GPIOA setup:
 * PA0  - GPIOA_PIN0                (input pullup).
 * PA1  - GPIOA_ADC                 (analog).
 * PA2  - GPIOA_TX2                 (alternate 7).
 * PA3  - GPIOA_RX2                 (alternate 7).
 * PA4  - GPIOA_W25Q16_CS           (output pushpull).
 * PA5  - GPIOA_SPI1_SCK            (alternate 5).
 * PA6  - GPIOA_SPI1_MISO           (alternate 5).
 * PA7  - GPIOA_SPI1_MOSI           (alternate 5).
 * PA8  - GPIOA_TXRX1               (output pushpull).
 * PA9  - GPIOA_TX1                 (alternate 7).
 * PA10 - GPIOA_RX1                 (alternate 7).
 * PA11 - GPIOA_TX6                 (alternate 8).
 * PA12 - GPIOA_RX6                 (alternate 8).
 * PA13 - GPIOA_SWDIO               (alternate 0).
 * PA14 - GPIOA_SWCLK               (alternate 0).
 * PA15 - GPIOA_OSCILADOR           (alternate 1).
 */


#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_PIN0) |         \
                                     PIN_MODE_ANALOG(GPIOA_ADC) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_TX2) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_RX2) |          \
                                     PIN_MODE_OUTPUT(GPIOA_W25Q16_CS) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_SCK) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MISO) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MOSI) |         \
                                     PIN_MODE_OUTPUT(GPIOA_TXRX1) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_TX1) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_RX1) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_TX6) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_RX6) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_OSCILADOR))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ADC) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TX2) |           \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RX2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_W25Q16_CS) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_SCK) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MISO) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MOSI) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TXRX1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TX1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RX1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TX6) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RX6) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OSCILADOR))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_PIN0) |    \
                                     PIN_OSPEED_HIGH(GPIOA_ADC) |        \
                                     PIN_OSPEED_HIGH(GPIOA_TX2) |          \
                                     PIN_OSPEED_HIGH(GPIOA_RX2) |         \
                                     PIN_OSPEED_HIGH(GPIOA_W25Q16_CS) |        \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_SCK) |        \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MISO) |        \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MOSI) |        \
                                     PIN_OSPEED_HIGH(GPIOA_TXRX1) |        \
                                     PIN_OSPEED_HIGH(GPIOA_TX1) |        \
                                     PIN_OSPEED_HIGH(GPIOA_RX1) |       \
                                     PIN_OSPEED_HIGH(GPIOA_TX6) |     \
                                     PIN_OSPEED_HIGH(GPIOA_RX6) |     \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_OSCILADOR))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP(GPIOA_PIN0) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_ADC) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_TX2) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_RX2) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_W25Q16_CS) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_SCK) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_MISO) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_MOSI) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_TXRX1) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_TX1) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_RX1) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_TX6) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_RX6) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_OSCILADOR))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PIN0) |           \
                                     PIN_ODR_LOW(GPIOA_ADC) |           \
                                     PIN_ODR_LOW(GPIOA_TX2) |           \
                                     PIN_ODR_LOW(GPIOA_RX2) |           \
                                     PIN_ODR_HIGH(GPIOA_W25Q16_CS) |           \
                                     PIN_ODR_HIGH(GPIOA_SPI1_SCK) |           \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MISO) |           \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MOSI) |           \
                                     PIN_ODR_HIGH(GPIOA_TXRX1) |           \
                                     PIN_ODR_HIGH(GPIOA_TX1) |           \
                                     PIN_ODR_HIGH(GPIOA_RX1) |           \
                                     PIN_ODR_HIGH(GPIOA_TX6) |        \
                                     PIN_ODR_HIGH(GPIOA_RX6) |        \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_OSCILADOR))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_ADC, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_TX2, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_RX2, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_W25Q16_CS, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_SPI1_SCK, 5U) |        \
                                     PIN_AFIO_AF(GPIOA_SPI1_MISO, 5U) |        \
                                     PIN_AFIO_AF(GPIOA_SPI1_MOSI, 5U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_TXRX1, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_TX1, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_RX1, 7U) |        \
                                     PIN_AFIO_AF(GPIOA_TX6, 8U) |    \
                                     PIN_AFIO_AF(GPIOA_RX6, 8U) |    \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_OSCILADOR, 1U))




/*
 * GPIOB setup:
 *
 * PB0  - GPIOB_TXRX2                  (output pushpull).
 * PB1  - GPIOB_ENHM10                 (output pushpull).
 * PB2  - GPIOB_STHM10                 (input).
 * PB3  - GPIOB_I2C2SDA                (alternate 9).
 * PB4  - GPIOB_PIN4                   (input analog).
 * PB5  - GPIOB_PIN5                   (input analog).
 * PB6  - GPIOB_SENSOR                 (input)
 * PB7  - GPIOB_PIN7                   (input)
 * PB8  - GPIOB_PIN8                   (input)
 * PB9  - GPIOB_PIN9                   (input).
 * PB10 - GPIOB_I2C2SCL                (alternate 4).
 * PB11 - GPIOB_PIN11                  (input analog).
 * PB12 - GPIOB_PIN12                  (input analog).
 * PB13 - GPIOB_PIN13                  (input analog).
 * PB14 - GPIOB_PIN14                  (input analog).
 * PB15 - GPIOB_RELE                   (input analog).
 */

#define GPIOB_TXRX2                   0U
#define GPIOB_ENHM10                 1U
#define GPIOB_STHM10                 2U
#define GPIOB_I2C2SDA                3U
#define GPIOB_PIN4                   4U
#define GPIOB_PIN5                   5U
#define GPIOB_SENSOR                 6U
#define GPIOB_PIN7                   7U
#define GPIOB_PIN8                   8U
#define GPIOB_PIN9                   9U
#define GPIOB_I2C2SCL               10U
#define GPIOB_PIN11                 11U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_RELE2                 15U

#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_TXRX2) |         \
                                     PIN_MODE_OUTPUT(GPIOB_ENHM10) |           \
                                     PIN_MODE_INPUT(GPIOB_STHM10) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C2SDA) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOB_SENSOR) |         \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN9) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C2SCL) |    \
                                     PIN_MODE_INPUT(GPIOB_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |          \
                                     PIN_MODE_OUTPUT(GPIOB_RELE2))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_TXRX2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ENHM10) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_STHM10) |     \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C2SDA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SENSOR) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |     \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C2SCL) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN11) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN12) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN13) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RELE2))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_TXRX2) |        \
                                     PIN_OSPEED_HIGH(GPIOB_ENHM10) |        \
                                     PIN_OSPEED_HIGH(GPIOB_STHM10) |        \
                                     PIN_OSPEED_HIGH(GPIOB_I2C2SDA) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN4) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN5) |        \
                                     PIN_OSPEED_HIGH(GPIOB_SENSOR) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN7) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN8) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN9) |        \
                                     PIN_OSPEED_HIGH(GPIOB_I2C2SCL) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN11) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN12) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN13) |        \
                                     PIN_OSPEED_HIGH(GPIOB_PIN14) |        \
                                     PIN_OSPEED_HIGH(GPIOB_RELE2))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_TXRX2) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_ENHM10) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_STHM10) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_I2C2SDA) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN5) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_SENSOR) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN7) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN8) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN9) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_I2C2SCL) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN11) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN12) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN13) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN14) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_RELE2))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_TXRX2) |           \
                                     PIN_ODR_HIGH(GPIOB_ENHM10) |           \
                                     PIN_ODR_HIGH(GPIOB_STHM10) |           \
                                     PIN_ODR_HIGH(GPIOB_I2C2SDA) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN5) |           \
                                     PIN_ODR_HIGH(GPIOB_SENSOR) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN7) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN8) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN9) |           \
                                     PIN_ODR_HIGH(GPIOB_I2C2SCL) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN11) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN12) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN13) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN14) |           \
                                     PIN_ODR_HIGH(GPIOB_RELE2))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_TXRX2, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_ENHM10, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_STHM10, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_I2C2SDA, 9U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN5, 2U) |        \
                                     PIN_AFIO_AF(GPIOB_SENSOR, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN9, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_I2C2SCL, 4U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN12, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN13, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_RELE2, 0U))
/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (input pullup).
 * PC0  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - PIN3                      (input pullup).
 * PC4  - PIN4                      (input pullup).
 * PC5  - PIN5                      (input pullup).
 * PC6  - PIN6                      (input pullup).
 * PC7  - PIN7                      (input pullup).
 * PC8  - PIN8                      (input pullup).
 * PC9  - PIN9                      (input pullup).
 * PC10 - PIN10                     (input pullup).
 * PC11 - PIN11                     (input pullup).
 * PC12 - PIN12                     (input pullup).
 * PC13 - GPIOC_LED_RELE1           (output pushpull high).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PIN0) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |         \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |          \
                                     PIN_MODE_OUTPUT(GPIOC_LED_RELE1) |         \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_RELE1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_PIN0) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN1) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN7) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN12) |         \
                                     PIN_OSPEED_MEDIUM(GPIOC_LED_RELE1) |        \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_PIN0) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN7) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_RELE1) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PIN0) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN12) |            \
                                     PIN_ODR_LOW(GPIOC_LED_RELE1) |           \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_LED_RELE1, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (input pullup).
 * PD1  - PIN1                      (input pullup).
 * PD2  - PIN2                      (input pullup).
 * PD3  - PIN3                      (input pullup).
 * PD4  - PIN4                      (input pullup).
 * PD5  - PIN5                      (input pullup).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - PIN8                      (input pullup).
 * PD9  - PIN9                      (input pullup).
 * PD10 - PIN10                     (input pullup).
 * PD11 - PIN11                     (input pullup).
 * PD12 - PIN12                     (input pullup).
 * PD13 - PIN13                     (input pullup).
 * PD14 - PIN14                     (input pullup).
 * PD15 - PIN15                     (input pullup).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (input pullup).
 * PE1  - PIN1                      (input pullup).
 * PE2  - PIN2                      (input pullup).
 * PE3  - PIN3                      (input pullup).
 * PE4  - PIN4                      (input pullup).
 * PE5  - PIN5                      (input pullup).
 * PE6  - PIN6                      (input pullup).
 * PE7  - PIN7                      (input pullup).
 * PE8  - PIN8                      (input pullup).
 * PE9  - PIN9                      (input pullup).
 * PE10 - PIN10                     (input pullup).
 * PE11 - PIN11                     (input pullup).
 * PE12 - PIN12                     (input pullup).
 * PE13 - PIN13                     (input pullup).
 * PE14 - PIN14                     (input pullup).
 * PE15 - PIN15                     (input pullup).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLUP(GPIOE_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input pullup).
 * PF1  - PIN1                      (input pullup).
 * PF2  - PIN2                      (input pullup).
 * PF3  - PIN3                      (input pullup).
 * PF4  - PIN4                      (input pullup).
 * PF5  - PIN5                      (input pullup).
 * PF6  - PIN6                      (input pullup).
 * PF7  - PIN7                      (input pullup).
 * PF8  - PIN8                      (input pullup).
 * PF9  - PIN9                      (input pullup).
 * PF10 - PIN10                     (input pullup).
 * PF11 - PIN11                     (input pullup).
 * PF12 - PIN12                     (input pullup).
 * PF13 - PIN13                     (input pullup).
 * PF14 - PIN14                     (input pullup).
 * PF15 - PIN15                     (input pullup).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLUP(GPIOF_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0U))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (input pullup).
 * PG1  - PIN1                      (input pullup).
 * PG2  - PIN2                      (input pullup).
 * PG3  - PIN3                      (input pullup).
 * PG4  - PIN4                      (input pullup).
 * PG5  - PIN5                      (input pullup).
 * PG6  - PIN6                      (input pullup).
 * PG7  - PIN7                      (input pullup).
 * PG8  - PIN8                      (input pullup).
 * PG9  - PIN9                      (input pullup).
 * PG10 - PIN10                     (input pullup).
 * PG11 - PIN11                     (input pullup).
 * PG12 - PIN12                     (input pullup).
 * PG13 - PIN13                     (input pullup).
 * PG14 - PIN14                     (input pullup).
 * PG15 - PIN15                     (input pullup).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_PULLUP(GPIOG_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input pullup).
 * PH3  - PIN3                      (input pullup).
 * PH4  - PIN4                      (input pullup).
 * PH5  - PIN5                      (input pullup).
 * PH6  - PIN6                      (input pullup).
 * PH7  - PIN7                      (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - PIN9                      (input pullup).
 * PH10 - PIN10                     (input pullup).
 * PH11 - PIN11                     (input pullup).
 * PH12 - PIN12                     (input pullup).
 * PH13 - PIN13                     (input pullup).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOH_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup).
 * PI1  - PIN1                      (input pullup).
 * PI2  - PIN2                      (input pullup).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - PIN9                      (input pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - PIN11                     (input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
