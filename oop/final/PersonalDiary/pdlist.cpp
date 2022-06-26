#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include"Diary.h"

using namespace std;

//list i-th diary
void list(int i, vector<Diary>& diary) {
	cout << diary[i].GetDate() << endl;
	for (int j = 0; j < diary[i].size(); j++) {
		cout << diary[i].GetText(j) << endl;
	}
	cout << "." << endl;
}

int main(int argc, char*argv[]) {
	vector<Diary> diary;
	string option, begin, end;

	read_from_diary("diary.txt", diary);
	sort(diary.begin(), diary.end(), date_compare);//sort the diary first
	cout << "input time duration?Y/N" << endl;//whether need a duration
	cin >> option;

	if (option == "N")//no duration, output all the diary
		for(int i = 0; i<diary.size(); i++)
			list(i,diary);
	else {//output diary between begin and end date
		cin >> begin >> end;
		for (int i = 0; i < diary.size(); i++) {
			if (diary[i].GetDate() >= begin && diary[i].GetDate() <= end)
				list(i, diary);
		}
	}

	output_to_file("diary.txt", diary);
}