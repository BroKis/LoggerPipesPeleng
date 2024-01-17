#ifndef COMMAND_H
#define COMMAND_H
#pragma once
#include <thread>
#include <mutex>
#include "Event.h"
#include "Logger.h"
#include <map>
#include <string>
#include <Windows.h>
using namespace std;
void Exit();
void currentTime();
void currentDate();
void Faster();
void Slower();
void Pause();
void Resume();
void Level0();
void Level1();
void Level2();
void Stat();
void GenerateNewEvent(HANDLE hPipe);
void LogEvents(HANDLE hPipe);
void InputHandler();
void FillSelector();
#endif
