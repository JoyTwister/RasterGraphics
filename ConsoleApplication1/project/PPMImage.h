#pragma once
#include "image.h"
#include "readStream.h"

class PPMImage : public ReadStream, public Image
{
public:
	// Constructors
	PPMImage(const char* fileName);
	PPMImage(const char* fileName, const std::size_t newHeight, const std::size_t newWidth);
	PPMImage(const PPMImage& other);

	// Functions that manipulate the image
	void grayscale() override;
	void monochrome() override;
	void rotateLeft() override;
	void rotateRight() override;
	void flipVertical() override;
	void flipHorizontal() override;
	void readImage() override;
	void write(const char* fileName) const override;
	Image* clone() const override;
	const String& getFileName() const override;

private:
	bool isGrayscale;
	bool isMonochrome;
};

