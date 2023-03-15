#pragma once

#include "positions.h"
#include <cstddef>

class PositionsPixelVector
{
public:
	PositionsPixelVector(const std::size_t newCapacity = 64);
	PositionsPixelVector(const PositionsPixelVector& other);
	PositionsPixelVector& operator=(const PositionsPixelVector& other);
	~PositionsPixelVector();

	void addPosition(const Positions& position);

	const Positions& operator[](unsigned int index) const;
	const std::size_t getSize() const;

	// Tester
	void print() const;

private:
	void resize();
	void copy(const PositionsPixelVector& other);
	void destroy();

private:
	std::size_t capacity;
	std::size_t size;
	Positions* positions;
};

