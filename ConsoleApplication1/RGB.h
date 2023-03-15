#pragma once

/// <summary>
/// Contains 3 positive numbers for red, green and blue values of a color.
/// </summary>
class RGB
{
public:
	RGB(const unsigned int newRed = 255, const unsigned int newGreen = 255, const unsigned int newBlue = 255);

	bool operator==(const RGB& other) const;

	const unsigned int getRed() const;
	const unsigned int getGreen() const;
	const unsigned int getBlue() const;

private:
	unsigned int red;
	unsigned int green;
	unsigned int blue;
};

