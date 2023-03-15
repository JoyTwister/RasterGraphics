#pragma once

#include "linearEquation.h"
#include "positionsPixelVector.h"

class Line : public LinearEquation
{
public:
	Line(const Positions& start, const Positions& end, const int newLineThicknes, unsigned int newOffSetNumber = 0);

	const std::size_t getVectorSize() const;
	const Positions& operator[](unsigned int index) const;
	bool isLineVerticaleHorizontal() const;

	// Tester
	void print() const;

private:
	void addPositionsVerticaleHorizontal(const unsigned int startI, const unsigned int endI, const unsigned int startJ, const unsigned int endJ);
	void addPositions(const unsigned int startI, const unsigned int endI, const unsigned int startJ, const unsigned int endJ);

private:
	unsigned int lineThicknes;
	unsigned int offSetNumber; // used only when the line is horizontal or vertical
	Positions start;
	Positions end;
	PositionsPixelVector vector;
};

