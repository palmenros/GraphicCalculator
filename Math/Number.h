#pragma once
#include <iostream>

class Number
{
protected:

	double r;
	double i;
public:
	Number(double real = 0);
	Number(double real, double imaginary);

	Number operator*(const Number& other) const;
	Number operator/(const Number& other) const;
	Number operator+(const Number& other) const;
	Number operator-(const Number& other) const;

	Number operator*(double f) const;
	Number operator/(double f) const;

	Number& operator*=(const Number& other);
	Number& operator/=(const Number& other);
	Number& operator+=(const Number& other);
	Number& operator-=(const Number& other);

	Number& operator*=(double f);
	Number& operator/=(double f);

	bool operator==(const Number& other) const;
	bool operator==(double f) const;

	Number power(const Number& exponent) const;

	Number getConjugate() const;

	double getReal() const;
	double getImaginary() const;

};

std::ostream& operator<<(std::ostream& out, const Number& n);
