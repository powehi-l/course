#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include"Diary.h"

int main() {
	vector<Diary> diary;
	string date;
	read_from_diary("diary.txt", diary);
	sort(diary.begin(), diary.end(), date_compare);//sort the diary before output
	for (int i = 0; i < diary.size(); i++) {
		cout << diary[i].GetDate() << endl;//output date one by one
	}
	output_to_file("diary.txt", diary);
}