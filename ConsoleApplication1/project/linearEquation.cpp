#include "linearEquation.h"

LinearEquation::LinearEquation(const Positions& startPosition, const Positions& endPosition)
	: Equations()
{
	this->calculateCoefficients(startPosition, endPosition);
}

void LinearEquation::calculateCoefficients(const Positions& startPosition, const Positions& endPosition)
{
	int coefficientX = endPosition.getY() - startPosition.getY();
	int coefficientY = startPosition.getX() - endPosition.getX();
	int constant = coefficientX * startPosition.getX() + coefficientY * startPosition.getY();
	this->coefficientX = coefficientX;
	this->coefficientY = coefficientY;
	this->constant = constant;
}

bool LinearEquation::isPointOnPixelLine(const Positions& point, const int offsetNumber) const
{
	if (this->coefficientX * point.getX() + this->coefficientY * point.getY() >= this->constant - offsetNumber &&
		this->coefficientX * point.getX() + this->coefficientY * point.getY() <= this->constant + offsetNumber) {
		return true;
	}
	return false;
}


//this->coefficientX = end.getY() - start.getY();
//this->coefficientY = start.getX() - end.getX();
//this->constant = this->coefficientX * start.getX() + this->coefficientY * start.getY(); // a = y2 - y1, b = x1 - x2, C
//this->print();