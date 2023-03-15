#include "positionsPixelVector.h"

PositionsPixelVector::PositionsPixelVector(const std::size_t newCapacity)
	: capacity(newCapacity), size(0)
{
	this->positions = new Positions[this->capacity];
}

PositionsPixelVector::PositionsPixelVector(const PositionsPixelVector& other)
{
	this->copy(other);
}

PositionsPixelVector& PositionsPixelVector::operator=(const PositionsPixelVector& other)
{
	if (this != &other) {
		this->destroy();
		this->copy(other);
	}
	return *this;
}

PositionsPixelVector::~PositionsPixelVector()
{
	this->destroy();
}

void PositionsPixelVector::addPosition(const Positions& position)
{
	if (this->size == this->capacity) {
		this->resize();
	}
	this->positions[size] = position;
	this->size++;
}

const Positions& PositionsPixelVector::operator[](unsigned int index) const
{
	if (index >= this->size) {
		throw "invalid index";
	}
	return this->positions[index];
}

const std::size_t PositionsPixelVector::getSize() const
{
	return this->size;
}

void PositionsPixelVector::print() const
{
	for (std::size_t i = 0; i < this->size; ++i)
	{
		this->positions[i].print();
	}
}

void PositionsPixelVector::resize()
{
	this->capacity *= 2;
	Positions* holdPositions = new Positions[this->capacity];
	for (std::size_t i = 0; i < this->size; ++i)
	{
		holdPositions[i] = this->positions[i];
	}
	delete[] this->positions;
	this->positions = new Positions[this->capacity];
	for (std::size_t i = 0; i < this->size; ++i)
	{
		this->positions[i] = holdPositions[i];
	}
	delete[] holdPositions;
}

void PositionsPixelVector::copy(const PositionsPixelVector& other)
{
	this->size = other.size;
	this->capacity = other.capacity;
	this->positions = new Positions[this->capacity];
	for (std::size_t i = 0; i < this->size; ++i)
	{
		this->positions[i] = other.positions[i];
	}
}

void PositionsPixelVector::destroy()
{
	delete[] this->positions;
}
