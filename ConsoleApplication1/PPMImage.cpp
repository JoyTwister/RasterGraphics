#include "PPMImage.h"
#include <iostream>

/// <summary>
/// Creates an image with given .ppm file.
/// </summary>
/// <param name="file name"></param>
PPMImage::PPMImage(const char* fileName)
	: ReadStream(fileName), Image(this->ReadStream::readHeight(), this->ReadStream::readWidth()), isGrayscale(false), isMonochrome(false)
{
	if (this->ReadStream::getImageType() != PPM) {
		throw "file is not .ppm";
	}
	this->readImage();
}

/// <summary>
/// Creates an image with given its size parameter (height/width) and a .ppm file.
/// </summary>
/// <param name="file name"></param>
/// <param name="image height"></param>
/// <param name="image width"></param>
PPMImage::PPMImage(const char* fileName, const std::size_t newHeight, const std::size_t newWidth)
	: ReadStream(fileName), Image(newHeight, newWidth), isGrayscale(false), isMonochrome(false) {}

PPMImage::PPMImage(const PPMImage& other)
	: ReadStream(other), Image(other), isGrayscale(other.isGrayscale), isMonochrome(other.isMonochrome) {}

/// <summary>
/// Makes the image gray if this->isGrayscale == false.
/// </summary>
void PPMImage::grayscale()
{
	if (this->isGrayscale == false) {
		this->isGrayscale = true;
		this->Image::grayscale();
	}
}

/// <summary>
/// Makes the image monochrome, with colors black and white if this->isMonochrome == false.
/// </summary>
void PPMImage::monochrome()
{
	if (this->isMonochrome == false) {
		this->isMonochrome = true;
		this->isGrayscale = true;
		this->Image::monochrome();
	}
}

/// <summary>
/// Rotates an image counter clockwise.
/// </summary>
void PPMImage::rotateLeft()
{
	PPMImage rotatedImage(this->getFileName().getText(), this->getWidth(), this->getHeight()); // Creates a new image, given the old image parameters fliped
	for (std::size_t i = 0, oldJ = this->getWidth() - 1; i < rotatedImage.getHeight() && oldJ >= 0; ++i, --oldJ)
	{
		for (std::size_t j = 0, oldI = 0; j < rotatedImage.getWidth() && oldI < this->getHeight(); ++j, ++oldI)
		{
			rotatedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = rotatedImage;
}

/// <summary>
/// Rotates an image clockwise.
/// </summary>
void PPMImage::rotateRight()
{
	PPMImage rotatedImage(this->getFileName().getText(), this->getWidth(), this->getHeight()); // Creates a new image, given the old image parameters fliped
	for (std::size_t i = 0, oldJ = 0; i < rotatedImage.getHeight() && oldJ < this->getWidth(); ++i, ++oldJ)
	{
		for (std::size_t j = 0, oldI = this->getHeight() - 1; j < rotatedImage.getWidth() && oldI >= 0; ++j, --oldI)
		{
			rotatedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = rotatedImage;
}

/// <summary>
/// Flips an image on its vertical axis.
/// </summary>
void PPMImage::flipVertical()
{
	PPMImage flippedImage(this->getFileName().getText(), this->getHeight(), this->getWidth());
	for (std::size_t i = 0, oldI = 0; i < flippedImage.getHeight() && oldI < this->getHeight(); ++i, ++oldI)
	{
		for (std::size_t j = 0, oldJ = this->getWidth() - 1; j < flippedImage.getWidth() && oldJ >= 0; ++j, --oldJ)
		{
			flippedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = flippedImage;
}

/// <summary>
/// Flips an image on its horizontal axis.
/// </summary>
void PPMImage::flipHorizontal()
{
	PPMImage flippedImage(this->getFileName().getText(), this->getHeight(), this->getWidth());
	for (std::size_t i = 0, oldI = this->getHeight() - 1; i < flippedImage.getHeight() && oldI >= 0; ++i, --oldI)
	{
		for (std::size_t j = 0, oldJ = 0; j < flippedImage.getWidth() && oldJ < this->getWidth(); ++j, ++oldJ)
		{
			flippedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = flippedImage;
}

/// <summary>
/// Read an image from a .ppm file.
/// </summary>
void PPMImage::readImage()
{
	unsigned int maxColorValue; // not in use "trash"
	this->ReadStream::getStream() >> maxColorValue;
	for (std::size_t i = 0; i < this->getHeight(); ++i)
	{
		for (std::size_t j = 0; j < this->getWidth(); ++j)
		{
			unsigned char readColor[3];
			this->ReadStream::getStream().read(reinterpret_cast<char*>(readColor), 3);
			RGB color(readColor[2], readColor[1], readColor[0]);
			this->setColor(i, j, color);
		}
	}
}

/// <summary>
/// Writes a image on to a .ppm file, give the file name.
/// </summary>
/// <param name="file name with a .ppm"></param>
void PPMImage::write(const char* fileName) const
{
	std::ofstream fout;
	fout.open(fileName, std::ios::out | std::ios::binary);
	if (fout.is_open() == false) {
		throw std::runtime_error("File could not be opened");
	}
	fout << "P6" << " " << this->getWidth() << " " << this->getHeight() << " " << 255 << "\n";
	for (std::size_t i = 0; i < this->getHeight(); ++i)
	{
		for (std::size_t j = 0; j < this->getWidth(); ++j)
		{
			unsigned char red = static_cast<unsigned char>(this->getColor(i, j).getRed());
			unsigned char green = static_cast<unsigned char>(this->getColor(i, j).getGreen());
			unsigned char blue = static_cast<unsigned char>(this->getColor(i, j).getBlue());
			fout << green;
			fout << red;
			fout << blue;
		}
	}
	fout.close();
}

Image* PPMImage::clone() const
{
	return new PPMImage(*this);
}

const String& PPMImage::getFileName() const
{
	return this->ReadStream::getFileName();
}
