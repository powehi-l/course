#pragma once
#ifndef DIARY_H
#define DIARY_H

using namespace std;

class Diary {
private:
	string date;//record the date of the diary
	vector<string> content;//record content of diary
public:
	void reset();//clear the content of diary
	void Addline(string);//add another line to content
	void Setdate(string d);
	int size();//return the lines of content
	string GetText(int i);//get i-th line's content
	string GetDate();//get date of the diary
};

void read_from_diary(string filename, vector<Diary>& my_diary);//read diary from the file to memory
void output_to_file(string filrname, vector<Diary>& my_diary);//output the file from memory to file
bool date_compare(Diary& a1, Diary& a2);//compare two diary's date

#endif

