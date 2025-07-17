#ifndef SERIAL_STM32_H
#define SERIAL_STM32_H

#ifdef _cplusplus
extern "C"{
#endif

#include "stm32l4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Sets the serial communication context for a STM32 system.
 *
 * @param huart Reference to the UART handler
 * @param baud The baud rate for communication.
 * @return true if the context was set successfully, false otherwise.
 */
bool setContextSTM32(const char *port, const uint32_t baud);

#ifdef _cplusplus
}
#endif

#endif