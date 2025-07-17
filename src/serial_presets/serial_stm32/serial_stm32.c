#ifdef STM32

#include "serial_stm32.h"
#include "../../serial.h"
#include <string.h>

UART_HandleTypeDef* serialHuart = NULL;
//Serial Variables
extern int serialConnection;
extern enum serialState serialState;
extern serialContext context;

#ifdef USE_UART4
extern UART_HandleTypeDef huart4;
#endif

bool openPortSTM32(void)
{
    if (serialHuart == NULL) return false;
    serialState = OPEN;
    return true;
}

bool closePortSTM32(void)
{
    serialState = CLOSED;
    return true;
}

int readSTM32(char *bytes, const uint16_t length)
{
    if (serialState != OPEN || serialHuart == NULL) return -1;
    HAL_StatusTypeDef result = HAL_UART_Receive(serialHuart, (uint8_t*)bytes, length, HAL_MAX_DELAY);
    return (result == HAL_OK) ? length : -1;
}

int writeSTM32(const char *data, const uint16_t length)
{
    if (serialState != OPEN || serialHuart == NULL) return -1;
    HAL_StatusTypeDef result = HAL_UART_Transmit(serialHuart, (uint8_t*)data, length, HAL_MAX_DELAY);
    return (result == HAL_OK) ? length : -1;
}

bool setContextSTM32(const char * port, const uint32_t baud){
    //Set baud
    context.serialBaud = baud;

    //Set serialHuart to determine whether context open or not
    #ifdef USE_UART4
    if(strcmp(port, "UART4") == 0){
        serialHuart = &huart4;
    }
    else{
        return false;
    }
    #endif

    //Set functions of context
    context.serialInit = openPortSTM32;
    context.serialDeInit = closePortSTM32;
    context.serialRead = readSTM32;
    context.serialWrite = writeSTM32;

    //Set port
    strncpy(context.serialPort, port, SERIAL_PORT_LENGTH);

    //Test if iit and deinit work
    if(context.serialInit() && context.serialDeInit())
        return true;

    //If test init and deinit don't pass, return false
    return false;

}

#endif