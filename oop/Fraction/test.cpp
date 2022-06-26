#include"Fraction.h"

int main() {
	Fraction a;
	cout << "1.1 the default ctor" << endl;
	cout << "a = " << a << endl;
	//ctor takes two integers as parameters
	cout << "1.2 ctor takes two integers as parameters" << endl;
	cout << "Input two integers as parameters:";
	int m, n;
	cin >> m >> n;
	Fraction b(m, n);
	cout << "b = " << b << endl;
	//copy ctor
	cout << "1.3 copy ctor b to c " << endl;
	Fraction c(b);
	cout << "c = " << c << endl;

	//inserter and extractor for streams
	cout << "2.1 inserter and extractor for streams " << endl;
	Fraction x, y;
	cout << "Input two fractions x, y (example:1/2):" << endl;
	cout << "Nonminimalist fractions will be automatically simplified." << endl;
	cin >> x >> y;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

	//arithmetical operators: + - * /
	cout << "3.1 arithmetical operators" << endl;
	cout << "x + y = " << x + y << endl;
	cout << "x - y = " << x - y << endl;
	cout << "x * y = " << x * y << endl;
	cout << "x / y = " << x / y << endl;

	//relational operators : < <= == != >= >
	cout << "3.2 relational operators " << endl;
	cout << "x < y is " << (x < y) << endl;
	cout << "x <= y is " << (x <= y) << endl;
	cout << "x == y is " << (x == y) << endl;
	cout << "x != y is " << (x != y) << endl;
	cout << "x >= y is " << (x >= y) << endl;
	cout << "x > y is " << (x > y) << endl;

	//type cast to double
	cout << "4.1 type cast to double " << endl;
	double p = x.To_double();
	cout << "x type cast to double p." << endl << "p = " << p << endl;
	//type cast to string
	cout << "4.2 type cast to string " << endl;
	string q = x.To_string();
	cout << "x type cast to string q." << endl << "q = " << q << endl;

	//conversion from a finite decimal string like : 1.414
	cout << "5.1 conversion from a finite decimal string " << endl;
	cout << "Input a finite decimal string like 1.414:" << endl;
	string str;
	cin >> str;
	Fraction d;
	d.convertfromstr(str);
	cout << "d = " << d << endl;

	system("pause");
	return 0;
}