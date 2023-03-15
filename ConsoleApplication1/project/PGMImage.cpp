#include "PGMImage.h"

/// <summary>
/// Creates a PGM image with the input of a .pgm file, witch creates the stream and reads the image.
/// </summary>
/// <param name="fileName"></param>
PGMImage::PGMImage(const char* fileName)
	: ReadStream(fileName), Image(this->ReadStream::readHeight(), this->ReadStream::readWidth()), isMonochrome(false)
{
	if (this->ReadStream::getImageType() != PGM) { // Checks if the file is .pgm
		throw "file is not .pgm";
	}
	this->readImage();
}

/// <summary>
/// Ceates a white PGM image with given height and width of the image.
/// </summary>
/// <param name="fileName"></param>
/// <param name="newHeight"></param>
/// <param name="newWidth"></param>
PGMImage::PGMImage(const char* fileName, const std::size_t newHeight, const std::size_t newWidth)
	: ReadStream(fileName), Image(newHeight, newWidth), isMonochrome(false) {}

PGMImage::PGMImage(const PGMImage& other)
	: ReadStream(other), Image(other), isMonochrome(other.isMonochrome) {}

/// <summary>
/// Function does not change the image, because it's already grayscale.
/// </summary>
void PGMImage::grayscale()
{
	return;
}

/// <summary>
/// Turns the image monochrome if the image is not monochrome already.
/// </summary>
void PGMImage::monochrome()
{
	if (this->isMonochrome == false) {
		this->isMonochrome = true;
		this->Image::monochrome();
	}
}

/// <summary>
/// Rotates an image counter clockwise.
/// </summary>
void PGMImage::rotateLeft()
{
	PGMImage rotatedImage(this->getFileName().getText(), this->getWidth(), this->getHeight()); // Creates a new image, given the old image parameters fliped
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
void PGMImage::rotateRight()
{
	PGMImage rotatedImage(this->getFileName().getText(), this->getWidth(), this->getHeight()); // Creates a new image, given the old image parameters fliped
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
void PGMImage::flipVertical()
{
	PGMImage flippedImage(this->getFileName().getText(), this->getHeight(), this->getWidth());
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
void PGMImage::flipHorizontal()
{
	PGMImage flippedImage(this->getFileName().getText(), this->getHeight(), this->getWidth());
	for (std::size_t i = 0, oldI = this->getHeight() - 1; i < flippedImage.getHeight() && oldI >= 0; ++i, --oldI)
	{
		for (std::size_t j = 0, oldJ = 0; j < flippedImage.getWidth() && oldJ < this->getWidth(); ++j, ++oldJ)
		{
			flippedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = flippedImage;
}

void PGMImage::drawLine(const Positions& positionOne, const Positions& positionTwo, const RGB& color, const unsigned int lineThicknes)
{
	unsigned int grayscaleValue = (color.getRed() * 0.299) + (color.getGreen() * 0.587) + (color.getBlue() * 0.114);
	RGB grayscaledColor(grayscaleValue, grayscaleValue, grayscaleValue);
	this->Image::drawLine(positionOne, positionTwo, grayscaledColor, lineThicknes);
}

/// <summary>
/// Read an image from a .pgm file.
/// </summary>
void PGMImage::readImage()
{
	unsigned int maxColorValue; // not in use "trash"
	this->ReadStream::getStream() >> maxColorValue;
	for (std::size_t i = 0; i < this->getHeight(); ++i)
	{
		for (std::size_t j = 0; j < this->getWidth(); ++j)
		{
			unsigned char readColor[1];
			this->ReadStream::getStream().read(reinterpret_cast<char*>(readColor), 1);
			RGB color(readColor[0], readColor[0], readColor[0]);
			this->setColor(i, j, color);
		}
	}
}

/// <summary>
/// Writes a image on to a .pgm file, give the file name.
/// </summary>
/// <param name="file name with a .pgm"></param>
void PGMImage::write(const char* fileName) const
{
	std::ofstream fout;
	fout.open(fileName, std::ios::out | std::ios::binary);
	if (fout.is_open() == false) {
		throw std::runtime_error("File could not be opened");
	}
	fout << "P5" << " " << this->getWidth() << " " << this->getHeight() << " " << 255 << "\n";
	for (std::size_t i = 0; i < this->getHeight(); ++i)
	{
		for (std::size_t j = 0; j < this->getWidth(); ++j)
		{
			unsigned char red = static_cast<unsigned char>(this->getColor(i, j).getRed());
			fout << red;
		}
	}
	fout.close();
}

Image* PGMImage::clone() const
{
	return new PGMImage(*this);
}

const String& PGMImage::getFileName() const
{
	return this->ReadStream::getFileName();
}
