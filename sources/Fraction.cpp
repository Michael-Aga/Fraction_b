#include "Fraction.hpp"

using namespace std;
using namespace ariel;

int Fraction::getNumerator() const
{
    return this->numerator;
};

int Fraction::getDenominator() const
{
    return this->denominator;
};

void Fraction::setNumerator(int toSetNumerator)
{
    this->numerator = toSetNumerator;
}

void Fraction::setDenominator(int toSetDenominator)
{
    if (toSetDenominator != 0)
    {
        this->denominator = toSetDenominator;
    }
    else
    {
        throw runtime_error("You cant divide by zero !");
    }
}

Fraction Fraction::doubleToFraction(double num, int precision) const
{ // Convert the decimal to a numerator and denominator with the given precision default as request 3 numbers after the dot
    if (num == 0.0)
    {
        return Fraction(0, 1);
    }

    int numerator = round(num * precision);
    int denominator = precision;

    int simplifier = gcd(numerator, denominator); // We use this to simplify the fraction

    return Fraction(numerator / simplifier, denominator / simplifier);
}

Fraction::Fraction(const int numerator, const int denominator)
{
    if (denominator == 0)
    {
        throw invalid_argument("You cant divide by zero !");
    }

    int sign = (numerator < 0) ^ (denominator < 0) ? -1 : 1;
    int simplifier = gcd(abs(numerator), abs(denominator));

    this->numerator = sign * abs(numerator) / simplifier;
    this->denominator = abs(denominator) / simplifier;
}

Fraction Fraction::operator+(const Fraction &other) const
{
    int common_denominator = lcm(this->denominator, other.getDenominator());
    int left_numerator = this->numerator * (common_denominator / this->denominator);
    int right_numerator = other.getNumerator() * (common_denominator / other.getDenominator());
    int summed_numerator;

    if (__builtin_add_overflow(left_numerator, right_numerator, &summed_numerator)) {
        throw std::overflow_error("Addition overflow");
    }

    int simplifier = gcd(summed_numerator, common_denominator);

    return Fraction(summed_numerator / simplifier, common_denominator / simplifier);
};

Fraction Fraction::operator+(double num) const
{
    return *this + doubleToFraction(num);
};

Fraction Fraction::operator-(const Fraction &other) const // Basically this is like the + operator but with a - command in the summed_numerator
{
    int common_denominator = lcm(this->denominator, other.getDenominator());
    int left_numerator = this->numerator * (common_denominator / this->denominator);
    int right_numerator = other.getNumerator() * (common_denominator / other.getDenominator());
    int summed_numerator;

    if (__builtin_sub_overflow(left_numerator, right_numerator, &summed_numerator)) {
        throw std::overflow_error("Subtraction overflow");
    }

    int simplifier = gcd(summed_numerator, common_denominator);

    return Fraction(summed_numerator / simplifier, common_denominator / simplifier);
};

Fraction Fraction::operator-(int num) const
{
    return *this - Fraction(num * this->getDenominator(), this->getDenominator());
};

Fraction Fraction::operator-(double num) const
{
    return *this - doubleToFraction(num);
}

Fraction Fraction::operator*(const Fraction &other) const
{
    int multi_numerator, multi_denominator;

    if (__builtin_mul_overflow(this->getNumerator(), other.getNumerator(), &multi_numerator) ||
        __builtin_mul_overflow(this->getDenominator(), other.getDenominator(), &multi_denominator)) {
        throw std::overflow_error("Multiplication overflow");
    }

    int simplifier = gcd(multi_numerator, multi_denominator);
    return Fraction(multi_numerator / simplifier, multi_denominator / simplifier);
};

Fraction Fraction::operator/(const Fraction &other) const
{
    if (other.getNumerator() == 0) {
        throw runtime_error("You cant divide by zero !");
    }

    int multi_numerator, multi_denominator;

    if (__builtin_mul_overflow(this->getNumerator(), other.getDenominator(), &multi_numerator) ||
        __builtin_mul_overflow(this->getDenominator(), other.getNumerator(), &multi_denominator)) {
        throw std::overflow_error("Division overflow");
    }

    int simplifier = gcd(multi_numerator, multi_denominator);
    return Fraction(multi_numerator / simplifier, multi_denominator / simplifier);
}

bool Fraction::operator==(const Fraction &other) const
{
    bool sameSign = (this->getNumerator() < 0) == (other.getNumerator() < 0);
    bool sameFraction = (abs(this->getNumerator()) == abs(other.getNumerator())) && (abs(this->getDenominator()) == abs(other.getDenominator()));
    return sameSign && sameFraction;
};

bool Fraction::operator>(const Fraction &other) const
{
    int common_denominaor = lcm(this->getDenominator(), other.getDenominator());
    int firstNumerator = this->getNumerator() * (common_denominaor / this->getDenominator());
    int secondNumerator = other.getNumerator() * (common_denominaor / other.getDenominator());

    return firstNumerator > secondNumerator;
}

bool Fraction::operator>(double num) const
{
    return *this > doubleToFraction(num);
};

bool Fraction::operator<(const Fraction &other) const
{
    return !(*this > other) && !(*this == other);
};

bool Fraction::operator>=(const Fraction &other) const
{
    return (*this == other) || (*this > other);
}

bool Fraction::operator<=(const Fraction &other) const
{
    return (*this == other) || (*this < other);
};

Fraction &Fraction::operator++()
{ // Prefix
    this->numerator += this->getDenominator();

    int simplify = gcd(this->numerator, this->getDenominator());
    this->numerator /= simplify;
    this->denominator /= simplify;

    return *this;
}

Fraction Fraction::operator++(int) // Postfix
{
    Fraction temp = *this;
    ++(*this);
    return temp;
}

Fraction &Fraction::operator--() // Prefix
{
    this->numerator -= this->denominator;

    int simplify = gcd(this->numerator, this->denominator);
    this->numerator /= simplify;
    this->denominator /= simplify;

    return *this;
};

Fraction Fraction::operator--(int) // Postfix
{
    Fraction temp = *this;
    --(*this);
    return temp;
};

ostream &ariel::operator<<(std::ostream &os, const Fraction &myFraction)
{
    int numerator = myFraction.getNumerator();
    int denominator = myFraction.getDenominator();

    if (denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }

    os << numerator << '/' << denominator;
    return os;
}

std::istream &ariel::operator>>(std::istream &is, Fraction &myFraction)
{
    int numerator, denominator;

    is >> numerator;

    if (is.eof() || !(is >> ws >> denominator) || denominator == 0)
    {
        is.setstate(ios::failbit);
        throw runtime_error("Invalid fraction input");
    }

    else
    {
        int sign = (numerator < 0) ^ (denominator < 0) ? -1 : 1;
        int simplifier = gcd(abs(numerator), abs(denominator));
        numerator = sign * abs(numerator) / simplifier;
        denominator = abs(denominator) / simplifier;

        myFraction.setNumerator(numerator);
        myFraction.setDenominator(denominator);
    }

    return is;
}

bool ariel::operator>(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction > myFraction;
}

bool ariel::operator<=(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction <= myFraction;
}

bool ariel::operator>=(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction >= myFraction;
}

bool ariel::operator<(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction < myFraction;
}

Fraction ariel::operator/(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction / myFraction;
}

Fraction ariel::operator-(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction - myFraction;
}

Fraction ariel::operator+(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction + myFraction;
}

Fraction ariel::operator*(const double num, const Fraction &myFraction)
{
    Fraction doubleAsFraction = myFraction.doubleToFraction(num);
    return doubleAsFraction * myFraction;
};