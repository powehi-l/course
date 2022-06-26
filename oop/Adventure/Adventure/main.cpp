#include"castle.h"
#include"Room.h"

using namespace std;

int main() {
	castle Castle;//initialize a castle object
	Castle.construct();//construct the rooms of this castle
	Castle.randowPM();//initialize the position of princess and monster
	Castle.run();//begin our game
	system("pause");
	return 0;
}