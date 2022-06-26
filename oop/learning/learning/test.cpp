#include<iostream>
using namespace std;

int main() {
	int* i;
	int p = 0;
	i = &p;
	delete(i);
	cout << "delete finish" << endl;
}