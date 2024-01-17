#ifndef EVENT_H
#define EVENT_H
#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <random>
#include <sstream>
struct Event
{
	int id;
	string date;
	string time;
	int firstValue;
	int secondValue;
	int thirdValue;
	static Event* CreateNewEvent();


};
#endif