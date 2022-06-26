#ifndef SKEW_HEAP_HPP
#define SKEW_HEAP_HPP

#include "commons.hpp"

struct SkewNode : public GeneralNode
{
    struct SkewNode *leftchild;
    struct SkewNode *rightchild;
    struct SkewNode *parent;
};

class SkewHeap : public GeneralHeap
{
private:
    struct SkewNode *root; // record the root of this heap
public:
    struct SkewNode **nodes = (struct SkewNode **)nodes;
    void initialize(Point *pl, int np)
    {
        struct SkewNode *node[np]; // declare a array of pointer which pointing to each node in the heap
        for (int i = 0; i < np; i++)
            node[i] = NULL; // make all these pointer to be NULL because there is no node in this heap yet
        nodes = node;
        root = NULL;
    }
    GeneralNode deleteMin()
    {
        struct SkewNode min = *root;
        root = merge(root->leftchild, root->rightchild);
        return min;
    }
    void insert(int index, ll dist)
    {
        SkewNode node; // create a new SkewNode to be added to the heap
        node.index = index;
        node.distance = dist;
        node.leftchild = node.rightchild = NULL;
        SkewNode *newnode = &node;
        nodes[index] = newnode;                  // record the node in nodes array
        this->root = merge(this->root, newnode); // merge this new node with origin heap
    }
    void decreaseKey(int idx, ll newVal)
    {
        this->nodes[idx]->distance = newVal; // change the state of that node
        struct SkewNode *cur = this->nodes[idx];
        struct SkewNode *temp = this->nodes[idx];
        while (cur->distance < cur->parent->distance)
        {
            percolateup(cur); // every time the current key is smaller then the parent, swap their position
        }
    }

    void percolateup(SkewNode *cur)
    {
        bool gpright;
        struct SkewNode *uptemp = cur->parent->parent;
        struct SkewNode *downtemp;
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
        return !this->root;
    }
    void free()
    {
        delete[] nodes;
        freenodes(root);
    }
    void freenodes(struct SkewNode *node)
    {
        if (node == NULL)
            return;
        else
        {
            freenodes(node->leftchild);
            freenodes(node->rightchild);
            delete node;
        }
    }
    struct SkewNode *merge(struct SkewNode *h1, struct SkewNode *h2)
    {
        struct SkewNode *temp;
        if (h1 == NULL)
            return h2;
        if (h2 == NULL)
            return h1;
        if (h1->distance < h2->distance)
        {
            temp = h1->leftchild;
            h1->leftchild = merge(h1->rightchild, h2);
            h1->rightchild = temp;
            return h1;
        }
        else
        {
            temp = h2->leftchild;
            h2->leftchild = merge(h2->rightchild, h1);
            h1->rightchild = temp;
            return h2;
        }
    }
};

#endif