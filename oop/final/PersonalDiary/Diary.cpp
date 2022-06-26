#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<vector>
#include<algorithm>
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

//read diary from the file to memory
void read_from_diary(string filename, vector<Diary>& my_diary) {
	Diary diary;
	string str;
	fstream file;
	file.open(filename, ios::in);//open the file
	while (getline(file, str)) {//read date
		diary.Setdate(str);
		diary.reset();
		while (getline(file, str)) {//read the content line by line
			if (str == ".")//end with a line which is "."
				break;
			diary.Addline(str);//add this line to the content
		}
		my_diary.push_back(diary);//add this diary to the memory
	}
	file.close();//close the file
}

//output the file from memory to file
void output_to_file(string filename, vector<Diary>& my_diary) {
	sort(my_diary.begin(), my_diary.end(), date_compare);//sort the diary first
	Diary diary;
	string text, date;
	fstream file;
	file.open(filename, ios::out);//open file with output mode
	for (int i = 0; i < my_diary.size(); i++) {
		file << my_diary[i].GetDate() << endl;
		for (int j = 0; j < my_diary[i].size(); j++) {
			file << my_diary[i].GetText(j) << endl;
		}
		file << "." << endl;
	}
	file.close();
}

//compare two diary's date
bool date_compare(Diary& a1, Diary& a2) {
	string date1 = a1.GetDate();
	string date2 = a2.GetDate();
	if (date1.compare(date2) >= 0)
		return false;
	else return true;
}