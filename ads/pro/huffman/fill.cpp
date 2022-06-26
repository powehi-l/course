#include<iostream>
#include<algorithm>

using namespace std;
struct Node{
    float price;
    int dis;
};

bool comp(struct Node a, struct Node b){
    return a.dis<b.dis;
}

int main(){
    int i,j;
    int contain, Distance, dave, N;
    int oil_dis = 0, curnode = 0;
    float money = 0;
    scanf("%d %d %d %d", &contain, &Distance, &dave, &N);
    int period = contain*dave;

    struct Node *a = (struct Node*)malloc(sizeof(struct Node) * (N+1));
    for(i = 0;i<N;i++) scanf("%f %d", &a[i].price, &a[i].dis);
    a[N].dis = Distance;
    a[N].price = 0;
    sort(a,a+N,comp);
    if(a[0].dis !=0){
        cout<<"The maximum travel distance = 0";
        return 0;
    }

    while(1){
        int pe = curnode;
        if(a[pe+1].dis - a[curnode].dis > period){
            if(Distance - a[curnode].dis < period){
                money += a[curnode].price*(Distance-a[curnode].dis-oil_dis);
                printf("%.2f",money);
                return 0;
            }
            else{
                printf("The maximum travel distance = %d", a[curnode].dis+period);
                return 0;
            }
        }

        while(pe<N && a[++pe].dis - a[curnode].dis <= period ){
            if(a[pe].price < a[curnode].price){
                if(oil_dis >= a[pe].dis-a[curnode].dis){
                    oil_dis -= a[pe].dis-a[curnode].dis;
                }
                else{
                    money += 1.0*(a[pe].dis-a[curnode].dis-oil_dis)/dave * a[curnode].price;
                    oil_dis = 0;
                }
                curnode = pe;
                break;
            }
        }

        if(a[pe].dis - a[curnode].dis > period){
            money += 1.0 *(period - oil_dis)/dave * a[curnode].dis;
            oil_dis = period - (a[pe-1].dis - a[curnode].dis);
            curnode = pe-1;
        }
    }
    return 0;
}
