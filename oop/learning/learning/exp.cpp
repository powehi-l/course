#include<iostream>
class x {
public:
	x();
};

x::x() {};

void f(int i) {
	if (i < 10) {
		goto jump1;
	}
	x x1;
jump1:
	switch (i) {
	case(1):
		x x2;
		break;
	case(2):
		x x3;
		break;
	}
}

int main() {
	f(9);
	f(11);
	getchar();
}