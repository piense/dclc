#include "sACN.h"
#include <stdio.h>
#include <cstring>

sACN_Universe *sACN_initUniverse(uint16_t size, uint8_t priority, uint8_t startCode, uint16_t universe) {
	sACN_Universe * newUniverse = (sACN_Universe*)malloc(sizeof(sACN_Universe));

	if (newUniverse == NULL) {
		printf("ERROR: Failed to allocate new universe.\n");
		goto error;
	}

	newUniverse->previewData = 0;
	newUniverse->priority = priority;
	newUniverse->sequenceNum = 0;
	newUniverse->size = size;
	//newUniverse->sourceName = "";
	newUniverse->startCode = startCode;
	newUniverse->univserse = universe;
	newUniverse->packetLength = size + 126;

	sACN_rebuildPacket(newUniverse);

	return newUniverse;

error:
	return NULL;
}

sACN_Universe *sACN_initUniverse(uint16_t universe) {
	return sACN_initUniverse(512, 100, 0, universe);
}

void sACN_setChannel(sACN_Universe *universe, uint16_t channel, uint8_t value)
{
	universe->packet[125 + channel] = value;
}

void sACN_setChannel16bit(sACN_Universe *universe, uint16_t channel, uint16_t value)
{
	//TODO: other platform endianness
	universe->packet[125 + channel] = (value && 0xFF00) >> 8;
	universe->packet[125 + channel + 1] = value && 0xFF;
}

void sACN_incrementSequence(sACN_Universe *universe) {
	universe->sequenceNum++;
	universe->packet[111] = universe->sequenceNum;
}

void sACN_zeros(sACN_Universe *universe) {
	for (int i = 0; i < 512; i++) {
		universe->packet[i + 126] = 0;
	}
}

void sACN_rebuildPacket(sACN_Universe *universe) {
	//Create the framing for the ACN packet

	//Preamble Size
	universe->packet[0] = 0x00;
	universe->packet[1] = 0x10;

	//Post-amble size
	universe->packet[2] = 0x00;
	universe->packet[3] = 0x00;

	//ACN Packet Identifier
	universe->packet[4] = 0x41;
	universe->packet[5] = 0x53;
	universe->packet[6] = 0x43;
	universe->packet[7] = 0x2d;
	universe->packet[8] = 0x45;
	universe->packet[9] = 0x31;
	universe->packet[10] = 0x2e;
	universe->packet[11] = 0x31;
	universe->packet[12] = 0x37;
	universe->packet[13] = 0x00;
	universe->packet[14] = 0x00;
	universe->packet[15] = 0x00;

	//Flags and Length
	//TODO: fix endian wierdness for other platforms

	uint16_t temp = (universe->size + 110) | 0x7000;

	universe->packet[16] = (temp & 0xFF00) >> 8;
	universe->packet[17] = temp & 0xFF;

	//Vector
	universe->packet[18] = 0x00;
	universe->packet[19] = 0x00;
	universe->packet[20] = 0x00;
	universe->packet[21] = 0x04;

	//CID
	//TODO: figure out a good CID algorithm
	universe->packet[22] = 0x00;
	universe->packet[23] = 0x00;
	universe->packet[24] = 0x00;
	universe->packet[25] = 0x00;
	universe->packet[26] = 0x00;
	universe->packet[27] = 0x00;
	universe->packet[28] = 0x00;
	universe->packet[29] = 0x00;
	universe->packet[30] = 0x00;
	universe->packet[31] = 0x00;
	universe->packet[32] = 0x00;
	universe->packet[33] = 0x00;
	universe->packet[34] = 0x00;
	universe->packet[35] = 0x00;
	universe->packet[36] = 0x00;
	universe->packet[37] = 0x00;

	//Flags and Length
	//TODO: fix endian wierdness for other platforms

	temp = (universe->size + 88) | 0x7000;

	universe->packet[38] = (temp & 0xFF00) >> 8;
	universe->packet[39] = temp & 0xFF;

	//Vector
	universe->packet[40] = 0x00;
	universe->packet[41] = 0x00;
	universe->packet[42] = 0x00;
	universe->packet[43] = 0x02;

	//Name
	//TODO:Maybe add some safety here
	memcpy(&universe->packet[44], &universe->sourceName, 64);

	//Priority
	universe->packet[108] = universe->priority;

	//Reserved
	universe->packet[109] = 0x00;
	universe->packet[110] = 0x00;

	//Sequence Number
	universe->packet[111] = universe->sequenceNum;

	//options
	universe->packet[112] = universe->previewData * 64;

	//Universe Number
	//TODO: endianness handling
	universe->packet[113] = (universe->univserse & 0xFF00) >> 8;
	universe->packet[114] = universe->univserse & 0xFF;

	//Flags and Length
	//TODO: fix endian wierdness for other platforms

	temp = (universe->size + 11) | 0x7000;

	universe->packet[115] = (temp & 0xFF00) >> 8;
	universe->packet[116] = temp & 0xFF;

	//Vector
	universe->packet[117] = 0x02;

	//Address Type & Data Type
	universe->packet[118] = 0xa1;

	//First Property Address
	universe->packet[119] = 0x00;
	universe->packet[120] = 0x00;

	//Address Increment
	universe->packet[121] = 0x00;
	universe->packet[122] = 0x01;

	//Number of Properties (start code + dmx channels)
	temp = universe->size + 1;
	universe->packet[123] = (temp & 0xFF00) >> 8;
	universe->packet[124] = temp & 0xFF;

	universe->packet[125] = universe->startCode;

	sACN_zeros(universe);
}
