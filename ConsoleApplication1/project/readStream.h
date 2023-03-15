#pragma once
#include "string.h"
#include <fstream>

enum FileType
{
	PPM,
	PGM,
	PBM
};

/// <summary>
/// Creates a input stream to a these file types ".ppm", ".pgm" and ".pbm".
/// </summary>
class ReadStream
{
public:
	ReadStream(const char* newFileName);
	ReadStream(const ReadStream& other);
	ReadStream& operator=(const ReadStream& other);
	~ReadStream();

	std::istream& getStream();

	void setFileType();
	const std::size_t readWidth();
	const std::size_t readHeight();

	const String& getFileName() const;
	const FileType& getImageType() const;

private:
	std::ifstream fin;
	String fileName;
	FileType type;
};

