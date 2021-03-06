	/*

  WS2812B CPU and memory efficient library

  Date: 28.9.2016

  Author: Martin Hubacek
  	  	  http://www.martinhubacek.cz
  	  	  @hubmartin

  Licence: MIT License

*/

#ifndef VISEFFECT_H_
#define VISEFFECT_H_

#include <stdint.h>
#include "artnet/ProtocolSettings.h"
#include "stm32f4xx_hal.h"

// RGB Framebuffers
uint8_t frameBuffer[17][ARTNET_MAX_BUFFER+1];
uint8_t sendDMX;
UART_HandleTypeDef huart2;

void visInit(UART_HandleTypeDef huart);
void visHandle();
void sendDMXFrame(void);

#endif /* VISEFFECT_H_ */
