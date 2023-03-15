#pragma once
#include "image.h"
#include "readStream.h"

class PGMImage : public ReadStream, public Image
{
public:
	// Constructors
	PGMImage(const char* fileName);
	PGMImage(const char* fileName, const std::size_t newHeight, const std::size_t newWidth);
	PGMImage(const PGMImage& other);

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

private:
	bool isMonochrome;
};
