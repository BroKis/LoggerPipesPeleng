
#include "Command.h"
#include "Event.h"

HANDLE hReadPipe, hWritePipe;

typedef void (*Routine)();
map<string, Routine> CommandSelector;

Event*event = Event::CreateNewEvent();
Logger* logger = Logger::GetLogger(0);

mutex mtx;
static int timeoutEvents = 5;
static  bool isEnd = false;

static bool isPaused = false;

void Exit() {
	isEnd = true;
}

void currentTime()
{
	cout << (*event).time << endl;
}

void currentDate()
{
	cout << (*event).date << endl;
}

void Faster() {
	if (timeoutEvents - 1 <= 0) {
		std::cerr << "Нельзя сделать время между событиями меньше";
		return;
	}
	timeoutEvents--;
	cout << "Сейчас время между событиями равно: " << timeoutEvents << endl;
}

void Slower() {
	timeoutEvents += 1;
	cout << "Сейчас время между событиями равно: " << timeoutEvents << endl;
}

void Pause() {
	isPaused = true;
	cout << "Генерация событий остановлена" << endl;
}

void Resume() {
	isPaused = false;
	cout << "Генерация событий продолжена" << endl;
}

void Level0() {
	mtx.lock();
	logger = Logger::GetLogger(0);
	mtx.unlock();
	std::cout << "Уровень логгирования 0" << std::endl;
}

void Level1() {
	mtx.lock();
	logger = Logger::GetLogger(1);
	mtx.unlock();
	cout << "Уровень логгирования 1" << endl;
}
void Level2() {
	mtx.lock();
	logger = Logger::GetLogger(2);
	mtx.unlock();
	cout << "Уровень логгирования 2" << endl;
}

void Stat()
{
	cout << "Generated events " << (*event).id + 1 << endl;
}

void GenerateNewEvent(HANDLE hPipe) {
	while (!isEnd)
	{
		if (!isPaused)
		{
			mtx.lock();
			Event* localEvent = Event::CreateNewEvent();
			event = localEvent;
			mtx.unlock();
		}
		DWORD bytesWritten;
		if (!WriteFile(hPipe, event, sizeof(Event), &bytesWritten, NULL)) {
			std::cerr << "Ошибка записи в канал. Код ошибки: " << GetLastError() << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(timeoutEvents));
	}
	CloseHandle(hPipe);

}

void LogEvents(HANDLE hPipe) {
	int previousId = 0;
	while (!isEnd) {
		Event e;
		DWORD bytesRead;
		if (!ReadFile(hPipe, &e, sizeof(Event), &bytesRead, NULL)) {
			std::cerr << "Ошибка чтения из канала. Код ошибки: " << GetLastError() << std::endl;
			break;
		}
		if (e.id != previousId) {
			Logger* l = logger;
			l->Logger::Write(e);
			previousId = e.id;
		}
	}
}

void InputHandler() {
	std::string command;
	while (!isEnd) {
		std::cin >> command;

		if (CommandSelector.find(command) != CommandSelector.end()) {
			CommandSelector[command]();
			continue;
		}

		std::cerr << "There is no such command..." << std::endl;
	}
}


void FillSelector()
{
	CommandSelector["date"] = currentDate;
	CommandSelector["time"] = currentTime;
	CommandSelector["exit"] = Exit;
	CommandSelector["faster"] = Faster;
	CommandSelector["slower"] = Slower;
	CommandSelector["pause"] = Pause;
	CommandSelector["resume"] = Resume;
	CommandSelector["level0"] = Level0;
	CommandSelector["level1"] = Level1;
	CommandSelector["level2"] = Level2;
	CommandSelector["stat"] = Stat;
}
