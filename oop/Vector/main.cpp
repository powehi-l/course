#include<iostream>
#include"Vector.h"

using namespace std;

class human {
private:
	int height;
	float weight;
public:
	human() {
		height = 0;
		weight = 0;
	}

	human(int h, float w):height(h),weight(w){}
	int getHeight() {
		return height;
	}

	float getwight() {
		return weight;
	}
};

int main() {
	Vector<int> a;
	cout << "--------------push_back---------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "current a's m_nSize: " << a.size() << endl;
		a.push_back(i);
	}
	cout << endl;
	cout << "----------------------other two vector construct-------------------" << endl;
	Vector<int> b(8);
	cout << "construct vector b with size 8, show the size and capability of b: " << b.size()<< "   "<<b.capa() << endl;
	Vector<int> c(a);
	cout << "construct vector c from a, show the size and capability of c: " << c.size() << "   " << c.capa() << endl << endl;

	cout << "--------------opeator[] and at--------------" << endl;
	cout << a[9] << endl;
	cout << a[10] << endl;
	cout << a.at(9) << endl;
	cout << a.at(10) << endl << endl;

	cout << "--------------empty, size, clear -------------" << endl;
	cout << "current a's m_nSize: " << a.size() << endl;
	cout << "a is_empty: " << a.empty() << endl;
	cout << "clear a. " << endl;
	a.clear();
	cout << "a is_empty: " << a.empty() << endl;

	cout << "----------------inflate-------------------------" << endl;
	cout << "current size and capability of c: " << c.size() <<"   "<< c.capa() << endl;
	cout << "after push_back one element 11." << endl;
	c.push_back(11);
	cout << "current size and capability of c: " << c.size() << "   " << c.capa() << endl << endl;


	cout << "The function is correct, and now test the other data type" << endl;
	cout << "create a vector of class human vector_human and push a instance with 180 height and 60 weight into the vector" << endl;
	Vector<human> vector_human;
	human *d = new human(180,60);
	vector_human.push_back(*d);
	cout << "current size and capability of vector_human: " << vector_human.size() << "    " << vector_human.capa() << endl;
	cout << "get the height and wight of the first one of vector_human: " << vector_human[0].getHeight() << "   " << vector_human[0].getwight() << endl;
}