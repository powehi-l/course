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

	read_from_diary("diary.txt", diary);
	getline(cin, date);
	one_diary.Setdate(date);
	getline(cin, str);
	while (str != ".") {
		one_diary.Addline(str);
		getline(cin, str);
	}

	int record;
	for (record = 0; record < diary.size(); record++) {
		if (one_diary.GetDate() == diary[record].GetDate())
			break;
	}
	if (record == diary.size())
		diary.push_back(one_diary);
	else
		diary[record] = one_diary;

	output_to_file("diary.txt", diary);
}