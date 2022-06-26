#ifndef LEFTIST_HEAP_HPP
#define LEFTIST_HEAP_HPP

#include "commons.hpp"

struct LeftistNode : public GeneralNode
{
    unsigned int npl;
    struct LeftistNode *leftchild;  // pointer to leaeft child
    struct LeftistNode *rightchild; // pointer to right child
    struct LeftistNode *parent;     // pointer to its parent
};

class LeftistHeap : public GeneralHeap
{
private:
    struct LeftistNode *root; // record the root of this heap

public:
    struct LeftistNode **nodes = (struct LeftistNode **)nodes; // convert the nodes from general type to leftist type
    void initialize(Point *pl, int np)
    {
        struct LeftistNode *node[np]; // declare a array of pointer which pointing to each node in the heap
        for (int i = 0; i < np; i++)
            node[i] = NULL; // make all these pointer to be NULL because there is no node in this heap yet
        nodes = node;
        root = NULL;
    }
    GeneralNode deleteMin()
    {
        struct LeftistNode min = *root;                  // create a node to contain that min item
        root = merge(root->leftchild, root->rightchild); // merge the rest nodes to make it a leftist heap again
        return min;
    }
    void insert(int index, ll dist)
    {
        LeftistNode node; // create a new leftistNode to be added to the heap
        node.index = index;
        node.distance = dist;
        node.leftchild = node.rightchild = NULL;
        node.npl = 0;
        LeftistNode *newnode = &node;
        nodes[index] = newnode;                  // record the node in nodes array
        this->root = merge(this->root, newnode); // merge this new node with origin heap
    }
    void decreaseKey(int idx, ll newVal)
    {
        this->nodes[idx]->distance = newVal; // change the state of that node
        struct LeftistNode *cur = this->nodes[idx];
        struct LeftistNode *temp = this->nodes[idx];
        while (cur->distance < cur->parent->distance)
        {
            percolateup(cur); // every time the current key is smaller then the parent, swap their position
        }
    }
    // there may be many bug, one way to implement this easily is to use merge too

    void percolateup(struct LeftistNode *cur)
    {
        bool gpright;
        struct LeftistNode *uptemp = cur->parent->parent;
        struct LeftistNode *downtemp;
        if (cur == cur->parent->rightchild)
        {
            if (uptemp->rightchild == cur->parent)
                gpright = 1;
            downtemp = cur->parent->leftchild;

            cur->leftchild->parent = cur->rightchild->parent = cur->parent;
            cur->parent->leftchild = cur->parent = cur;

            cur->parent->leftchild = cur->leftchild;
            cur->parent->rightchild = cur->rightchild;
            cur->leftchild = downtemp;
            cur->rightchild = cur->parent;

            cur->parent = uptemp;
            if (gpright)
                uptemp->rightchild = cur;
            else
                uptemp->leftchild = cur;
        }
        else
        {
            if (uptemp->rightchild == cur->parent)
                gpright = 1;
            downtemp = cur->parent->rightchild;

            cur->leftchild->parent = cur->rightchild->parent = cur->parent;
            cur->parent->rightchild = cur->parent = cur;

            cur->parent->leftchild = cur->leftchild;
            cur->parent->rightchild = cur->rightchild;
            cur->rightchild = downtemp;
            cur->leftchild = cur->parent;

            cur->parent = uptemp;
            if (gpright)
                uptemp->rightchild = cur;
            else
                uptemp->leftchild = cur;
        }
    }
    bool isEmpty()
    {
        return !this->root; // if root is null, return 1, else return 0
    }
    void free()
    {
    }
    struct LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
    {
        if (h1 == NULL)
            return h2;
        if (h2 == NULL)
            return h1;
        if (h1->distance < h1->distance) // be sure the first one contianing smaller key
            return merge1(h1, h2);
        else
            return merge1(h2, h1);
    }

    struct LeftistNode *merge1(struct LeftistNode *h1, struct LeftistNode *h2)
    {
        if (h1->leftchild == NULL) // if the left child of h1 is empty, then just lat h2 be the leftchild
        {
            h1->leftchild = h2;
            h2->parent = h1;
        }
        else
        {
            h1->rightchild = merge(h1->rightchild, h2);   // recursively merge the right child and h2
            if (h1->rightchild->npl > h1->leftchild->npl) // adjust the position of left child and right child according to npl
            {
                struct LeftistNode *temp = h1->rightchild;
                h1->rightchild = h1->leftchild;
                h1->leftchild = temp;
            }
            h1->npl = h1->rightchild->npl; // update the npl of h1 with smaller npl of its right child
        }
        return h1;
    }
};

#endif