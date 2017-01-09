/*

Copyright (c) Charles Yarnold charlesyarnold@gmail.com 2015

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, under version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

// Class for saving details to and for constructing pollreply packets

#include "PollReply.h"
#include "OpCodes.h"
#include "NodeReportCodes.h"
#include "StyleCodes.h"
#include "PriorityCodes.h"
#include "ProtocolSettings.h"
#include "config.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

struct replyPollPacket pollPacket;

void initPacket(){
	sprintf(pollPacket.ID, "Art-Net");
	pollPacket.OpCode = OpPollReply;
	memset(pollPacket.IPAddr, 0, sizeof(pollPacket.IPAddr));
	pollPacket.Port = 0x1936;
	pollPacket.VersionInfoHi = 0;
	pollPacket.VersionInfoLo = 1;
	pollPacket.NetSwitch = 0;
	pollPacket.SubSwitch = 0;
	pollPacket.Oem = 0x0190;
	pollPacket.UbeaVersion = 0;
	pollPacket.Status = 0;
	pollPacket.EstaMan[0] = 0;
	pollPacket.EstaMan[1] = 0;
	memset(pollPacket.ShortName, 0, sizeof(pollPacket.ShortName));
	sprintf(pollPacket.ShortName, HOSTNAME);
	memset(pollPacket.LongName, 0, sizeof(pollPacket.LongName));
	sprintf(pollPacket.LongName, HOSTNAME);
	memset(pollPacket.NodeReport, 0, sizeof(pollPacket.NodeReport));
	pollPacket.NumPortsHi = 0;
	pollPacket.NumPortsLo = 0;
	memset(pollPacket.PortTypes, 0, sizeof(pollPacket.PortTypes));
	memset(pollPacket.GoodInput, 0, sizeof(pollPacket.GoodInput));
	memset(pollPacket.GoodOutput, 0, sizeof(pollPacket.GoodOutput));
	memset(pollPacket.SwIn, 0, sizeof(pollPacket.SwIn));
	memset(pollPacket.SwOut, 0, sizeof(pollPacket.SwOut));
	pollPacket.SwVideo = 0;
	pollPacket.SwMacro = 0;
	pollPacket.SwRemote = 0;
	pollPacket.Spare1 = 0;
	pollPacket.Spare2 = 0;
	pollPacket.Spare3 = 0;
	pollPacket.Style = 0;
	pollPacket.Mac[0] = MACADDR0;
	pollPacket.Mac[1] = MACADDR1;
	pollPacket.Mac[2] = MACADDR2;
	pollPacket.Mac[3] = MACADDR3;
	pollPacket.Mac[4] = MACADDR4;
	pollPacket.Mac[5] = MACADDR5;
	memset(pollPacket.BindIp, 0, sizeof(pollPacket.BindIp));
	pollPacket.BindIndex = 0;
	pollPacket.Status2 = 0b00000000;
	pollPacket.Status2 = pollPacket.Status2 | 0b00000100;
	pollPacket.Status2 = pollPacket.Status2 | 0b00000010;
	memset(pollPacket.Filler, 0, sizeof(pollPacket.Filler));

	pollPacket.NetSwitch = 0 >> 8;
	pollPacket.SubSwitch = (0 & 0b000000011111111) >> 4;
}


//void PollReply::setIP(IPAddress IP){
//  packet.IPAddr[0] = IP[0];
//  packet.IPAddr[1] = IP[1];
//  packet.IPAddr[2] = IP[2];
//  packet.IPAddr[3] = IP[3];
//}
//
//void PollReply::setNumPorts(uint8_t num){
//  packet.NumPortsLo = num;
//}
//
//void PollReply::setSwOut(uint8_t id, uint16_t universe){
//  if(id > -1 && id < 4){
//    packet.SwOut[id] = universe & 0b0000000000001111;
//  }
//}
//
//void PollReply::setOutputEnabled(uint8_t port){
//  if(port >= 0 && port < 4){
//    packet.PortTypes[port] = packet.PortTypes[port] | 0b10000000;
//    packet.GoodOutput[port] = packet.GoodOutput[port] | 0b10000000;
//  }
//}
//
//void PollReply::setOutputDisabled(uint8_t port){
//  if(port >= 0 && port < 4){
//    packet.PortTypes[port] = packet.PortTypes[port] & (~0b10000000);
//    packet.GoodOutput[port] = packet.GoodOutput[port] & (~0b10000000);
//  }
//}
//
//void PollReply::setStartingUniverse(uint16_t startUniverse){
//  packet.NetSwitch = startUniverse >> 8;
//  packet.SubSwitch = (startUniverse & 0b000000011111111) >> 4;
//}
//
//uint8_t* PollReply::printPacket(){
//  return (uint8_t *)&packet;
//}
