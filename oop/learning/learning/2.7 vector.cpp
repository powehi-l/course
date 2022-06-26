#include<string>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

int main() {
	// to print a source code with line position

	//vector<string> v;
	//ifstream in("2.6 file1.cpp");

	//string line;
	//while (getline(in, line))
	//	v.push_back(line);
	//for (int i = 0; i < v.size(); i++)
	//	cout << i << ":" << v[i] << endl;
	//getchar();

	//vector output the source file with space 
	/*vector<string> words;
	ifstream in("2.6 file1.cpp");
	string word;
	while (in >> word)
		words.push_back(word);
	for (int i = 0; i < words.size(); i++)
		cout << words[i] << endl;
	getchar();*/

	/*vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << ", ";
	cout << endl;
	for (int i = 0; i < v.size(); i++)
		v[i] = v[i] * 10;
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << ", ";
	cout << endl;
	getchar();*/
	string s = "asdasfhjaBUYHV";
	string s1;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 65 && s[i] <= 90)
			s[i] += 32;
	}
	cout << s << endl;
	system("pause");
}