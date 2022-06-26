#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

class file
{
public:
	vector<string> words;
	int wordsnum;
	int repeat;

public:
	string changeform(string s);
	string removepunc(string s);
	float getfre(string s, int i);
	float norm();
	void addwords(string s);
};

void file::addwords(string s)
{
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ',' || s[i] == '.' || s[i] == '?' || s[i] == '!')
			return;
	}
	string s1, s2;
	s1 = removepunc(s);
	s2 = changeform(s1);
	words.push_back(s2);
	wordsnum++;
	
}

float file::getfre(string s, int i)
{
	int count = 0;
	for (int j = 0; j < i; j++)
		if (words[j] == words[i])
			return 0;
	for (int j = i; j < words.size(); j++)
	{
		if (words[j] == s) {
			count++;
		}
	}
	return 1.0*count/(wordsnum);
}

float file::norm() {
	float fre = 0;
	for (int i = 0; i < wordsnum; i++) {
		fre += pow(getfre(words[i], i), 2);
	}
	return sqrt(fre);
}

string file::removepunc(string s)
{
	string s1;
	if (s[s.size() - 1] == ',' || s[s.size() - 1] == '.' || s[s.size() - 1] == '?' || s[s.size() - 1] == '!')
		s = s.substr(0, s.size() - 1);
	return s;
}

string file::changeform(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 65 && s[i] <= 90)
			s[i] += 32;
	}
	return s;
}

int main()
{
	vector<string> name;
	vector<file *> files;
	file *f;
	int n;
	string curname, word;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		f = new file();
		cin >> curname;
		name.push_back(curname);
		cin >> word;
		while (word != "#")
		{
			f->addwords(word);
			cin >> word;
		}
		files.push_back(f);
	}

	int m;
	string f1, f2;
	int t1, t2;
	float frequen1, frequen2, DD, norm1, norm2;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		DD = 0;
		cin >> f1 >> f2;
		for (int j = 0; j < name.size(); j++)
		{
			if (name[j] == f1)
				t1 = j;
			if (name[j] == f2)
				t2 = j;
		}

		for (int j = 0; j < files[t1]->wordsnum; j++)
		{
			frequen1 = frequen2 = 0;
			frequen1 = files[t1]->getfre(files[t1]->words[j],j);
			for (int k = 0; k < files[t2]->wordsnum; k++)
			{
				if (files[t1]->words[j] == files[t2]->words[k])
				{
						frequen2 = files[t2]->getfre(files[t2]->words[k], k);
						break;
				}
			}
			DD += frequen1 * frequen2;
		}
		norm1 = files[t1]->norm();
		norm2 = files[t2]->norm();
		cout << "Case " << i+1 << ": " << setprecision(3) << acos(DD/norm1/norm2) << endl;
	}
	system("pause");
	return 0;
}