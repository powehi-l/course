#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include "commons.hpp"

struct BinaryNode : public GeneralNode
{
    int position; // record the position this node in the heap(from 0 to heapsize)
    BinaryNode()
    {
        position = -1;
    }
};

class BinaryHeap : public GeneralHeap
{

private:
    BinaryNode **heap; //
    BinaryNode *acutalNodes;
    int heapSize; // record nodes int the heap

public:
    BinaryHeap()
    {
        HeapName = "BinaryHeap";
    }
    void initialize(Point *pl, int np)
    {
        heapSize = 0;
        max_size = np;
        HeapName = "BinaryHeap";
        nodes = new GeneralNode *[np];    // allocate space for pointers pointing to the nodes
        acutalNodes = new BinaryNode[np]; // allocate space for those nodes
        for (int i = 0; i < np; i++)
        {
            nodes[i] = acutalNodes + i; // make every pointer pointing to corresponding nodes
            nodes[i]->index = i;        // make the index of nodes and pointer the same
        }
        BinaryNode **bn = reinterpret_cast<BinaryNode **>(nodes);
        heap = new BinaryNode *[np]; // make "heap" a binary heap consists of pointers pointing to actual nodes
    }
    GeneralNode deleteMin()
    {
        GeneralNode gn = *(heap[0]);  // record the minimal node and return in the end
        heap[0] = heap[heapSize - 1]; // make the end of the heap to the root
        heap[0]->position = 0;
        int cur_pos = 0, newVal = heap[heapSize - 1]->distance;
        heapSize--;
        int leftChild = cur_pos * 2 + 1;
        int rightChild = cur_pos * 2 + 2;
        // iteratively percolate down
        while (cur_pos < heapSize && (leftChild < heapSize && heap[leftChild]->distance < newVal || rightChild < heapSize && heap[rightChild]->distance < newVal))
        { // percolate down
            int tg;
            if (leftChild < heapSize && rightChild < heapSize)
            { // determine the samller child tg
                if (heap[leftChild]->distance < heap[rightChild]->distance)
                    tg = leftChild;
                else
                    tg = rightChild;
            }
            else if (leftChild < heapSize)
                tg = leftChild;
            else
                tg = rightChild;
            SWAP(heap[cur_pos], heap[tg]);     // swap smaler child and current point
            heap[cur_pos]->position = cur_pos; // update the position of current ponit
            heap[tg]->position = tg;           // update the position of child
            cur_pos = tg;
            leftChild = cur_pos * 2 + 1;
            rightChild = cur_pos * 2 + 2;
        }
        return gn;
    }
    void insert(int index, ull dist)
    {
        heap[heapSize] = static_cast<BinaryNode *>(nodes[index]); // add a node in the end of the heap
        heap[heapSize]->position = heapSize;                      // update its position
        nodes[index]->inHeap = true;                              // update the state of this node
        nodes[index]->distance = dist;
        int cur_pos = heapSize;
        int parent_pos = (cur_pos + 1) / 2 - 1;
        // percolate up iteratively
        while (cur_pos != 0 && heap[cur_pos]->distance < heap[parent_pos]->distance)
        { // if current node is smaller than its parent
            SWAP(heap[cur_pos], heap[parent_pos]);
            heap[cur_pos]->position = cur_pos;
            heap[parent_pos]->position = parent_pos;
            cur_pos = parent_pos;               // update current point
            parent_pos = (cur_pos + 1) / 2 - 1; // update current point's parent
        }
        heapSize++; // after inserting, the size of heap plus one
    }
    void decreaseKey(int idx, ull newVal)
    {
        int cur_pos = static_cast<BinaryNode *>(nodes[idx])->position;
        int parent_pos = (cur_pos + 1) / 2 - 1;
        if (newVal < nodes[idx]->distance)
        { // percolate up iteratively
            while (cur_pos != 0 && newVal < heap[parent_pos]->distance)
            {
                SWAP(heap[cur_pos], heap[parent_pos]);
                heap[cur_pos]->position = cur_pos;
                heap[parent_pos]->position = parent_pos;
                cur_pos = parent_pos;               // update current point
                parent_pos = (cur_pos + 1) / 2 - 1; // update current point's parent
            }
        }
        nodes[idx]->distance = newVal; // update the distance of the point
    }
    bool isEmpty() // return true if the heap is empty
    {
        return heapSize == 0;
    }
    void free() // free all the space
    {
        delete[] acutalNodes;
        delete[] nodes;
        if (heap != nullptr)
            delete[] heap;
        heap = nullptr;
        nodes = nullptr;
    }
    void reset()
    {
        BinaryNode **bn = reinterpret_cast<BinaryNode **>(nodes);
        for (int i = 0; i < max_size; i++)
        {
            auto &c = bn[i];
            c->position = -1;
            c->distance = -1;
            c->index = i;
            c->inHeap = false;
            heap[i] = nullptr;
        }
        heapSize = 0;
    }
};

#endif