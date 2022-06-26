#include <cstddef>
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

// SWAP performs an exchange on a and b
template <typename T>
void SWAP(T &a, T &b)
{
    T __swap_temp = (a);
    (a) = (b);
    (b) = (__swap_temp);
}

// The node definition of Huffman tree
struct HuffmanNode
{
    char c = '!';                           // store the character
    int w = 0;                              // store the frequecy

    struct HuffmanNode *left = nullptr;     // point to the left of this node
    struct HuffmanNode *right = nullptr;    // point to the right of this node
};

// The node definition of prefix tree
struct PrefixNode
{
    struct PrefixNode * left = nullptr;     // '0' goes left
    struct PrefixNode * right = nullptr;    // '1' goes right
};

// Variable definition
static  int N;                               // store the number of character input
char    c[63];                               // use to store the character
static  int f[256];                          // use to store the frequency
int     min_length;                          // the minimum length of total code
bool    result[1000];                        // whether it is right for
struct  HuffmanNode **heap;                  // the heap array
int     heapsize;                            // the size of the min-heap
ofstream outfile("process.txt", ios::trunc);

// Function declaration
struct  HuffmanNode *createHuf();                      // bulid the huffman tree
void    Insertheap(struct HuffmanNode *Node);          // insert a new node into min-heap
struct  HuffmanNode *deletemin();                      // delete the min of min-heap
bool    check();                                       // check the input code
int     find_length(struct HuffmanNode *root, int depth); // work out the min length of total code;
bool    check_and_insert(PrefixNode * prefixTree,string code);
                                                      // check a code string into the prefix tree , and , if valid ,insert it
void delete_tree(PrefixNode * node);                  // free a tree , avoid memory leak
int main()
{
    cin >> N;
    ofstream outfile("process.txt", ios::trunc);
    // build min heap
    heapsize = 0;
    heap = new HuffmanNode *[N];
    for (int i = 0; i < N; i++)
    {
        cin >> c[i];
        cin >> f[c[i]];
        HuffmanNode *T = new HuffmanNode;
        T->c = c[i];
        T->w = f[c[i]];
        Insertheap(T);
    }
    struct HuffmanNode *ROOT;
    ROOT = createHuf();     //create the huffman tree
    min_length = find_length(ROOT, 0); //get the minimal length for comparation of the submission
    int num;
    cin >> num;
    for (int i = 0; i < num; i++) result[i] = check();//check whether the case satisfy the huffman code
    for (int i = 0; i < num; i++)
    {
        if (result[i]) cout << "Yes";
        else cout << "No";
        if(i != num) cout << endl;
    }
    outfile.close();
    system("pause");
    return 0;
}

struct HuffmanNode *createHuf()
{
    struct HuffmanNode *T;
    int n;
    n = heapsize;
    int i;
    for (i = 1; i < n; i++)
    {
        T = new HuffmanNode;
        T->left = deletemin();//get the minimal one
        T->right = deletemin();//get the second minimal one
        T->w = T->left->w + T->right->w;//get sum frequency of left and right
        Insertheap(T);//insert T into heap for further compare
    }
    T = deletemin();
    return T;
}

void Insertheap(HuffmanNode *Node)
{
    outfile << "insert character : " << Node->c << " "
            << "weight : " << Node->w << endl;
    heap[heapsize] = Node;//insert this node into end of heap
    int cur = heapsize;
    int parent = (cur + 1) / 2 - 1;
    while (cur != 0 && heap[cur]->w < heap[parent]->w)//while this cur is not root and frequency of cur is smaller than its parent
    {
        SWAP(heap[cur], heap[parent]);//swap cur and its parent
        cur = parent;//update cur and parent
        parent = (cur + 1) / 2 - 1;
    }
    heapsize++;//after insertion, the size of heap increase
}

HuffmanNode *deletemin()
{
    HuffmanNode *gn = heap[0];//store the minimal one
    if (gn->c != '!')
    {
        outfile << "delete character : " << gn->c << " "
                << "weight : " << gn->w << endl;
    }
    else
    {
        outfile << "delete character : " << gn->c << " "
                << "weight : " << gn->w << " (left child : c : " << gn->left->c << " w : " << gn->left->w
                << " and right child : c : " << gn->c << "  w : " << gn->right->w << ")" << endl;
    }
    heap[0] = heap[heapsize - 1];//replace the minimal one with the node in the end
    int cur = 0;
    int newVal = heap[heapsize - 1]->w;
    heapsize--;//after deletemin, the size of heap minus one
    int leftc = cur * 2 + 1;//update left child
    int rightc = cur * 2 + 2;//update right child

    while (cur < heapsize && (leftc < heapsize && heap[leftc]->w < newVal || rightc < heapsize && heap[rightc]->w < newVal))//while the frequency of child is smaller than cur
    { // percolate down
        int tg;
        if (leftc < heapsize && rightc < heapsize)//be sure the tg is smaller one
        {
            if (heap[leftc]->w < heap[rightc]->w) tg = leftc;
            else
                tg = rightc;
        }
        else if (leftc < heapsize) tg = leftc;
        else tg = rightc;
        SWAP(heap[cur], heap[tg]);//swap cur and child
        cur = tg;//update cur and leftchild and rightchild
        leftc = cur * 2 + 1;
        rightc = cur * 2 + 2;
    }
    return gn;
}

bool check_and_insert(string code, PrefixNode * tree){
    PrefixNode * c = tree;
    int flag = 1;
    for(int i=0;i<code.size();i++){
        if(flag && c != tree && (c->left == nullptr && c->right == nullptr))return false;//if this code is already exist in previous code, than return flase
        switch (code[i]) {
            case '0':
                if(!c->left) c->left = new PrefixNode, flag = 0;//go left
                c = c->left;
                break;
            case '1':
                if(!c->right) c->right = new PrefixNode , flag = 0;//go right
                c = c->right;
                break;
            default:return false;
        }
    }
    if(c->left || c->right) return false;//if this code is not a leaf node, return false
    return true;
}
void delete_tree(PrefixNode * tree){//recursively delete the prefixNode tree
    if(!tree)return ;
    if(tree->left) delete_tree(tree->left);
    if(tree->right) delete_tree(tree->right);
    delete tree;
}
bool check()
{
    char c;
    int i;
    int wpl = 0;
    int flag = 1;
    PrefixNode * ptree = new PrefixNode;
    string code;
    for ( i = 0; i < N && flag; i++)
    {
        cin >> c >> code;
        outfile << code << endl;
        if( !check_and_insert(code,ptree))flag = 0;//for each code, check whether it is right
        wpl = wpl + code.length() * f[c];//update the cost
    }
    for(;i<N;i++)cin >> c >> code;
    delete_tree(ptree);
    return flag && wpl == min_length;
}

int find_length(struct HuffmanNode *root, int depth)
{
    if (root->left == NULL && root->right == NULL) return root->w * depth;
    return find_length(root->left, depth + 1) + find_length(root->right, depth + 1);
}