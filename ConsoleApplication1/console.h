#pragma once
#include "session.h"

class Console
{
public:
	Console();
	~Console();

	void executeCommand(const String* command, const unsigned int commandWordCount);
	void addSession(const String& fileName);
	void switchSession(const unsigned int sessionId);

private:
	void resizeSessions();

private:
	bool consoleRunning;
	unsigned int sessionMemory;
	unsigned int sessionCount;
	unsigned int workingOnSession;
	Session* sessions;
};

