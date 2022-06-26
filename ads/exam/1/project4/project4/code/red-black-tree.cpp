#include<iostream>
#include<vector>
#define maxlen 501
#define OVERFLOW 1000000007
using namespace std;

long long vr[maxlen][maxlen], vb[maxlen][maxlen];
//vr stands for red-root node conditions; vb stands for black-root node conditions; 

int main(){
	int N;//the number of internal nodes
	long long sum = 0;//the sum of all the conditions
	cin>>N;
	vb[1][1] = vr[0][1] = 1;//define the conditions when there is at least a nil child of the root
	vb[1][2] = 2;
	for(int i = 0; i < 100; i++){//i stands for the black height
		for(int j = 2; j < N; j++){
			//j stands for the internal nodes, since we have already considered the one_node condition, here j starts from 2
			for(int k = 1; k < j; k++){//k is used to scan the array and add up the conditions
				long long m1=(vb[i][k] * vb[i][j - k]) % OVERFLOW;//the child nodes of the red-root
				long long m2=(vr[i][k] + vb[i][k]) * (vr[i][j - k] + vb[i][j - k]) % OVERFLOW;//the child nodes of the black-root
				vr[i][j + 1] += m1 % OVERFLOW;
				vb[i + 1][j + 1] += m2 % OVERFLOW;
				vr[i][j + 1] %= OVERFLOW;
				vb[i + 1][j + 1] %= OVERFLOW;
			}
		}
	}
	for(int i = 0; i <= N; i++) sum = (sum + vb[i][N]) % OVERFLOW;//since the red-black-tree must have a black root, count all the conditions in array vb[]
	cout<<sum;
	return 0;
}
