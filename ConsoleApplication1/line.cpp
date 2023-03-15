#include "line.h"
#include <iostream>

Line::Line(const Positions& start, const Positions& end, const int newLineThicknes, unsigned int newOffSetNumber)
	: LinearEquation(start, end), start(start), end(end), lineThicknes(newLineThicknes), offSetNumber(newOffSetNumber), vector(64U)
{
	if (start < end) {
		this->addPositions(start.getY(), end.getY(), start.getX(), end.getX());
	}
	if (start > end) {
		this->addPositions(end.getY(), start.getY(), end.getX(), start.getX());
	}
	if (start.getX() >= end.getX() && start.getY() <= end.getY()) {
		if (start.getX() == end.getX() || start.getY() == end.getY()) {
			this->addPositionsVerticaleHorizontal(start.getY(), end.getY(), end.getX(), start.getX());
		}
		else {
			this->addPositions(start.getY(), end.getY(), end.getX(), start.getX());
		}
	}
	if (start.getX() <= end.getX() && start.getY() >= end.getY()) {
		if (start.getX() == end.getX() || start.getY() == end.getY()) {
			this->addPositionsVerticaleHorizontal(end.getY(), start.getY(), start.getX(), end.getX());
		}
		else {
			this->addPositions(end.getY(), start.getY(), start.getX(), end.getX());
		}
	}
}

const std::size_t Line::getVectorSize() const
{
	return this->vector.getSize();
}

const Positions& Line::operator[](unsigned int index) const
{
	return this->vector[index];
}

bool Line::isLineVerticaleHorizontal() const
{
	if (this->start.getX() == end.getX()) {
		return true;
	}
	if (this->start.getY() == end.getY()) {
		return true;
	}
	return false;
}

void Line::print() const
{
	for (std::size_t i = this->start.getY(); i <= this->end.getY(); ++i)
	{
		for (std::size_t j = this->start.getX(); j <= this->end.getX(); ++j)
		{
			Positions currentPosition(j, i);
			bool flag = false;
			for (std::size_t k = 0; k < this->vector.getSize(); ++k)
			{
				if (currentPosition == vector[k]) {
					flag = true;
				}
			}
			if (flag == true) {
				std::cout << "1 ";
			}
			else {
				std::cout << "0 ";
			}
		}
		std::cout << std::endl;
	}
}

void Line::addPositionsVerticaleHorizontal(const unsigned int startI, const unsigned int endI, const unsigned int startJ, const unsigned int endJ)
{
	for (std::size_t i = startI - this->offSetNumber; i <= endI + this->offSetNumber; ++i)
	{
		for (std::size_t j = startJ - this->offSetNumber; j <= endJ + this->offSetNumber; ++j)
		{
			Positions currentPosition(j, i);
			if (this->LinearEquation::isPointOnPixelLine(currentPosition, this->lineThicknes) == true) {
				this->vector.addPosition(currentPosition);
			}
		}
	}
}

void Line::addPositions(const unsigned int startI, const unsigned int endI, const unsigned int startJ, const unsigned int endJ)
{
	for (std::size_t i = startI; i <= endI; ++i)
	{
		for (std::size_t j = startJ; j <= endJ; ++j)
		{
			Positions currentPosition(j, i);
			if (this->LinearEquation::isPointOnPixelLine(currentPosition, this->lineThicknes) == true) {
				this->vector.addPosition(currentPosition);
			}
		}
	}
}
 