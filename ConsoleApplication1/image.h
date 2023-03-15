#pragma once
#include <cstddef>
#include "RGB.h"
#include "string.h"
#include "line.h"

class Image
{
public:
	// Constructors
	Image() = delete;
	Image(const std::size_t newHeight, const std::size_t newWidth);
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image();
	
	// Functions that manipulate the image
	virtual void grayscale();
	virtual void monochrome();
	virtual void negative();
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;
	virtual void flipVertical() = 0;
	virtual void flipHorizontal() = 0;
	virtual void drawLine(const Positions& positionOne, const Positions& positionTwo, const RGB& color, const unsigned int lineThicknes = 1);
	void setColor(const unsigned int indexI, const unsigned int indexJ, const RGB& newColor);
	void setColor(const Positions& position, const RGB& color);

	const std::size_t getHeight() const;
	const std::size_t getWidth() const;
	const RGB& getColor(const unsigned int indexI, const unsigned int indexJ) const;

	virtual void readImage() = 0;
	virtual void write(const char* fileName) const = 0;
	virtual Image* clone() const = 0;
	virtual const String& getFileName() const = 0;

private:
	void drawLine(const Line& line, const RGB& color);
	void initializeImage();
	void copy(const Image& other);
	void destroy();

private:
	std::size_t width;
	std::size_t height;
	RGB** image;
};

