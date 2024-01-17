#include "Event.h"
using namespace std;
	static int Id = 0;
	
	Event* Event::CreateNewEvent()
	{
		std::time_t rawtime;
		std::time(&rawtime);
		std::tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		char date[11];
		strftime(date, sizeof(date), "%d.%m.%Y", &timeinfo);

		char time[9];
		strftime(time, sizeof(time), "%H:%M:%S", &timeinfo);

		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> disturb(-50, 50);

		int firstVal = disturb(gen);
		int secondVal = disturb(gen);
		int thirdVal = disturb(gen);

		return new Event{ Id++, date, time, firstVal, secondVal, thirdVal };
	}


