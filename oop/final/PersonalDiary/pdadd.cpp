#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<vector>
#include<algorithm>
#include "Diary.h"

using namespace std;

int main() {
	vector<Diary> diary;
	Diary one_diary;
	string date;
	string str;

	read_from_diary("diary.txt", diary);//first read and final output

	getline(cin, date);//get the date
	one_diary.Setdate(date);
	getline(cin, str);//get content line by line
	while (str != ".") {
		one_diary.Addline(str);
		getline(cin, str);
	}

	int record;
	for (record = 0; record < diary.size(); record++) {//exam whether the date is already in diary
		if (one_diary.GetDate() == diary[record].GetDate())
			break;
	}
	if (record == diary.size())
		diary.push_back(one_diary);//insert into diary
	else
		diary[record] = one_diary;//update the diary with same date

	output_to_file("diary.txt", diary);
}