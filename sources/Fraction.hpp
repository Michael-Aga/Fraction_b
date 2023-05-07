#include <iostream>
#include <stdio.h>
#include <utility>
#include <cmath>
#include <numeric>
#include <limits.h>

namespace ariel
{
    class Fraction
    {
    private:
        int numerator;   // The one on top
        int denominator; // The one on the bottom
        static const int DEFAULT_PRECISION = 1000;

    public:
        Fraction(const int numerator, const int denominator); // NOLINT

        Fraction() : numerator(1), denominator(1){};

        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int);
        void setDenominator(int);
        Fraction doubleToFraction(double decimal, int precision = DEFAULT_PRECISION) const;

        Fraction(const float num)
        {
            Fraction my_new_float = doubleToFraction(num);
            this->numerator = my_new_float.getNumerator();
            this->denominator = my_new_float.getDenominator();
        }

        Fraction operator+(const Fraction&) const;
        Fraction operator+(double) const;
        Fraction operator-(const Fraction &) const;
        Fraction operator-(int) const;
        Fraction operator-(double) const;
        Fraction operator*(const Fraction &) const;
        Fraction operator/(const Fraction &) const;

        bool operator==(const Fraction &) const;
        bool operator>(const Fraction &) const;
        bool operator>(double) const;
        bool operator<(const Fraction &) const;
        bool operator>=(const Fraction &) const;
        bool operator<=(const Fraction &) const;

        Fraction &operator++();   // Prefix
        Fraction operator++(int); // Postfix

        Fraction &operator--();   // Prefix
        Fraction operator--(int); // Postfix

        friend std::ostream &operator<<(std::ostream &, const Fraction &);
        friend std::istream &operator>>(std::istream &, Fraction &);

        friend Fraction operator+(double, const Fraction &);
        friend Fraction operator-(double, const Fraction &);
        friend Fraction operator*(double, const Fraction &);
        friend Fraction operator/(double, const Fraction &);

        friend bool operator>(double, const Fraction &);
        friend bool operator<(double, const Fraction &);
        friend bool operator>=(double, const Fraction &);
        friend bool operator<=(double, const Fraction &);
    };
};