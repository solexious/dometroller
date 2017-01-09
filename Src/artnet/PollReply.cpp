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

#include <PollReply.h>

replyPollPacket pollPacket;

void initPacket(){
	pollPacket.ID[8] = "Art-Net"; // protocol ID = "Art-Net";
	//  //char ID[8]; // protocol ID = "Art-Net"
	pollPacket.OpCode = OpPollReply; // == OpPollReply
	//  uint8_t IPAddr[4]; // 0 if not yet configured
	pollPacket.Port = 0x1936;
	//
	pollPacket.VersionInfoHi = 0; // The node's current FIRMWARE VERS hi
	pollPacket.VersionInfoLo = 1; // The node's current FIRMWARE VERS lo
	//
	pollPacket.NetSwitch = 0; // Bits 14-8 of the 15 bit universe number are encoded into the bottom 7 bits of this field.
	//  // This is used in combination with SubSwitch and Swin[] or Swout[] to produce the full universe address.
	pollPacket.SubSwitch = 0; // Bits 7-4 of the 15 bit universe number are encoded into the bottom 4 bits of this field.
	//  // This is used in combination with NetSwitch and Swin[] or Swout[] to produce the full universe address.
	//
	pollPacket.Oem = 0x0190; // Manufacturer code, bit 15 set if
	//  // extended features avail
	//
	pollPacket.UbeaVersion = 0; // Firmware version of UBEA
	//
	pollPacket.Status = 0;
	//  // bit 0 = 0 UBEA not present
	//  // bit 0 = 1 UBEA present
	//  // bit 1 = 0 Not capable of RDM (Uni-directional DMX)
	//  // bit 1 = 1 Capable of RDM (Bi-directional DMX)
	//  // bit 2 = 0 Booted from flash (normal boot)
	//  // bit 2 = 1 Booted from ROM (possible error condition)
	//  // bit 3 = Not used
	//  // bit 54 = 00 Universe programming authority unknown
	//  // bit 54 = 01 Universe programming authority set by front panel controls
	//  // bit 54 = 10 Universe programming authority set by network
	//  // bit 76 = 00 Indicators Normal
	//  // bit 76 = 01 Indicators Locate
	//  // bit 76 = 10 Indicators Mute
	//
	pollPacket.EstaMan[2] = {0, 0};      // ESTA manufacturer id, lo byte
	//
	pollPacket.ShortName[18] = "ElLab Artnetnode\0"; // short name defaults to IP
	pollPacket.LongName[64] = "Electric Laboratory Artnetnode\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";   // long name
	//  char NodeReport[64]; // Text feedback of Node status or errors
	//  //  also used for debug info
	//
	//  uint8_t NumPortsHi = 0; // 0
	//  uint8_t NumPortsLo = 0; // 4 If num i/p ports is dif to output ports, return biggest
	//
	//  uint8_t PortTypes[4];
	//  // bit 7 is output
	//  // bit 6 is input
	//  // bits 0-5 are protocol number (0= DMX, 1=MIDI)
	//  // for DMX-Hub ={0xc0,0xc0,0xc0,0xc0};
	//
	//
	//  uint8_t GoodInput[4];
	//  // bit 7 is data received
	//  // bit 6 is data includes test packets
	//  // bit 5 is data includes SIP's
	//  // bit 4 is data includes text
	//  // bit 3 set is input is disabled
	//  // bit 2 is receive errors
	//  // bit 1-0 not used, transmitted as zero.
	//  // Don't test for zero!
	//
	//  uint8_t GoodOutput[4];
	//  // bit 7 is data is transmitting
	//  // bit 6 is data includes test packets
	//  // bit 5 is data includes SIP's
	//  // bit 4 is data includes text
	//  // bit 3 output is merging data.
	//  // bit 2 set if DMX output short detected on power up
	//  // bit 1 set if DMX output merge mode is LTP
	//  // bit 0 not used, transmitted as zero.
	//
	//  uint8_t SwIn[4];
	//  // Bits 3-0 of the 15 bit universe number are encoded into the low nibble
	//  // This is used in combination with SubSwitch and NetSwitch to produce the full universe address.
	//  // THIS IS FOR INPUT - ART-NET or DMX
	//  // NB ON ART-NET II THESE 4 UNIVERSES WILL BE UNICAST TO.
	//
	//
	//  uint8_t SwOut[4];
	//  // Bits 3-0 of the 15 bit universe number are encoded into the low nibble
	//  // This is used in combination with SubSwitch and NetSwitch to produce the full universe address.
	//  // data belongs
	//  // THIS IS FOR OUTPUT - ART-NET or DMX.
	//  // NB ON ART-NET II THESE 4 UNIVERSES WILL BE UNICAST TO.
	//
	//  uint8_t SwVideo = 0;
	//  // Low nibble is the value of the video
	//  // output channel
	//
	//  uint8_t SwMacro = 0;
	//  // Bit 0 is Macro input 1
	//  // Bit 7 is Macro input 8
	//
	//
	//  uint8_t SwRemote = 0;
	//  // Bit 0 is Remote input 1
	//  // Bit 7 is Remote input 8
	//
	//
	//  uint8_t Spare1 = 0; // Spare, currently zero
	//  uint8_t Spare2 = 0; // Spare, currently zero
	//  uint8_t Spare3 = 0; // Spare, currently zero
	//  uint8_t Style = 0; // Set to Style code to describe type of equipment
	//
	//  uint8_t Mac[6] = {MACADDR0, MACADDR1, MACADDR2, MACADDR3, MACADDR4, MACADDR5}; // Mac Address, zero if info not available
	//
	//  uint8_t BindIp[4]; // If this unit is part of a larger or modular product, this is the IP of the root device.
	//  uint8_t BindIndex = 0; // Set to zero if no binding, otherwise this number represents the order of bound devices. A lower number means closer to root device.
	//
	//  uint8_t Status2 = 0b00000000;
	//  // bit 0 = 0 Node does not support web browser
	//  // bit 0 = 1 Node supports web browser configuration
	//
	//  // bit 1 = 0 Node's IP address is manually configured
	//  // bit 1 = 1 Node's IP address is DHCP configured
	//
	//  // bit 2 = 0 Node is not DHCP capable
	//  // bit 2 = 1 Node is DHCP capable
	//
	//  // bit 2-7 not implemented, transmit as zero
	//
	//
	//
	//  uint8_t Filler[26]; // Filler bytes, currently zero.
}

