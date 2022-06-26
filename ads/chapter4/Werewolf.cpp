#include <iostream>
#include <vector>
#include <math.h>
#define max 200
using namespace std;

int statement[max];
bool check(vector<int> wolf, int N, int L)
{
    int lierinwolf = 0, temp, liers;
    vector<int> identity(N + 1, 1);
    vector<int> lier;
    for (int i = 1; i <= wolf.size(); i++)
        identity[wolf[i]] = -1;
    for (int i = 1; i <= N; i++)
    {
        temp = abs(statement[i]);
        if(statement[i] != identity[temp] * temp) lier.push_back(i);
    }

    if(lier.size() == L){
        for(int i = 1; i<=lier.size(); i++){
            if(identity[lier[i]] == -1 ) lierinwolf++;
        }
        if(lierinwolf > 0 && lierinwolf < lier.size()) return true;
    }
    return false;
}
bool bt(vector<int> wolf, int N, int M, int L, int k)
{
    if (wolf.size() == M)
    {
        if (check(wolf, N, L))
            return true;
        else
            return false;
    }
    for (; k > 0; k--)
    {
        wolf.push_back(k);
        if (bt(wolf, N, M, L, k))
            return true;
        else
        {
            wolf.pop_back();
        }
    }
    return false;
}
int main()
{
    int N, M, L;
    int lierInWolf = 0, lierInHuman = 0, wolves = 0;
    vector<int> wolf;
    cin >> N >> M >> L;
    for (int i = 1; i <= N; i++)
        cin >> statement[i];
    if (!bt(wolf, N, M, L, N))
        cout << "No Solution" << endl;
    else
    {
        for (int i = 0; i < wolf.size(); i++)
        {
            cout << wolf[i];
            if (i != wolf.size())
                cout << " ";
            else
                cout << endl;
        }
    }
}