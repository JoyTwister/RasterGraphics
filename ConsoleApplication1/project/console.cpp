#include "console.h"
#include <iostream>

Console::Console()
	: consoleRunning(true), sessionMemory(8), sessionCount(0)
{
	this->sessions = new Session[this->sessionMemory];
	do
	{
		char userInput[100];
		std::cout << "> ";
		std::cin.getline(userInput, 100);

		String inputStr(userInput);
		String* commands = new String[inputStr.countSpaces() + 1];
		commands = inputStr.breakDown();

		this->executeCommand(commands, inputStr.countSpaces() + 1);
	} while (this->consoleRunning == true);
}

Console::~Console()
{
	delete[] this->sessions;
}

void Console::executeCommand(const String* command, const unsigned int commandWordCount)
{
	if (command[0] == "load") {
		if (commandWordCount == 1) {
			std::cout << "You must give a file" << std::endl;
		}
		else {
			this->addSession(command[1]);
			if (commandWordCount > 2) {
				for (std::size_t i = 2; i < commandWordCount; ++i)
				{
					this->sessions[this->workingOnSession].addImage(command[i]);
				}
			}
			std::cout << "Session with ID: "<< this->sessions[this->workingOnSession].getId() << " started" << std::endl;
		}
	}
	if (command[0] == "grayscale") {
		if (commandWordCount > 1) {
			std::cout << "invalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].addCommand(command[0]);
		}
	}
	if (command[0] == "save") {
		if (commandWordCount > 1) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].save("_modified_time");
		}
	}
	if (command[0] == "monochrome") {
		if (commandWordCount > 1) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].addCommand(command[0]);
		}
	}
	if (command[0] == "negative") {
		if (commandWordCount > 1) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].addCommand(command[0]);
		}
	}
	if (command[0] == "rotate") {
		if (command[1] == "left") {
			if (commandWordCount > 2) {
				std::cout << "ivalid command" << std::endl;
			}
			else {
				this->sessions[this->workingOnSession].addCommand(command[1]);
			}
		}
		if (command[1] == "right") {
			if (commandWordCount > 2) {
				std::cout << "ivalid command" << std::endl;
			}
			else {
				this->sessions[this->workingOnSession].addCommand(command[1]);
			}
		}
	}
	if (command[0] == "flip") {
		if (command[1] == "horizontal") {
			if (commandWordCount > 2) {
				std::cout << "ivalid command" << std::endl;
			}
			else {
				this->sessions[this->workingOnSession].addCommand(command[1]);
			}
		}
		if (command[1] == "vertical") {
			if (commandWordCount > 2) {
				std::cout << "ivalid command" << std::endl;
			}
			else {
				this->sessions[this->workingOnSession].addCommand(command[1]);
			}
		}
	}
	if (command[0] == "line") {
		if (commandWordCount > 2) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].addCommand(command[0]);
		}
	}
	if (command[0] == "undo") {
		if (commandWordCount > 1) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].undoLastCommand();
		}
	}
	if (command[0] == "add") {
		if (commandWordCount > 2) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].addImage(command[1]);
		}
	}
	if (command[0] == "session" && command[1] == "info") {
		if (commandWordCount > 2) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			this->sessions[this->workingOnSession].printCommandsDone();
		}
	}
	if (command[0] == "switch") {
		if (commandWordCount > 2) {
			std::cout << "ivalid command" << std::endl;
		}
		else {
			unsigned int sessionId = command[1].convertStrToNumber();
			this->switchSession(sessionId);
		}
	}
	if (command[0] == "exit") {
		this->consoleRunning = false;
	}
}

void Console::addSession(const String& fileName)
{
	Session session(fileName);
	if (this->sessionCount == this->sessionMemory) {
		this->resizeSessions();
	}
	this->workingOnSession = this->sessionCount;
	this->sessions[this->workingOnSession] = session;
	this->sessionCount++;
}

void Console::switchSession(const unsigned int sessionId)
{
	for (std::size_t i = 0; i < this->sessionCount; ++i)
	{
		if (this->sessions[i].getId() == sessionId) {
			this->workingOnSession = i;
		}
	}
}

void Console::resizeSessions()
{
	this->sessionMemory *= 2;
	Session* holdSessions = new Session[this->sessionMemory];
	for (std::size_t i = 0; i < this->sessionCount; ++i)
	{
		holdSessions[i] = this->sessions[i];
	}
	delete[] this->sessions;
	this->sessions = new Session[this->sessionMemory];
	for (std::size_t i = 0; i < this->sessionCount; ++i)
	{
		this->sessions[i] = holdSessions[i];
	}
}



 