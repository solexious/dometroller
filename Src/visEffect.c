/*

  WS2812B CPU and memory efficient library

  Date: 28.9.2016

  Author: Martin Hubacek
  	  	  http://www.martinhubacek.cz
  	  	  @hubmartin

  Licence: MIT License

*/

#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "ws2812b/ws2812b.h"
#include "artnet/ProtocolSettings.h"
#include <stdlib.h>

// RGB Framebuffers
uint8_t frameBuffer[17][ARTNET_MAX_BUFFER];

// Helper defines
#define newColor(r, g, b) (((uint32_t)(r) << 16) | ((uint32_t)(g) <<  8) | (b))
#define Red(c) ((uint8_t)((c >> 16) & 0xFF))
#define Green(c) ((uint8_t)((c >> 8) & 0xFF))
#define Blue(c) ((uint8_t)(c & 0xFF))

void visInit(){
	for(int a = 0; a < 16; a++){
		for(int b = 0; b < ARTNET_MAX_BUFFER; b++){
			frameBuffer[a][b] = 0;
		}
	}
	// If you need more parallel LED strips, increase the WS2812_BUFFER_COUNT value
	for(uint8_t i = 0; i < WS2812_BUFFER_COUNT; i++)
	{
		// Set output channel/pin, GPIO_PIN_0 = 0, for GPIO_PIN_5 = 5 - this has to correspond to WS2812B_PINS
		ws2812b.item[i].channel = i;
		// Your RGB framebuffer
		ws2812b.item[i].frameBufferPointer = frameBuffer[i];
		// RAW size of framebuffer
		ws2812b.item[i].frameBufferSize = sizeof(frameBuffer[i]);

	}
	ws2812b_init();
}


void visHandle(){
	if(ws2812b.transferComplete){
		// Signal that buffer is changed and transfer new data
		ws2812b.startTransfer = 1;
		ws2812b_handle();
	}
}


