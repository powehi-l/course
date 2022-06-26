#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include "commons.hpp"

struct BinaryNode : public GeneralNode{
    BinaryNode * parent;
    BinaryNode * left;
    BinaryNode * right;
};

class BinaryHeap : public GeneralHeap{

    private:
    BinaryNode * root ;

    public:

    void initialize(Point *pl,int np){
        root = nullptr;
        if(nodes)delete[] nodes;
        else nodes = new GeneralNode*[np];
        for(int i =0 ;i< np;i++)nodes[i] = new BinaryNode;
        BinaryNode** bn = reinterpret_cast<BinaryNode**>(nodes);
        for(int i=0;i<np;i++){
            bn[i]->distance = -1;
            bn[i]->index = i;
            bn[i]->left = bn[i]->right = nullptr;
        }
    }
    GeneralNode deleteMin(){
        
    }
    void insert(int index,ll dist){
        
    }
    void decreaseKey(int idx,ll newVal){

    }
    bool isEmpty(){

    }
    void free(){
        
    }

};


#endif