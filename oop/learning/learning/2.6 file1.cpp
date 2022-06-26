#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main() {
	ifstream in("2.6 file.cpp");
	ofstream out("2.6 file1.cpp");
	string s;
	while (getline(in, s))
		out << s << "\n";
	getchar();
}
