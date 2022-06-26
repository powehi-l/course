#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
#include"Diary.h"

int main() {
	vector<Diary> diary;
	string str;
	cout << "please input the date of the diary to be removed" << endl;
	cin >> str;//get the diary to be removed
	read_from_diary("diary.txt", diary);
	for (int i = 0; i < diary.size(); i++) {
		if (diary[i].GetDate() == str) {//exam whether a diary with date str exist
			for (int j = i; j < diary.size()-1; j++)//if exist, delete it
				diary[j] = diary[j + 1];
			diary.pop_back();
			cout << "Success!" << endl;
			output_to_file("diary.txt", diary);
			return 0;
		}
	}
	cout << "Fail to delete this diary!" << endl;
	output_to_file("diary.txt", diary);
	return -1;
}