PollReply::PollReply(){
  // Zero out vars
  memset(packet.IPAddr, 0, sizeof(packet.IPAddr));
  memset(packet.NodeReport, 0, sizeof(packet.NodeReport));
  memset(packet.PortTypes, 0, sizeof(packet.PortTypes));
  memset(packet.GoodInput, 0, sizeof(packet.GoodInput));
  memset(packet.GoodOutput, 0, sizeof(packet.GoodOutput));
  memset(packet.SwIn, 0, sizeof(packet.SwIn));
  memset(packet.SwOut, 0, sizeof(packet.SwOut));
  memset(packet.Filler, 0, sizeof(packet.Filler));
}

void PollReply::setMac(byte mac[]){
  packet.Mac[0] = mac[0];
  packet.Mac[1] = mac[1];
  packet.Mac[2] = mac[2];
  packet.Mac[3] = mac[3];
  packet.Mac[4] = mac[4];
  packet.Mac[5] = mac[5];
}

void PollReply::setIP(IPAddress IP){
  packet.IPAddr[0] = IP[0];
  packet.IPAddr[1] = IP[1];
  packet.IPAddr[2] = IP[2];
  packet.IPAddr[3] = IP[3];
}

void PollReply::setShortName(char name[]){
  int shortNameLen = sizeof(packet.ShortName);

  memset(packet.ShortName, 0, shortNameLen);

  for(int i = 0; i < shortNameLen && name[i] != 0; i++){
    packet.ShortName[i] = name[i];
  }
}

void PollReply::setLongName(char name[]){
  int longNameLen = sizeof(packet.LongName);

  memset(packet.LongName, 0, longNameLen);

  for(int i = 0; i < longNameLen && name[i] != 0; i++){
    packet.LongName[i] = name[i];
  }
}

void PollReply::canDHCP(bool can){
  if(can){
    packet.Status2 = packet.Status2 | 0b00100000;
  }
  else{
    packet.Status2 = packet.Status2 & (~0b00100000);
  }
}

void PollReply::isDHCP(bool is){
  if(is){
    packet.Status2 = packet.Status2 | 0b01000000;
  }
  else{
    packet.Status2 = packet.Status2 & (~0b01000000);
  }
}

void PollReply::setNumPorts(uint8_t num){
  packet.NumPortsLo = num;
}

void PollReply::setSwOut(uint8_t id, uint16_t universe){
  if(id > -1 && id < 4){
    packet.SwOut[id] = universe & 0b0000000000001111;
  }
}

void PollReply::setOutputEnabled(uint8_t port){
  if(port >= 0 && port < 4){
    packet.PortTypes[port] = packet.PortTypes[port] | 0b10000000;
    packet.GoodOutput[port] = packet.GoodOutput[port] | 0b10000000;
  }
}

void PollReply::setOutputDisabled(uint8_t port){
  if(port >= 0 && port < 4){
    packet.PortTypes[port] = packet.PortTypes[port] & (~0b10000000);
    packet.GoodOutput[port] = packet.GoodOutput[port] & (~0b10000000);
  }
}

void PollReply::setStartingUniverse(uint16_t startUniverse){
  packet.NetSwitch = startUniverse >> 8;
  packet.SubSwitch = (startUniverse & 0b000000011111111) >> 4;
}

uint8_t* PollReply::printPacket(){
  return (uint8_t *)&packet;
}
