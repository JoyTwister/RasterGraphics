#include "PBMImage.h"

/// <summary>
/// Creates a monochrome image given a file name of file type .pbm.
/// </summary>
/// <param name="fileName"></param>
PBMImage::PBMImage(const char* fileName)
	: ReadStream(fileName), Image(this->ReadStream::readHeight(), this->ReadStream::readWidth())
{
	if (this->ReadStream::getImageType() != PBM) { // Checks if the file is .pbm
		throw "file is not .pbm";
	}
	this->readImage();
}

PBMImage::PBMImage(const char* fileName, const std::size_t newHeight, const std::size_t newWidth)
	: ReadStream(fileName), Image(newHeight, newWidth) {}

PBMImage::PBMImage(const PBMImage& other)
	: ReadStream(other), Image(other) {}

void PBMImage::grayscale()
{
	return;
}

void PBMImage::monochrome()
{
	return;
}

void PBMImage::rotateLeft()
{
	PBMImage rotatedImage(this->getFileName().getText(), this->getWidth(), this->getHeight()); // Creates a new image, given the old image parameters fliped
	for (std::size_t i = 0, oldJ = this->getWidth() - 1; i < rotatedImage.getHeight() && oldJ >= 0; ++i, --oldJ)
	{
		for (std::size_t j = 0, oldI = 0; j < rotatedImage.getWidth() && oldI < this->getHeight(); ++j, ++oldI)
		{
			rotatedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = rotatedImage;
}

void PBMImage::rotateRight()
{
	PBMImage rotatedImage(this->getFileName().getText(), this->getWidth(), this->getHeight()); // Creates a new image, given the old image parameters fliped
	for (std::size_t i = 0, oldJ = 0; i < rotatedImage.getHeight() && oldJ < this->getWidth(); ++i, ++oldJ)
	{
		for (std::size_t j = 0, oldI = this->getHeight() - 1; j < rotatedImage.getWidth() && oldI >= 0; ++j, --oldI)
		{
			rotatedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = rotatedImage;
}

void PBMImage::flipVertical()
{
	PBMImage flippedImage(this->getFileName().getText(), this->getHeight(), this->getWidth());
	for (std::size_t i = 0, oldI = 0; i < flippedImage.getHeight() && oldI < this->getHeight(); ++i, ++oldI)
	{
		for (std::size_t j = 0, oldJ = this->getWidth() - 1; j < flippedImage.getWidth() && oldJ >= 0; ++j, --oldJ)
		{
			flippedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = flippedImage;
}

void PBMImage::flipHorizontal()
{
	PBMImage flippedImage(this->getFileName().getText(), this->getHeight(), this->getWidth());
	for (std::size_t i = 0, oldI = this->getHeight() - 1; i < flippedImage.getHeight() && oldI >= 0; ++i, --oldI)
	{
		for (std::size_t j = 0, oldJ = 0; j < flippedImage.getWidth() && oldJ < this->getWidth(); ++j, ++oldJ)
		{
			flippedImage.setColor(i, j, this->getColor(oldI, oldJ));
		}
	}
	*this = flippedImage;
}

void PBMImage::drawLine(const Positions& positionOne, const Positions& positionTwo, const RGB& color, const unsigned int lineThicknes)
{
	RGB newColor;
	RGB white(255, 255, 255);
	RGB black(0, 0, 0);
	double number = (color.getRed() + color.getGreen() + color.getBlue()) / 3;
	if (number < 127) {
		newColor = black;
	}
	else {
		newColor = white;
	}
	this->Image::drawLine(positionOne, positionTwo, newColor, lineThicknes);
}

void PBMImage::readImage()
{
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

void PBMImage::write(const char* fileName) const
{
	std::ofstream fout;
	fout.open(fileName, std::ios::out | std::ios::binary);
	if (fout.is_open() == false) {
		throw std::runtime_error("File could not be opened");
	}
	fout << "P4" << " " << this->getWidth() << " " << this->getHeight() << "\n";
	for (std::size_t i = 0; i < this->getHeight(); ++i)
	{
		for (std::size_t j = 0; j < this->getWidth(); ++j)
		{
			unsigned char color = static_cast<unsigned char>(this->getColor(i, j).getRed());
			fout << color;
		}
	}
	fout.close();
}

Image* PBMImage::clone() const
{
	return new PBMImage(*this);
}

const String& PBMImage::getFileName() const
{
	return this->ReadStream::getFileName();
}
