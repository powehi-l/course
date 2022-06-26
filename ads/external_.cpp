#include<cstdio>
#include<vector>
#include<queue>
#include<iostream>

#define Size 10000
using namespace std;

int main(){
    int N, M, out_num, number = 0, index = 0;
    scanf("%d%d", &N, &M);
    int array[Size];
    for(int i = 0; i < N; i++){
        cin >> array[i];
    }
    priority_queue<int,vector<int>, greater<int>> queue;
    vector<int> cur_run, next_run;
    for(; index < M; index++)
        queue.push(array[index]);
    while(number < N){
        out_num = queue.top();
        queue.pop();
        number++;
        cur_run.push_back(out_num);
        if(index < N){
            if(array[index] < out_num){
                next_run.push_back(array[index++]);
            }
            else{
                queue.push(array[index++]);
            }
        }
        

        if(queue.empty()){
            for(int j = 0; j < cur_run.size(); j++){
                if(j != cur_run.size()-1)
                    cout << cur_run[j] << " ";
                else
                    cout << cur_run[j] << endl;
            }
            cur_run.clear();
            for(int j = 0; j < next_run.size(); j++){
                queue.push(next_run[j]);
            }
            next_run.clear();
        }
    } 
    
}