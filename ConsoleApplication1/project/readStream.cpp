#include "readStream.h"
#include <iostream>

/// <summary>
/// Creates a stream to a file using its name.
/// </summary>
/// <param name="file name"></param>
ReadStream::ReadStream(const char* newFileName)
	: fileName(newFileName)
{
	this->fin.open(this->fileName.getText(), std::ios::in | std::ios::binary);
	if (this->fin.is_open() == false) {
		throw std::runtime_error("File could not be opened");
	}
	this->setFileType();
}

ReadStream::ReadStream(const ReadStream& other)
	: fileName(other.fileName)
{
	this->fin.open(this->fileName.getText(), std::ios::in | std::ios::binary);
	if (this->fin.is_open() == false) {
		throw std::runtime_error("File could not be opened");
	}
	this->type = other.type;
}

ReadStream& ReadStream::operator=(const ReadStream& other)
{
	this->fileName = other.fileName;
	this->type = other.type;
	this->fin.open(this->fileName.getText(), std::ios::in | std::ios::binary);
	if (this->fin.is_open() == false) {
		throw std::runtime_error("File could not be opened");
	}
}

ReadStream::~ReadStream()
{
	this->fin.close();
}

/// <summary>
/// Gives access to the input stream.
/// </summary>
/// <returns></returns>
std::istream& ReadStream::getStream()
{
	return this->fin;
}

/// <summary>
/// Sets the file type.
/// </summary>
void ReadStream::setFileType()
{
	unsigned char fileTypeInfo[2];
	this->fin.read(reinterpret_cast<char*>(fileTypeInfo), 2);
	if (fileTypeInfo[0] == 'P' && fileTypeInfo[1] == '6') {
		this->type = PPM;
	}
	else if (fileTypeInfo[0] == 'P' && fileTypeInfo[1] == '5') {
		this->type = PGM;
	}
	else if (fileTypeInfo[0] == 'P' && fileTypeInfo[1] == '4') {
		this->type = PBM;
	}
	else {
		throw "does not support file type";
	}
}

/// <summary>
/// Reads from a file the image width.
/// </summary>
/// <returns></returns>
const std::size_t ReadStream::readWidth()
{
	std::size_t width;
	this->ReadStream::getStream() >> width;
	return width;
}

/// <summary>
/// Reads from a file the image height.
/// </summary>
/// <returns></returns>
const std::size_t ReadStream::readHeight()
{
	std::size_t height;
	this->ReadStream::getStream() >> height;
	return height;
}

const String& ReadStream::getFileName() const
{
	return this->fileName;
}

const FileType& ReadStream::getImageType() const
{
	return this->type;
}
