#include "session.h"
#include <iostream>

unsigned int Session::idGenerator = 1;

Session::Session()
	: id(0), imagesCount(0), imagesMemory(8), commandsCount(0), commandsMemory(8)
{
	this->initializeCommandsDone();
	this->initializeImages();
}

Session::Session(const String& fileName)
	: id(idGenerator++), imagesCount(0), imagesMemory(8), commandsCount(0), commandsMemory(8) 
{
	this->initializeCommandsDone();
	this->initializeImages();
	this->addImage(fileName);
}

Session::Session(const Session& other)
	: id(idGenerator++)
{
	this->copy(other);
}

Session& Session::operator=(const Session& other)
{
	if (this != &other) {
		this->destroy();
		this->copy(other);
		this->id = other.id;
	}
	return *this;
}

Session::~Session()
{
	this->destroy();
}

void Session::addImage(Image* newImage)
{
	if (this->imagesCount == this->imagesMemory) {
		this->resizeImages();
	}
	this->images[this->imagesCount] = newImage->clone();
	this->imagesCount++;
}

void Session::addImage(const String& fileName)
{
	String fileType = fileName.getLastChars(4);
	if (fileType == ".ppm") {
		PPMImage image(fileName.getText());
		this->addImage(&image);
	}
	else if (fileType == ".pgm") {
		PGMImage image(fileName.getText());
		this->addImage(&image);
	}
	else if (fileType == ".pbm") {
		PBMImage image(fileName.getText());
		this->addImage(&image);
	}
	else {
		throw "does not support file type";
	}
}

void Session::addCommand(const String& newCommand)
{
	if (this->commandsCount == this->commandsMemory) {
		this->resizeCommandsDone();
	}
	this->commandsDone[this->commandsCount] = newCommand;
	this->commandsCount++;

	if (newCommand == "grayscale") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->grayscale();
		}
	}
	else if (newCommand == "monochrome") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->monochrome();
		}
	}
	else if (newCommand == "negative") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->negative();
		}
	}
	else if (newCommand == "left") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->rotateLeft();
		}
	}
	else if (newCommand == "right") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->rotateRight();
		}
	}
	else if (newCommand == "vertical") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->flipVertical();
		}
	}
	else if (newCommand == "horizontal") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->flipHorizontal();
		}
	}
	else if (newCommand == "line") {
		unsigned int posX;
		unsigned int posY;
		std::cout << "Enter START position:\n> x: ";
		std::cin >> posX;
		std::cout << "> y: ";
		std::cin >> posY;
		Positions start(posX, posY);

		std::cout << "\nEnter END position:\n> x: ";
		std::cin >> posX;
		std::cout << "> y: ";
		std::cin >> posY;
		Positions end(posX, posY);

		std::cout << "\nEnter line thicknes: ";
		unsigned int lineThicknes;
		std::cin >> lineThicknes;
		std::cout << std::endl;

		RGB black(0, 0, 0);
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->drawLine(start, end, black, lineThicknes);
		}
	}
}

void Session::undoLastCommand()
{
	if (this->commandsCount == 0) {
		std::cout << "There are no commands" << std::endl;
	}
	else if (this->commandsDone[this->commandsCount - 1] == "left") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->rotateRight();
		}
		this->removeLastCommand();
	}
	else if (this->commandsDone[this->commandsCount - 1] == "right") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->rotateLeft();
		}
		this->removeLastCommand();
	}
	else if (this->commandsDone[this->commandsCount - 1] == "horizontal") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->flipHorizontal();
		}
		this->removeLastCommand();
	}
	else if (this->commandsDone[this->commandsCount - 1] == "vertical") {
		for (std::size_t i = 0; i < this->imagesCount; ++i)
		{
			this->images[i]->flipVertical();
		}
		this->removeLastCommand();
	}
	else {
		std::cout << "Can't undo " << this->commandsDone[this->commandsCount - 1].getText() << " command." << std::endl;
	}
}

void Session::save(const char* fileName) const
{
	for (std::size_t i = 0; i < this->imagesCount; ++i)
	{
		String fullFileName(this->images[i]->getFileName());
		String fileFormat(fullFileName.getLastChars(4));
		fullFileName.removeLastChars(4);
		fullFileName += fileName;
		fullFileName += fileFormat.getText();
		std::cout << fullFileName.getText() << std::endl;
		this->images[i]->write(fullFileName.getText());
	}
}

const unsigned int Session::getId() const
{
	return this->id;
}

void Session::printCommandsDone() const
{
	for (std::size_t i = 0; i < this->commandsCount; ++i)
	{
		std::cout << this->commandsDone[i].getText() << " ";
	}
	std::cout << std::endl;
}

const std::size_t Session::getWidth() const
{
	return this->images[0]->getWidth();
}

void Session::resizeImages()
{
	this->imagesMemory *= 2;
	Image** holdImages = new Image*[this->imagesMemory];
	for (std::size_t i = 0; i < this->imagesCount; ++i)
	{
		holdImages[i] = this->images[i];
	}
	delete[] this->images;
	this->images = new Image*[this->imagesMemory];
	for (std::size_t i = 0; i < this->imagesCount; ++i)
	{
		this->images[i] = holdImages[i];
	}
}

void Session::resizeCommandsDone()
{
	this->commandsMemory *= 2;
	String* holdCommandsDone = new String[this->commandsMemory];
	for (std::size_t i = 0; i < this->commandsCount; ++i)
	{
		holdCommandsDone[i] = this->commandsDone[i];
	}
	delete[] this->commandsDone;
	this->commandsDone = new String[this->commandsMemory];
	for (std::size_t i = 0; i < this->commandsCount; ++i)
	{
		this->commandsDone[i] = holdCommandsDone[i];
	}
}

void Session::removeLastCommand()
{
	if (this->commandsCount == 0) {
		throw "error";
	}
	this->commandsDone[this->commandsCount - 1] = "";
	this->commandsCount -= 1;
}

void Session::initializeCommandsDone()
{
	this->commandsDone = new String[this->commandsMemory];
}

void Session::initializeImages()
{
	this->images = new Image*[this->imagesMemory];
}

void Session::copy(const Session& other)
{
	this->imagesCount = other.imagesCount;
	this->imagesMemory = other.imagesMemory;
	this->commandsCount = other.commandsCount;
	this->commandsMemory = other.commandsMemory;
	this->initializeCommandsDone();
	this->initializeImages();
	for (std::size_t i = 0; i < this->commandsCount; ++i)
	{
		this->commandsDone[i] = other.commandsDone[i];
	}
	for (std::size_t i = 0; i < this->imagesCount; ++i)
	{
		this->images[i] = other.images[i]->clone();
	}
}

void Session::destroy()
{
	delete[] this->commandsDone;
	delete[] this->images;
}
 