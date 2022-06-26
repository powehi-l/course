#ifndef SKEW_HEAP_HPP
#define SKEW_HEAP_HPP

#include "commons.hpp"

struct SkewNode : public GeneralNode
{
    struct SkewNode *leftchild;  // pointer to left child
    struct SkewNode *rightchild; // pointer to right child
    struct SkewNode *parent;     // pointer to its parent
    SkewNode()
    {
        leftchild = rightchild = NULL;
        parent = NULL;
    }
};

class SkewHeap : public GeneralHeap
{
private:
    struct SkewNode *root; // record the root of this heap
    struct SkewNode *actualNodes;

public:
    SkewHeap()
    {
        HeapName = "SkewHeap";
    }
    void initialize(Point *pl, int np)
    {
        nodes = new GeneralNode *[np]; // allocate space for pointers pointing to the nodes
        max_size = np;
        actualNodes = new SkewNode[np]; // allocate space for those nodes
        for (int i = 0; i < np; i++)
        {
            nodes[i] = actualNodes + i; // make every pointer pointing to corresponding nodes
            nodes[i]->index = i;
        }

        root = NULL;
    }
    // delete the root of the heap
    GeneralNode deleteMin()
    {
        SkewNode min = *root;                            // create a node to contain that min item
        root = merge(root->leftchild, root->rightchild); // merge the rest nodes to make it a leftist heap again
        if (root != nullptr)                             // after merge, cut thr root from its origin parent
            root->parent = nullptr;
        return min;
    }
    // insert a node to the heap whose index is index and distance is dist
    void insert(int index, ull dist)
    {
        if (nodes[index]->inHeap) // if this node is already in the heap, then no need to insert
            return;
        SkewNode *inserted = static_cast<SkewNode *>(nodes[index]); // make the node to be insert a new heap
        inserted->distance = dist;                                  // initialize the distance, index and state of this node
        inserted->inHeap = true;
        inserted->index = index;
        SkewNode *newroot = merge(root, inserted); // merge the new node and the origin heap
        root = newroot;
    }
    // decrease the distanceof a key with index idx to newVal
    void decreaseKey(int idx, ull newVal)
    {
        SkewNode *cur = static_cast<SkewNode *>(nodes[idx]);
        if (!cur->inHeap) // if this node is not in the heap, there is no need to decrease
            return;
        cur->distance = newVal;                                       // change the state of that node
        while (cur != root && cur->distance <= cur->parent->distance) // percolate
        {
            if (cur->distance < cur->parent->distance)
                cur = percolateup(cur);
            else
            {
                if (cur->index < cur->parent->index)
                    cur = percolateup(cur);
                else
                    break;
            }
        }
    }

    SkewNode *percolateup(SkewNode *cur)
    {
        // record the state of current point
        SkewNode *temp = cur;
        unsigned int tempindex = cur->index;
        ull tempdistance = cur->distance;

        // replace the state of current point with its parent state
        cur->index = cur->parent->index;
        cur->distance = cur->parent->distance;
        nodes[cur->parent->index] = cur;

        // replace the state of parent point with current point's state
        cur = cur->parent;
        cur->index = tempindex;
        cur->distance = tempdistance;
        nodes[cur->index] = cur;
        return cur;
    }
    // determine whether this heap is empty
    bool isEmpty()
    {
        return !this->root;
    }
    // free all the memory
    void free()
    {
        delete[] nodes;
        delete[] actualNodes;
        nodes = nullptr;
        actualNodes = nullptr;
    }
    SkewNode *merge(SkewNode *h1, SkewNode *h2) // merge tow heaps
    {
        SkewNode *temp;
        if (h1 == NULL)
            return h2;
        if (h2 == nullptr)
            return h1;
        // merge two heaps where smaller root being the parent
        if (h1->distance <= h2->distance)
        {
            if (h1->distance == h2->distance && h1->index > h2->index)
                return merge1(h2, h1);
            else
                return merge1(h1, h2);
        }
        else
            return merge1(h2, h1);
    }

    SkewNode *merge1(SkewNode *h1, SkewNode *h2)
    {
        SkewNode *temp = h1->leftchild;            // record left child
        h1->leftchild = merge(h1->rightchild, h2); // merge the right child of h1 with h2
        h1->leftchild->parent = h1;
        h1->rightchild = temp; // left the origin left child to be right child
        if (h1->rightchild != nullptr)
            h1->rightchild->parent = h1;
        return h1;
    }
    void reset()
    {
        SkewNode **bn = reinterpret_cast<SkewNode **>(nodes);
        for (int i = 0; i < max_size; i++)
        {
            auto &c = bn[i];
            c->distance = -1;
            c->index = i;
            c->inHeap = false;
            c->leftchild = c->rightchild = c->parent = nullptr;
        }
        root = nullptr;
    }
};

#endif
