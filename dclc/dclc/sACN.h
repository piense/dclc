#pragma once

#include <stdint.h>
#include <stdlib.h>

struct sACN_Universe {
	uint16_t univserse;
	uint16_t size; //number of channels used
	uint8_t priority; //Default = 100, lower = better
	char sourceName[64];
	uint8_t sequenceNum;
	uint8_t previewData; //0 = no, 1 = yes
	uint8_t startCode; //0 = DMX
	uint8_t packet[638];
	uint16_t packetLength;
};

void sACN_setChannel(sACN_Universe *universe, uint16_t channel, uint8_t value);
void sACN_setChannel16bit(sACN_Universe *universe, uint16_t channel, uint16_t value);
void sACN_incrementSequence(sACN_Universe *universe);
void sACN_zeros(sACN_Universe *universe);

void sACN_rebuildPacket(sACN_Universe *universe);

sACN_Universe *sACN_initUniverse(uint16_t size, uint8_t priority, uint8_t startCode, uint16_t universe);
sACN_Universe *sACN_initUniverse(uint16_t universe); //Inits using all default values

