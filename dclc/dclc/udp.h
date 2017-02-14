#pragma once

#include <stdint.h>
#include <stdlib.h>

void sendUDP(uint8_t* packetBytes, uint16_t packetLength, bool broadcast, uint16_t port);
