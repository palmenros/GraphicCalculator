#include "Number.h"
#include <complex>
#include "Double.h"

Number::Number(double real)
	: r(real), i(0)
{
}

Number::Number(double real, double imaginary)
	: r(real), i(imaginary)
{
}

Number Number::operator*(const Number& other) const
{
	return Number(
		r * other.r - i * other.i,
		r * other.i + i * other.r
	);
}

Number Number::operator/(const Number& other) const
{
	Number result = *this;
	result *= other.getConjugate();
	result /= (other.r * other.r + other.i * other.i);
	return result;
}

Number Number::operator+(const Number& other) const
{
	return Number(r + other.r, i + other.i);
}

Number Number::operator-(const Number& other) const
{
	return Number(r - other.r, i - other.i);
}

Number Number::operator*(double f) const
{
	return Number(r * f, i * f);
}

Number Number::operator/(double f) const
{
	return Number(r / f, i / f);
}

Number& Number::operator*=(const Number& other)
{
	*this = *this * other;
	return *this;
}

Number& Number::operator/=(const Number& other)
{
	*this = *this / other;
	return *this;
}

Number& Number::operator+=(const Number& other)
{
	r += other.r;
	i += other.i;
	return *this;
}

Number& Number::operator-=(const Number& other)
{
	r -= other.r;
	i -= other.i;
	return *this;
}

Number& Number::operator*=(double f)
{
	r *= f;
	i *= f;
	return *this;
}

Number& Number::operator/=(double f)
{
	r /= f;
	i /= f;
	return *this;
}

bool Number::operator==(const Number& other) const
{
	return almostEqualDouble(r, other.r) && almostEqualDouble(i, other.i);
}

bool Number::operator==(double f) const
{
	return almostEqualDouble(r, f) && almostEqualDouble(i, 0.f);
}

Number Number::power(const Number& exponent) const
{
	std::complex<double> b(r, i);
	std::complex<double> e(exponent.r, exponent.i);

	std::complex<double> res = std::pow(b, e);

	return Number(res.real(), res.imag());
}

Number Number::getConjugate() const
{
	return Number(r, -i);
}

double Number::getReal() const
{
	return r;
}

double Number::getImaginary() const
{
	return i;
}

std::ostream& operator<<(std::ostream& out, const Number& n)
{
	double r = n.getReal();
	double i = n.getImaginary();

	if (almostEqualDouble(0.0, r) && almostEqualDouble(0.0, i))
	{
		out << 0;
		return out;
	}

	if (almostEqualDouble(0.0, i))
	{
		//Print only r
		out << r;
		return out;
	}

	if (almostEqualDouble(0.0, r))
	{
		//Print only i
		if (almostEqualDouble(i, 1.0))
		{
			out << "i";
		}
		else if (almostEqualDouble(i, -1.0))
		{
			out << "-i";
		}
		else
		{
			out << i << "i";
		}
		return out;
	}

	//Print both

	out << r;
	if(i > 0.0)
	{
		out << "+";
	}

	if (almostEqualDouble(i, 1.0))
	{
		out << "i";
	}
	else if (almostEqualDouble(i, -1.0))
	{
		out << "-i";
	}
	else
	{
		out << i << "i";
	}


	return out;
}
