#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int main(int argc, char* argv[]){
    int w,h;
    srand((unsigned int)time(0));
    for (int i = 0; i < atoi(argv[1]);i++){
        h = rand() % 50 + 1;
        w = rand() % 30 + 1;
        printf("%d %d\n", w, h);
    }
    
    //system("pause");
}
