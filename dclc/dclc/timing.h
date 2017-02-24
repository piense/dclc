#pragma once
#include <stdint.h>

//OS specific timer initialization stuff, like resolution settings
void initTimers();

//Calls a function at a given rate
//TODO: Return ID to kill it
void startTimer(uint16_t rate, void(*cb)());

//Time since program launch in ms
uint64_t timeInMs();