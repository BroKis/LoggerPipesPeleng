
#include<map>
#include<string>
#include <iostream>
#include <thread>
#include "Command.h"
using namespace std;



int main()
{
	HANDLE hPipe[2];
	if (!CreatePipe(&hPipe[0], &hPipe[1], NULL, 0)) {
		std::cerr << "������ �������� ������. ��� ������: " << GetLastError() << std::endl;
		return 1;
	}

	FillSelector();

	thread userInputThread(InputHandler);
	thread mainThread(GenerateNewEvent,hPipe[1]);
	thread loggerThread(LogEvents,hPipe[0]);

	userInputThread.join();
	mainThread.join();
	loggerThread.join();

	std::cout << "������� �� ����� ������� ����� ��������� ���������" << std::endl;
	std::getchar();
	return 0;

}


