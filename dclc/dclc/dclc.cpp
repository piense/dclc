// dclc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sACN.h"
#include <stdio.h>
#include <iostream>
#include "udp.h"
#include <Windows.h>
#include "timing.h"

sACN_Universe *universe;
int x = 0;

/*
MASTER TODO:
sACN:
	Names
	CID

Timers:
	Generalize for different OSes
	Start & Stop
	Thread safety
	
	
*/


void sendUnivAgain() {
	for (int i = 0; i < 512; i++) {
		sACN_setChannel(universe, i + 1, x);
	}
	sACN_incrementSequence(universe);
	sendUDP(universe->packet, 638, false, 5568);
	x++;
}

int main()
{
	universe = sACN_initUniverse(1);

	startTimer(40, &sendUnivAgain);

	while (1) {
		Sleep(100);
	}
	
	getchar();
    return 0;
}

