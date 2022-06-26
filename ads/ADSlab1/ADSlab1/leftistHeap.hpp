#ifndef LEFTIST_HEAP_HPP
#define LEFTIST_HEAP_HPP

#include "commons.hpp"

struct LeftistNode : public GeneralNode
{
    unsigned int npl;
    LeftistNode *leftchild;  // pointer to left child
    LeftistNode *rightchild; // pointer to right child
    LeftistNode *parent;     // pointer to its parent
    LeftistNode()
    {
        npl = 0;
        leftchild = rightchild = NULL;
        parent = NULL;
    }
};

class LeftistHeap : public GeneralHeap
{
private:
    struct LeftistNode *root; // record the root of this heap
    struct LeftistNode *actualNodes;

public:
    LeftistHeap()
    {
        HeapName = "LeftistHeap";
    }
    void initialize(Point *pl, int np)
    {
        nodes = new GeneralNode *[np];     // allocate space for pointers pointing to the nodes
        actualNodes = new LeftistNode[np]; // allocate space for those nodes
        for (int i = 0; i < np; i++)
        {
            nodes[i] = actualNodes + i; // make every pointer pointing to corresponding nodes
            nodes[i]->index = i;        // make the index of nodes and pointer the same
        }
        max_size = np;
        root = NULL; // empty heap after initialize
    }
    GeneralNode deleteMin()
    {
        LeftistNode min = *root;                         // create a node to contain that min item
        root = merge(root->leftchild, root->rightchild); // merge the rest nodes to make it a leftist heap again
        if (root != nullptr)
            root->parent = nullptr;
        return min;
    }
    // insert a node to the heap whose index is index and distance is dist
    void insert(int index, ull dist)
    {
        if (nodes[index]->inHeap) // is this node is already in the heap, then no need to insert
            return;
        LeftistNode *inserted = static_cast<LeftistNode *>(nodes[index]); // make the node to be insert a new heap
        inserted->distance = dist;                                        // initialize the distance, index and state of this node
        inserted->inHeap = true;
        inserted->index = index;
        LeftistNode *newroot = merge(root, inserted); // merge the new node and the origin heap
        root = newroot;                               // make the new root to be the root of current heap
    }
    // decrease the distanceof a key with index idx to newVal
    void decreaseKey(int idx, ull newVal)
    {
        LeftistNode *cur = static_cast<LeftistNode *>(nodes[idx]); // create a pointer to the point to be decrease
        if (!cur->inHeap)                                          // if this node is not in the heap, there is no need to decrease
            return;
        cur->distance = newVal;                                       // change the distance of that node
        while (cur != root && cur->distance <= cur->parent->distance) // percolate
        {
            if (cur->distance < cur->parent->distance)
                cur = percolateup(cur);
            else
            {
                // if the distance of current's and parent's distance is the same, percolate up if the index
                // of the child is smaller than the parent's. This promise the index dequeue increasingly
                if (cur->index < cur->parent->index)
                    cur = percolateup(cur);
                else
                    break;
            }
        }
    }
    // percolate up a node in the heap
    LeftistNode *percolateup(LeftistNode *cur)
    {
        // record the state of current point
        LeftistNode *temp = cur;
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
        return !this->root; // if root is null, return 1, else return 0
    }
    // free all the memory
    void free()
    {
        delete[] nodes;
        delete[] actualNodes;
        nodes = nullptr;
        actualNodes = nullptr;
    }

    struct LeftistNode *merge(LeftistNode *h1, LeftistNode *h2) // merge two heaps
    {
        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;
        // merge two heaps where smaller root being the parent
        if (h1->distance <= h2->distance)
        {
            if (h1->distance == h2->distance && h1->index > h2->index) // promise smaller index to be the root
                return merge1(h2, h1);
            else
                return merge1(h1, h2);
        }
        else
            return merge1(h2, h1);
    }

    struct LeftistNode *merge1(struct LeftistNode *h1, struct LeftistNode *h2)
    {
        if (h1->leftchild == nullptr) // if the left child of h1 is empty, then just lat h2 be the leftchild
        {
            h1->leftchild = h2;
            h2->parent = h1;
        }
        else
        {
            h1->rightchild = merge(h1->rightchild, h2); // recursively merge the right child and h2
            h1->rightchild->parent = h1;
        }
        if (h1->rightchild == NULL)
            return h1;
        if (h1->rightchild->npl > h1->leftchild->npl) // adjust the position of left child and right child according to npl
        {
            struct LeftistNode *temp = h1->rightchild;
            h1->rightchild = h1->leftchild;
            h1->leftchild = temp;
        }
        h1->npl = h1->rightchild->npl + 1; // update the npl of h1 with smaller npl of its right child
        return h1;
    }
    void reset()
    {
        LeftistNode **bn = reinterpret_cast<LeftistNode **>(nodes);
        for (int i = 0; i < max_size; i++)
        {
            auto &c = bn[i];
            c->distance = -1;
            c->index = i;
            c->inHeap = false;

            c->npl = 0;
            c->leftchild = c->rightchild = c->parent = nullptr;
        }
        root = nullptr;
    }
};

#endif