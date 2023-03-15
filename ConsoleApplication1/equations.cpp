#include "equations.h"
#include <iostream>

Equations::Equations()
	: coefficientX(0), coefficientY(0), constant(0) {}

void Equations::print() const
{
	std::cout << this->coefficientX << "x + " << this->coefficientY << "y + " << this->constant << " =  0\n";
}
