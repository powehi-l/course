#pragma once
#ifndef FRACTION_H
#define FRACTION_H
#include<iostream>
#include<string>
#include<math.h>

using namespace std;

class Fraction {
private:
	int numerator;//the numerator
	int denominator;//the denominator
public:
	Fraction() :numerator(0), denominator(1) {};//default situation
	Fraction(int a, int b) :numerator(a), denominator(b) {
		if (denominator == 0) {
			throw exception("Denominator should not be zero");
		}
		simplify();
	}
	~Fraction();

	int gcd(int a, int b);//to get the greatest common division
	void simplify();//simplify the ctor to numerator and denomminator's gcd is 1
	Fraction(const Fraction& p);//copy from an exist fraction

	const friend Fraction operator+(const Fraction& a, const Fraction& b);//operator for plus two fraction
	const friend Fraction operator-(const Fraction& a, const Fraction& b);
	const friend Fraction operator*(const Fraction& a, const Fraction& b);
	const friend Fraction operator/(const Fraction& a, const Fraction& b);

	//operators compare two fractions
	bool operator<(const Fraction& a);
	bool operator<=(const Fraction& a);
	bool operator==(const Fraction& a);
	bool operator!=(const Fraction& a);
	bool operator>=(const Fraction& a);
	bool operator>(const Fraction& a);
	
	//change the fraction to double and string
	double To_double() const;
	string To_string() const;

	//input and output a fraction with operator ">>" "<<"
	friend istream& operator>>(istream& in, Fraction& o);
	friend ostream& operator<<(ostream& out, const Fraction& o);

	//convert a string to a fraction with simplification
	bool convertfromstr(string str);
	bool check(string str);
}; 
#endif // 
