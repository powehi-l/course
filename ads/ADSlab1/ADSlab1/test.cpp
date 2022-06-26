#include <ctime>
#include <functional>
#include<iostream>
#include<string>
#include<fstream>
#include <utility>
#include<vector>
#include <chrono>
#include<queue>

using namespace std;
int nv,ne;

struct Point{
    bool vis;
    unsigned int dis = -1;
    vector<int> adjs;
    vector<int> edges;
};

vector<Point> points;
void dijk(int start_point){
    priority_queue<pair<int,int>,vector<pair<int,int>>,std::greater<pair<int, int>>> q;
    ofstream ofs("sample.log");
    q.push({0,start_point});
    while(!q.empty()){
        auto p = q.top();
        q.pop();
        auto idx = p.second;
        auto dist = p.first;
        auto &pt = points[idx];
        if(! pt.vis){
            //ofs << "dequeue " << p.second  << " " << p.first << endl;
            pt.vis = true;
            pt.dis = dist;
            for(int i=0;i< pt.adjs.size();i++){
                int w = pt.dis + pt.edges[i];
                if(!points[pt.adjs[i]].vis && w < points[pt.adjs[i]].dis){
                    points[pt.adjs[i]].dis = w;
                    //ofs << "decrease " << p.second << "->" << pt.adjs[i] << " = " << w << endl;
                    q.push({w,pt.adjs[i]});
                }
            }
        }
        
    }
}
int main(){
    cout << "running test"  << endl;
    string filename = "USA-road-d.CAL.gr";
    ifstream ifs(filename);
    string s;
    ifs >> s >> s >> nv >> ne;
    points.resize(nv);
    cout << "reading file " << endl;
    for(int i=0;i<ne;i++){
        Point np;
        int a,b,c;
        ifs >> s  >> a >> b >> c;
        points[a -1].adjs.push_back(b -1);
        points[a-1].edges.push_back(c);
        points[b -1].adjs.push_back(a -1);
        points[b-1].edges.push_back(c);
    }
    ifs.close();
    auto clk = chrono::high_resolution_clock::now();
    cout << "dijk start !" << endl;
    dijk(0);
    ofstream ofs("sample.out");
    cout << "finished in " << std::chrono::duration_cast<std::chrono::milliseconds>((chrono::high_resolution_clock::now() - clk)).count() << " milliseconds!" << endl;
    for(int i=0;i<points.size();i++){
        //ofs << i + 1 << " " << points[i].dis << endl;
    }
    ofs.close();
    return 0;
}   
