#include<iostream>
#include<cstdlib>
using namespace std;

int main() {
	/*//output in different format for same object
	cout << dec << 11 << endl;
	cout << oct << 11 << endl;
	cout << hex << 11 << endl;

	//force a integer to be a char
	cout << "non-printing char (escape): " << char(97) << endl;

	//combination of character array
	cout << "this is far too long to puit on a"
		"single line but it can be broken up\n";

	//cin
	int number;
	cout << "input a number:";
	cin >> number;
	cout << dec<<number;*/

	//system() function  -- in <cstdlib>
	system("python");

	getchar();
	getchar();
	return 0;
}