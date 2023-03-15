#include "positions.h"
#include <iostream>

Positions::Positions(const unsigned int _x, const unsigned int _y)
	: x(_x), y(_y) {}

bool Positions::operator==(const Positions& other) const
{
	if (this->x == other.x && this->y == other.y) {
		return true;
	}
	return false;
}

bool Positions::operator>(const Positions& other) const
{
	if (this->x > other.x && this->y > other.y) {
		return true;
	}
	return false;
}

bool Positions::operator<(const Positions& other) const
{
	if (this->x < other.x && this->y < other.y) {
		return true;
	}
	return false;
}

const unsigned int Positions::getX() const
{
	return this->x;
}

const unsigned int Positions::getY() const
{
	return this->y;
}

void Positions::print() const
{
	std::cout << "(" << this->x << ", " << this->y << ") ";
}
