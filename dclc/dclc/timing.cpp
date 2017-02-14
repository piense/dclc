//This code is going to be one of the trickier cross-platform bits, bleh

#include "timing.h"
#include <windows.h>
#include <stdio.h>

/*
void startTimer(uint16_t rate, void(*cb)()) {

}*/

void (*timerCB)();

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	if (timerCB != NULL)
		timerCB();

}

void startTimer(uint16_t rate, void(*cb)()) {

	HANDLE hTimer = NULL;
	HANDLE hTimerQueue = NULL;

	//Ack, will fall out of scope
	int arg = 123;


	// Create the timer queue.
	hTimerQueue = CreateTimerQueue();
	if (NULL == hTimerQueue)
	{
		printf("CreateTimerQueue failed (%d)\n", GetLastError());
		return;
	}

	// Set a timer to call the timer routine in 10 seconds.
	if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
		(WAITORTIMERCALLBACK)TimerRoutine, &arg, 1000/rate, 1000 / rate, 0))
	{
		printf("CreateTimerQueueTimer failed (%d)\n", GetLastError());
		return;
	}

	timerCB = cb;

	// Delete all timers in the timer queue.
//	if (!DeleteTimerQueue(hTimerQueue))
//		printf("DeleteTimerQueue failed (%d)\n", GetLastError());

	return;
}
