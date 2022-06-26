#include"Fraction.h"


int Fraction::gcd(int a, int b) {
	if (a == 0 || b == 0)//if any a or b is 0 return 0
		return 0;
	if (b > a)
		return gcd(b, a);//besure b is smaller one
	if (a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}

void Fraction::simplify() {
	int a = abs(gcd(abs(numerator), abs(denominator)));
	if (a == 0)
		return;
	if ((numerator>0&& denominator > 0) || (numerator<0&&denominator<0))//fraction is positive
		numerator = abs(numerator / a);
	else
		numerator = -abs(numerator / a);
	denominator /= a;
	denominator = abs(denominator);
}

Fraction::Fraction (const Fraction& p) {
	numerator = p.numerator;
	denominator = p.denominator;
	this->simplify();
}

Fraction::~Fraction() {

}

double Fraction::To_double() const {
	return double(numerator) / double(denominator);
}

string Fraction::To_string() const {
	return to_string(numerator) + '/' + to_string(denominator);
}

const Fraction operator+(const Fraction& a, const Fraction& b) {
	Fraction result;
	result.denominator = a.denominator * b.denominator;
	result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
	result.simplify();
	return result;
}

const Fraction operator-(const Fraction& a, const Fraction& b) {
	Fraction result;
	result.denominator = a.denominator * b.denominator;
	result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
	result.simplify();
	return result;
}
const Fraction operator*(const Fraction& a, const Fraction& b) {
	Fraction result;
	result.denominator = a.denominator * b.denominator;
	result.numerator = a.numerator * b.numerator;
	result.simplify();
	return result;
}
const Fraction operator/(const Fraction& a, const Fraction& b) {
	Fraction result;
	result.denominator = a.denominator * b.numerator;
	result.numerator = a.numerator * b.denominator;
	result.simplify();
	return result;
}

bool Fraction::operator<(const Fraction& a) {
	return (numerator * a.denominator < a.numerator* denominator) ? true : false;
}
bool Fraction::operator<=(const Fraction& a) {
	return (numerator * a.denominator <= a.numerator* denominator) ? true : false;
}
bool Fraction::operator==(const Fraction& a) {
	return (numerator * a.denominator == a.numerator * denominator) ? true : false;
}
bool Fraction::operator!=(const Fraction& a) {
	return (numerator * a.denominator != a.numerator * denominator) ? true : false;
}
bool Fraction::operator>=(const Fraction& a) {
	return (numerator * a.denominator >= a.numerator * denominator) ? true : false;
}
bool Fraction::operator>(const Fraction& a) {
	return (numerator * a.denominator > a.numerator * denominator) ? true : false;
}

istream& operator>>(istream& in, Fraction& o) {
	int nume, demo;
	char oper;
	in >> nume >> oper >> demo;
	if (oper != '/')
		cout << "Error operator" << endl;//the format is not correct
	else
		o = Fraction(nume, demo);//construct the fraction
	return in;
}
ostream& operator<<(ostream& out, const Fraction& o) {
	if (o.numerator == 0)
		return out << 0;
	else if (o.denominator == o.numerator)
		return out << 1;
	else if (o.denominator == 1)
		return out << o.numerator;
	else
		out << o.numerator << '/' << o.denominator;
	return out;
}

bool Fraction::check(string str) {
	for (int i = 0; i < str.length(); i++)
		if ((str[i] < '0' || str[i]>'9') && str[i] != '.')//if there is other char except '0'-'9' and '.'
			return false;
	return true;
}

bool Fraction::convertfromstr(string str) {
	if (str.length() > 10) {
		cout << "Too long decimal! Unable to convert to a fraction" << endl;
		return false;
	}
	if (!check(str)) {
		cout << "invalid str" << endl;
		return false;
	}
	int pointposition;
	string integer, dfraction;
	int i, d;
	pointposition = str.find('.');//get the position of '.'
	integer = str.substr(0, pointposition);//get integer part
	dfraction = str.substr(pointposition + 1);//get decimal fraction part
	i = stoi(integer);//
	d = stoi(dfraction);
	denominator = pow(10, dfraction.length());
	numerator = i * pow(10, dfraction.length()) + d;//get the numerator to be integer
	simplify();
	return true;
}