#include<iostream>
#include<vector>
#include<string>

using namespace std;
//object student
class student {
private:
	//record the student's name and every course name with score
	string stuname;
	struct course {
		string couname;
		int score;
	};
	vector<course> courses;
public:
	//initialize a student with his/her name
	student(string name);

	//get the sum of all score of this student
	int getsum();

	//add a course and its score into the object
	void addcourse(string couname, int score);

	//print a student's information including student's name and every course and average score
	void print();
};

student::student(string name) {
	stuname = name;
}

int student::getsum(){
	int sum = 0;
	int coursenum = courses.size();
	for (int i = 0; i < coursenum; i++)
		sum += courses[i].score;
	return sum;
}

void student::addcourse(string couname, int score) {
	course course;
	course.couname = couname;
	course.score = score;
	courses.push_back(course);
}

void student::print() {
	cout << stuname << "\t";
	for (int i = 0; i < courses.size(); i++) {
		cout << courses[i].couname << "\t" << courses[i].score << "\t";
	}
	cout << "average: " << 1.0 * getsum() / courses.size()<< endl;
}

int main() {
	vector<student*> stuvector; //a collection of pointers of student object
	student *stu = 0;
	string name;
	int score;

	while (1) {
		cout << "Enter students name(if finished, enter exit):" << endl;
		cin >> name; //read a student's name
		if (name == "exit")// if enter exit, stop read more student
			break;
		stu = new student(name);//create the object for a new student
		cout << "Enter the course name and score(end with 0 0):" << endl;
		cin >> name >> score;//read a course name and its score
		while (name != "0") {
			stu->addcourse(name, score);//add this course into object
			cin >> name >> score;//read next course
		}

		stuvector.push_back(stu);// add this student object into vector
	}

	//print the shift
	int i;
	cout << "no\t" << "name\t" << "course\t"<< "score\t"<<	endl;
	for (i = 0; i < stuvector.size(); i++) {
		cout << i + 1 << "\t";
		stuvector[i]->print();
	}
	system("pause");
	return 0;

}
