#ifndef LOGGER_H
#define LOGGER_H
#pragma once
#include <fstream>
#include "Event.h"
#include <iostream>
using namespace std;
class Logger {
protected:
	std::ofstream file;
	Logger(const char* fileName) {
		file.open(fileName, std::ios::app);
		if (!file.is_open()) {
			std::cerr << "Fail to open " << fileName << std::endl;
		}
	}
	~Logger() {
		if (file.is_open()) {
			file.close();
		}
	}

public:
	static Logger* GetLogger(int level);
	virtual void Write(Event event) = 0;
};

class Level0Logger : public Logger {
public:
	Level0Logger(const char* fileName) : Logger(fileName) {}
	void Write(Event event) override {}
	
};
class Level1Logger : public Logger {
public:
	Level1Logger(const char* fileName) : Logger(fileName) {}
	void Write(Event event) override {}
};
class Level2Logger : public Logger {
public:
	Level2Logger(const char* fileName) : Logger(fileName) {}
	void Write(Event event) override {}
};

#endif
