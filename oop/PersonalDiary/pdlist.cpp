#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include"Diary.h"

void list(int i, vector<Diary>& diary) {
	cout << diary[i].GetDate() << endl;
	for (int j = 0; j < diary[i].size(); j++) {
		cout << diary[i].GetText(j) << endl;
	}
	cout << "." << endl;
}

using namespace std;
int main(int argc, char*argv[]) {
	vector<Diary> diary;
	string option, begin, end;

	read_from_diary("diary.txt", diary);
	sort(diary.begin(), diary.end(), date_compare);
	cout << "input time duration?Y/N" << endl;
	cin >> option;

	if (option == "N")
		for(int i = 0; i<diary.size(); i++)
			list(i,diary);
	else {
		cin >> begin >> end;
		for (int i = 0; i < diary.size(); i++) {
			if (diary[i].GetDate() >= begin && diary[i].GetDate() <= end)
				list(i, diary);
		}
	}

	output_to_file("diary.txt", diary);
}