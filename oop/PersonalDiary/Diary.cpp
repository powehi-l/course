#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>
#include "Diary.h"

using namespace std;

void Diary::reset() {
	content.clear();
}

void Diary::Setdate(string d) {
	date = d;
}

void Diary::Addline(string Newline) {
	content.push_back(Newline);
}

string Diary::GetDate() {
	return date;
}

string Diary::GetText(int i) {
	return content[i];
}

int Diary::size() {
	return content.size();
}

void read_from_diary(string filename, vector<Diary>& my_diary) {
	Diary diary;
	string str;
	fstream file;
	file.open(filename, ios::in);
	while (getline(file, str)){
		diary.Setdate(str);
		diary.reset();
		while (getline(file, str)) {
			if (str == ".")
				break;
			diary.Addline(str);
		}
		my_diary.push_back(diary);
	}
	file.close();
}

void output_to_file(string filename, vector<Diary>& my_diary) {
	sort(my_diary.begin(), my_diary.end(), date_compare);
	Diary diary;
	string text, date;
	fstream file;
	file.open(filename, ios::out);
	for (int i = 0; i < my_diary.size(); i++) {
		file << my_diary[i].GetDate() << endl;
		for (int j = 0; j < my_diary[i].size(); j++) {
			file << my_diary[i].GetText(j) << endl;
		}
		file << "." << endl;
	}
	file.close();
}

bool compare(string data1, string data2) {
	vector<string> time1, time2;
	string str;
	stringstream in1(data1);
	stringstream in2(data2);
	while (in1 >> str)
		time1.push_back(str);
	while (in2 >> str)
		time2.push_back(str);
	for (int i = 0; i < 3; i++){
		if (time1[i] > time2[i])
			return false;
		else if (time1[i] == time2[i])
			continue;
		else
			return true;
	}



}

bool date_compare(Diary& a1, Diary& a2) {
	string date1 = a1.GetDate();
	string date2 = a2.GetDate();
	return compare(date1, date2);
}