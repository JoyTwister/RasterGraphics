#pragma once

class Positions
{
public:
	Positions(const unsigned int _x = 0, const unsigned int _y = 0);

	bool operator==(const Positions& other) const;
	bool operator>(const Positions& other) const;
	bool operator<(const Positions& other) const;

	const unsigned int getX() const;
	const unsigned int getY() const;

	// Tester
	void print() const;

private:
	unsigned int x;
	unsigned int y;
};

