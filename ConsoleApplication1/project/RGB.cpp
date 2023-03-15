#include "RGB.h"

RGB::RGB(const unsigned int newRed, const unsigned int newGreen, const unsigned int newBlue)
	:red(newRed), green(newGreen), blue(newBlue) {}

bool RGB::operator==(const RGB& other) const
{
	if (this->red == other.red && this->green == other.green && this->blue == other.blue) {
		return true;
	}
	return false;
}

const unsigned int RGB::getRed() const
{
	return this->red;
}

const unsigned int RGB::getGreen() const
{
	return this->green;
}

const unsigned int RGB::getBlue() const
{
	return this->blue;
}
