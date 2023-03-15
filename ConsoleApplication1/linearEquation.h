#pragma once
#include "equations.h"

class LinearEquation : public Equations
{
public:
	LinearEquation(const Positions& startPosition, const Positions& endPosition);
	bool isPointOnPixelLine(const Positions& point, const int offsetNumber) const;

private:
	void calculateCoefficients(const Positions& startPosition, const Positions& endPosition) override;

private:

};

