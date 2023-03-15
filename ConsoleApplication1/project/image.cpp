#include "image.h"

/// <summary>
/// Creates an white image.
/// </summary>
/// <param name="image height"></param>
/// <param name="image width"></param>
Image::Image(const std::size_t newHeight, const std::size_t newWidth)
	: height(newHeight), width(newWidth)
{
	RGB white(255, 255, 255);
	this->initializeImage();
	for (std::size_t i = 0; i < this->height; ++i)
	{
		for (std::size_t j = 0; j < this->width; ++j)
		{
			this->image[i][j] = white;
		}
	}
}

Image::Image(const Image& other)
{
	this->copy(other);
}

Image& Image::operator=(const Image& other)
{
	if (this != &other) {
		this->destroy();
		this->copy(other);
	}
	return *this;
}

Image::~Image()
{
	this->destroy();
}

/// <summary>
/// Makes the image gray.
/// </summary>
void Image::grayscale()
{
	for (std::size_t i = 0; i < this->height; ++i)
	{
		for (std::size_t j = 0; j < this->width; ++j)
		{
			unsigned int grayscaleValue = (this->image[i][j].getRed() * 0.299) + (this->image[i][j].getGreen() * 0.587) + (this->image[i][j].getBlue() * 0.114);
			RGB grayscaledColor(grayscaleValue, grayscaleValue, grayscaleValue);
			this->image[i][j] = grayscaledColor;
		}
	}
}

/// <summary>
/// Makes the image monochrome, with colors black and white.
/// </summary>
void Image::monochrome()
{
	RGB white(255, 255, 255);
	RGB black(0, 0, 0);
	for (std::size_t i = 0; i < this->height; ++i)
	{
		for (std::size_t j = 0; j < this->width; ++j)
		{
			double number = (this->image[i][j].getRed() + this->image[i][j].getGreen() + this->image[i][j].getBlue()) / 3;
			if (number < 127) {
				this->image[i][j] = black;
			}
			else {
				this->image[i][j] = white;
			}
		}
	}
}

/// <summary>
/// Makes the image negative.
/// </summary>
void Image::negative()
{
	for (std::size_t i = 0; i < this->height; ++i)
	{
		for (std::size_t j = 0; j < this->width; ++j)
		{
			unsigned int newRed = 255 - this->image[i][j].getRed();
			unsigned int newGreen = 255 - this->image[i][j].getGreen();
			unsigned int newBlue = 255 - this->image[i][j].getBlue();
			RGB newColor(newRed, newGreen, newBlue);
			this->image[i][j] = newColor;
		}
	}
}

void Image::drawLine(const Positions& positionOne, const Positions& positionTwo, const RGB& color, const unsigned int lineThicknes)
{
	if (lineThicknes <= 0) {
		throw "invalid line thicknes";
	}
	unsigned int newLineThicknes = ((this->width + this->height) / 2) * lineThicknes;
	Line line(positionOne, positionTwo, newLineThicknes, lineThicknes);
	this->drawLine(line, color);
}

/// <summary>
/// Sets a pixels color with given its position.
/// </summary>
/// <param name="index I"></param>
/// <param name="index J"></param>
/// <param name="new color of the pixel"></param>
void Image::setColor(const unsigned int indexI, const unsigned int indexJ, const RGB& newColor)
{
	this->image[indexI][indexJ] = newColor;
}

void Image::setColor(const Positions& position, const RGB& color)
{
	this->image[position.getY()][position.getX()] = color;
}

const std::size_t Image::getHeight() const
{
	return this->height;
}

const std::size_t Image::getWidth() const
{
	return this->width;
}

/// <summary>
/// Returns a pixels color with given its position.
/// </summary>
/// <param name="index I"></param>
/// <param name="index J"></param>
/// <returns></returns>
const RGB& Image::getColor(const unsigned int indexI, const unsigned int indexJ) const
{
	return this->image[indexI][indexJ];
}

void Image::drawLine(const Line& line, const RGB& color)
{
	for (std::size_t i = 0; i < line.getVectorSize(); ++i)
	{
		if ((0 <= line[i].getX() && line[i].getX() <= this->width - 1) && 0 <= line[i].getY() && line[i].getY() <= this->height - 1) {
			this->setColor(line[i], color);
		}
	}
}

/// <summary>
/// Initializes the RGB matrix memory.
/// </summary>
void Image::initializeImage()
{
	this->image = new RGB*[this->height];
	for (std::size_t i = 0; i < this->height; ++i)
	{
		this->image[i] = new RGB[this->width];
	}
}

/// <summary>
/// Copies another image.
/// </summary>
/// <param name="other image"></param>
void Image::copy(const Image& other)
{
	this->width = other.width;
	this->height = other.height;
	this->initializeImage();
	for (std::size_t i = 0; i < this->height; ++i)
	{
		for (std::size_t j = 0; j < this->width; ++j)
		{
			this->image[i][j] = other.image[i][j];
		}
	}
}

/// <summary>
/// Frees the heap memory.
/// </summary>
void Image::destroy()
{
	for (std::size_t i = 0; i < this->height; ++i)
	{
		delete[] this->image[i];
	}
	delete[] this->image;
}

