#pragma once
#include "string.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"

class Session
{
public:
	Session();
	Session(const String& fileName);
	Session(const Session& other);
	Session& operator=(const Session& other);
	~Session();

	void addImage(Image* newImage);
	void addImage(const String& fileName);
	void addCommand(const String& newCommand);
	void undoLastCommand();
	void save(const char* fileName) const;

	const unsigned int getId() const;
	void printCommandsDone() const;

	//tester
	const std::size_t getWidth() const;

private:
	void resizeImages();
	void resizeCommandsDone();
	void removeLastCommand();

	void initializeCommandsDone();
	void initializeImages();
	void copy(const Session& other);
	void destroy();

private:
	static unsigned int idGenerator;
	unsigned int id;
	unsigned int imagesCount;
	unsigned int imagesMemory;
	unsigned int commandsCount;
	unsigned int commandsMemory;
	String* commandsDone;
	Image** images;
};

