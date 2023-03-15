#pragma once

#include "positions.h"

class Equations
{
public:
	Equations();

	// Tester
	virtual void print() const;

private:
	virtual void calculateCoefficients(const Positions& startPosition, const Positions& endPosition) = 0;

protected:
	double coefficientX;
	double coefficientY;
	double constant;
}; 

