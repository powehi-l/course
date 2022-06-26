#pragma once
#ifndef DIARY_H
#define DIARY_H

using namespace std;

class Diary {
private:
	string date;
	vector<string> content;
public:
	void reset();
	void Addline(string);
	void Setdate(string d);
	int size();
	string GetText(int i);
	string GetDate();
};

void read_from_diary(string filename, vector<Diary>& my_diary);
void output_to_file(string filrname, vector<Diary>& my_diary);
bool date_compare(Diary& a1, Diary& a2);

#endif

