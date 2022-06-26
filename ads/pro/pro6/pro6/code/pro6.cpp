#include <iostream>
#include <vector>
#include <ctime>
int min_height;  // min_height of package
int fix_width;   // width of package

int N;//number of texture

using namespace std;

struct t{
    int width, height;
};
typedef t texture;

struct l{
    int height;
    int now_width;
};
typedef l* level;
struct p{
    vector<level> pack_level;
    int now_height;
    int level_num;
};
typedef p* pack;

void sortbyheight(texture T[]){// bubble sort in descending order of height
    texture temp;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if(T[j].height<T[j+1].height){
                temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;
            }
        }
    }
}

pack initialize(){//initialize the package
    pack p1 = new struct p;
    p1->level_num = 0;
    p1->now_height = 0;
    level l1 = new struct l;
    l1->height = 0;
    l1->now_width = 0;
    p1->pack_level.push_back(l1);

    return p1;
}

int main()
{
    clock_t start, finish;
    int K;
    cout << "Please enter the repeat times(The recommended value is around 1000):" << endl;
    cin >> K;
    cout << "Please enter the width and height of the package(eg:30 50):" << endl;
    cin >> fix_width >> min_height;
    cout << "Please enter the number of texture(>0)(The recommended value is larger than 10)" << endl;
    cin >> N;
    texture T[N];
    // The default box is directional, it will not rotate the box because it is bigger than the height
    cout << "Please enter texture 's width(0<w<=package_width) and height(0<h<=package_height) respectively(eg:3 5)" << endl;
    for (int i = 0; i < N; i++){
        cin >> T[i].width >> T[i].height; //Enter the parameters of texture
    }

    vector<pack> package; //Use vector to store packages
    start = clock(); 

    for (int t = 0; t < K; t++){//K iteration
        package.clear();
        sortbyheight(T); // bubble sort in descending order of height
        //next-fit
        pack p1;
        int h,w;
        if(t == 0)cout << "[package " << package.size() + 1 << "]" << endl;
        for (int i = 0; i < N; i++ ){
            if (i == 0)
            {
                p1 =  initialize();//initialize a package
                //package T[0]
                p1->now_height = T[0].height;
                p1->pack_level[p1->level_num]->height = T[0].height;
                p1->pack_level[p1->level_num]->now_width += T[0].width;
                if(t==0)cout <<"texture "<<i+1<< ": (" << T[0].width << "," << T[0].height << ")" << endl; //Print the coordinates in the upper right corner of the texture
            }
            else{
                if(p1->pack_level[p1->level_num]->now_width + T[i].width <=fix_width){//In this level,if pack T[i],the width will not exceed the given width after packing
                    p1->pack_level[p1->level_num]->now_width += T[i].width;//pack T[i]
                }
                else{//In this level,if after packing T[i],the width exceeds the given width after packing
                    if(p1->now_height+T[i].height<=min_height){//We create a new layer for pack T[i](If after creating the new layer,the height will not exceed the given height)
                        p1->level_num++;
                        level l1 = new struct l;
                        l1->height = l1->now_width = 0;
                        p1->pack_level.push_back(l1);//create a new layer 
                        p1->now_height+= T[i].height;//pack T[i]
                        p1->pack_level[p1->level_num]->height = T[i].height;
                        p1->pack_level[p1->level_num]->now_width += T[i].width;
                    }
                    else{//If it will not be packed in this package
                        package.push_back(p1);
                        if(t==0) cout << "[package " << package.size() + 1 << "]" << endl;
                        p1 =  initialize();//create a new package and pack T[i]
                        p1->now_height = T[i].height;
                        p1->pack_level[p1->level_num]->height = T[i].height;
                        p1->pack_level[p1->level_num]->now_width += T[i].width;
                    }
                    
                }
                h = p1->now_height - p1->pack_level[p1->level_num]->height;
                w = p1->pack_level[p1->level_num]->now_width;
                if(t==0) cout << "texture " << i + 1 << ": (" << w << "," << h + T[i].height << ")" << endl;//Print the coordinates in the upper right corner of the texture
            }
        }
        package.push_back(p1);
    }
    finish = clock();
    cout << "number of packages: " << package.size() << endl;
    cout <<"For "<<K<<" round ,the time cost is:" << double(finish-start)*1000 / CLOCKS_PER_SEC<<" ms"<<endl;
    //system("pause");
}

