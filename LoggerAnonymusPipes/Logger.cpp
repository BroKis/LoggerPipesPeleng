#include "Logger.h"

using namespace std;

void Level0Logger::Write(Event event) {
	file << "level 0" << std::endl;
	file << "id: " << event.id << std::endl;
	file << "time: " << event.time << std::endl;
	file << std::endl;
}

void Level1Logger::Write(Event event) {
	file << "level 1" << std::endl;
	file << "id: " << event.id << std::endl;
	file << "date: " << event.date << std::endl;
	file << "time: " << event.time << std::endl;
	file << "first value: " << event.firstValue << std::endl;
	file << std::endl;
}

void Level2Logger::Write(Event event) {
	file << "level 2" << std::endl;
	file << "id: " << event.id << std::endl;
	file << "date: " << event.date << std::endl;
	file << "time: " << event.time << std::endl;
	file << "first value: " << event.firstValue << std::endl;
	file << "second value: " << event.secondValue << std::endl;
	file << "third value: " << event.thirdValue << std::endl;
	file << std::endl;
}

Logger* Logger::GetLogger(int level) {
	const char* fileName = "../LoggerAnonymousPipes/logs.txt";
	switch (level)
	{
	case 0: return new Level0Logger(fileName);
	case 1: return new Level1Logger(fileName);
	case 2: return new Level1Logger(fileName);
	default:
		return nullptr;
	}
}