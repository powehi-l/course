//空格， 标点转换
//界面美观，上面粘贴文本， 下面显示运行完的结果
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stdlib.h>

using namespace std;
string form(string a) {
	for (int j = 0; j < a.size(); j++) {
		int flag = 0;
		if (a[j] == -29)
			flag = 2;
		else if (a[j] == -30) {
			if (a[j + 2] == -103)
				flag = 5;
			else if (a[j + 2] == -100)
				flag = 6;
		}
		else if (a[j] == -17) {
			if (a[j + 2] == -116)
				flag = 1;
			else if (a[j + 2] == -97)
				flag = 3;
			else if (a[j + 2] == -127)
				flag = 4;
		}
		switch (flag) {
			case 1:a = a.erase(j, 3); a = a.insert(j,","); break;
			case 2:a = a.erase(j, 3); a = a.insert(j, "."); break;
			case 3:a = a.erase(j, 3); a = a.insert(j, "?"); break;
			case 4:a = a.erase(j, 3); a = a.insert(j, "!"); break;
			case 5:a = a.erase(j, 3); a = a.insert(j, "'"); break;
			case 6:a = a.erase(j, 3); a = a.insert(j, "\""); break;
		}
	}
	for (int i = 0; i< a.size(); i++) {
		if (a[i] == ',' || a[i] == '.' || a[i] == '?' || a[i] == '!')
			if (a[i + 1] != ' ')
				a = a.insert(i + 1, " ");
		if (a[i] == ' ') {
			while (a[i + 1] == ' ') {
				a = a.erase(i, 1);
			}
			if (a[i + 1] == ',' || a[i + 1] == '.' || a[i + 1] == '?' || a[i + 1] == '!') {
				a = a.erase(i, 1);
				i--;
			}
		}
	}
	return a;
}
int main() {
	vector<string> data;
	string one;
	ifstream input;
	input.open("data.txt");
	if (!input.is_open()) {
		cout << "文件打开失败了哦，看看是不是名字错了" << endl;
		system("pause");
		return 0;
	}
	cout << "read the file..." << endl;
	while (getline(input, one))
	{
		data.push_back(one);
	}
	input.close();

	cout << "fomalize the file..." << endl;
	for (int i = 0; i < data.size(); i++)
		data[i] = form(data[i]);

	ofstream output;
	output.open("result.txt");
	for (int i = 0; i < data.size(); i++)
		output << data[i] << endl;
	output.close();
	cout << "fomalize finish" << endl << "去result里面看看结果哦" << endl;
	system("pause");
	return 0;
}