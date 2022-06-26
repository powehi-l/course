#include<iostream>
#include<string>
#include <cstring>
#include <algorithm>

using namespace std;

const int course_num = 3;
const int student_num = 10;

/*	object recording a student's name and scores.
	methods constructing a student object, getting
	a student's name, getting a student's score for
	a certain object and getting average score of a student*/
class student {
private:
	string name;
	int score[course_num];
public:
	student(string name, int *score);
	string getname();
	int getscore(int k);
	double getaverage();
};
//implement of methods
student::student(string name, int *score){
	this->name = name;
	int i;
	for (i = 0; i < course_num; i++) {
		this->score[i] = score[i];
	}
}

string student::getname() {
	return this->name;
}

int student::getscore(int k) {
	return this->score[k];
}

double student::getaverage() {
	double sum = 0;
	int i;
	for (i = 0; i < course_num; i++) {
		sum += this->score[i];
	}
	return sum / course_num;
}

//record every student
student *stu[student_num];

int main() {
	string name;
	int score[course_num];
	int sumScore[course_num], maxScore[course_num], minScore[course_num];//record every course's sum, min and max score
	int i, j;
	//initialeze
	memset(minScore, 101, course_num * sizeof(int));
	memset(sumScore, 0, course_num * sizeof(int));
	memset(maxScore, 0, course_num * sizeof(int));
	//recording every student's name and scores
	for (i = 0; i < student_num; i++) {
		cin >> name;
		for (j = 0; j < course_num; j++) {
			cin >> score[j];
		}
		stu[i] = new student(name, score);
	}
	//begin print
	cout << "no\t" << "name\t" << "score1\t" << "score2\t" << "score3\t" << "average\t"<<endl;
	//print every student's name, scores and averaage scores
	for (int i = 0; i < student_num; i++) {
		cout << i + 1 << "\t" << stu[i]->getname() << "\t";
		for (int j = 0; j < course_num; j++) {
			score[j] = stu[i]->getscore(j);
			sumScore[j] += score[j];
			maxScore[j] = max(maxScore[j], score[j]);
			minScore[j] = min(minScore[j], score[j]);
			cout <<score[j] << "\t";
		}
		cout << stu[i]->getaverage() << endl;
	}
	//print every course's average score for all students
	cout << "\t" << "average\t";
	for (int i = 0; i < course_num; i++) {
		double sum = 0;
		for (j = 0; j < student_num; j++) {
			sum += stu[j]->getscore(i);
		}
		cout << sum / student_num << "\t";
	}
	cout << endl;
	//print every course's minimal score for all students
	cout << "\t" << "min\t";
	for (int i = 0; i < course_num; i++) {
		cout << minScore[i] << "\t";
	}
	cout << endl;
	//print every course's maximal score for all students
	cout << "\t" << "max\t";
	for (int i = 0; i < course_num; i++) {
		cout << maxScore[i] << "\t";
	}
	cout << endl;

	system("pause");
	return 0;
}