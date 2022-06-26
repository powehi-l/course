#include <iostream>
#include <string>
#include <vector>
using namespace std;

class file
{
public:
    vector<string> words;
    int wordsnum;

public:
    string changeform(string s);
    string removepunc(string s);
    float getfre(string s);
    void addwords(string s);
};

void file::addwords(string s)
{
    string s1, s2;
    s1 = removepunc(s);
    s1 = changeform(s);
    words.push_back(s2);
    wordsnum++;
}

float file::getfre(string s)
{
    int count = 0;
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == s)
            count++;
    }
    return wordsnum / count;
}

string file::removepunc(string s)
{
    string s1;
    if (s[s.size() - 1] == ',' || s[s.size() - 1] == '.' || s[s.size() - 1] == '?' || s[s.size() - 1] == '!')
        s1 = s.substr(0, s.size() - 1);
    return s1;
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
    float frequen1, frequen2;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        float DD = 0;
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
            frequen1 = files[t1]->getfre(files[t1]->words[j]);
            for (int k = 0; k < files[t2]->wordsnum; k++)
            {
                if (files[t1]->words[j] == files[t2]->words[k])
                {
                    frequen2 = files[t2]->getfre(files[t2]->words[k]);
                }
            }
            DD += frequen1 * frequen2;
        }

        cout << "case" << i << ": " << DD << endl;
        system("pause");
        return 0;
    }
}