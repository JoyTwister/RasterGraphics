#pragma once
#include "image.h"
#include "readStream.h"

class PBMImage : public ReadStream, public Image
{
public:
	// Constructors
	PBMImage(const char* fileName);
	PBMImage(const char* fileName, const std::size_t newHeight, const std::size_t newWidth);
	PBMImage(const PBMImage& other);

	// Functions that manipulate the image
	void grayscale() override;
	void monochrome() override;
	void rotateLeft() override;
	void rotateRight() override;
	void flipVertical() override;
	void flipHorizontal() override;
	void drawLine(const Positions& positionOne, const Positions& positionTwo, const RGB& color, const unsigned int lineThicknes = 1) override;
	void readImage() override;
	void write(const char* fileName) const override;
	Image* clone() const override;
	const String& getFileName() const override;
};

