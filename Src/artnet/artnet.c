/*

  Charles Yarnold Artnet library

*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../visEffect.h"
#include "lwip.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "lwip/ip.h"
#include <string.h>
#include <stdio.h>
#include "OpCodes.h"
#include "NodeReportCodes.h"
#include "StyleCodes.h"
#include "PriorityCodes.h"
#include "ProtocolSettings.h"
#include "PollReply.h"

//struct udp_pcb *upcb;

void udp_artnet_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

void artnetInit(void){
	   struct udp_pcb *upcb;
	   err_t err;

	   /* Create a new UDP control block  */
	   upcb = udp_new();

	   if (upcb)
	   {
	     /* Bind the upcb to the UDP_PORT port */
	     /* Using IP_ADDR_ANY allow the upcb to be used by any local interface */
	      err = udp_bind(upcb, IP_ADDR_ANY, ARTNET_PORT);

	      if(err == ERR_OK)
	      {
	        /* Set a receive callback for the upcb */
	        udp_recv(upcb, udp_artnet_receive_callback, NULL);
	      }
	   }

	   initPacket();
}

void udp_artnet_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port){
	/* Check packet length isn't bigger than ARTNET_MAX_BUFFER */
	if(p->len > ARTNET_MAX_BUFFER){
		return;
	}

	/* Change payload to array */
	uint8_t *buf = (uint8_t *)p->payload;

	/* Check start of payload == "Art-net" */
	for(int i = 0; i < 8; i++){
		if(buf[i] != ARTNET_ID[i]){
			return;
		}
	}

	/* Check if data or pollreply request */
	uint16_t opcode = buf[8] | buf[9] << 8;

	/* if pollreply, craft packet and respond */
	if(opcode == OpPoll){
		/* Generate payload */

		/* Connect and send to requesting IP */
		struct pbuf *ps;

		/* allocate pbuf from pool*/
		int len = sizeof(pollPacket);
		unsigned char * raw = malloc(len);
		memcpy(raw, &pollPacket, len);

		ps = pbuf_alloc(PBUF_TRANSPORT, len , PBUF_POOL);

		if (ps != NULL)
		{
			/* copy data to pbuf */
			pbuf_take(ps, raw, len);

			/* send udp data */
			udp_sendto(upcb, ps, addr, ARTNET_PORT);

			/* free pbuf */
			pbuf_free(ps);
		}
	}

	/* if data, sanitise and send to correct buffer */
	else if(opcode == OpDmx){
		/* Check not broadcast */
		if(getOurIP() == ip_current_dest_addr()->addr){
			/* Extract DMX and store in buffer */
			// Get universe
			uint16_t universe = buf[14] | buf[15] << 8;
			if(universe > 16){
				return;
			}

			if(universe == 16){
				// Get DMX frame length
				uint16_t dmxDataLength = buf[17] | buf[16] << 8;

				for (int i = 0 ; i < dmxDataLength ; i++){
					if(i < dmxDataLength){
						frameBuffer[universe][i+1] = buf[i+ARTNET_DMX_START_LOC];
					}
					else{
						frameBuffer[universe][i+1] = 0;
					}
				}
				sendDMX = 1;
			}
			else{
				// Get DMX frame length
				uint16_t dmxDataLength = buf[17] | buf[16] << 8;

				for (int i = 0 ; i < dmxDataLength ; i++){
					if(i < dmxDataLength){
						frameBuffer[universe][i] = buf[i+ARTNET_DMX_START_LOC];
					}
					else{
						frameBuffer[universe][i] = 0;
					}
				}
			}
		}
	}

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb);

	/* Free the p buffer */
	pbuf_free(p);
}
