#ifndef COMMONS_HPP
#define COMMONS_HPP
#include <string>
typedef long long int ll;

struct GeneralNode{
    unsigned int index;
    ll distance;
};

struct Point{
    ll *edges;
    bool visited;
    ll distance;
    unsigned int numAdjs;
    unsigned int * adjPoints;
};

class GeneralHeap{

public:
    /**
     * @brief the list of pointers to all nodes in the heap. Note that this is list is allocated when the heap is initialized.
     nodes[idx] represents the pointer to the node of the point with index idx.
     * 
     */
    GeneralNode** nodes;
    std::string HeapName;

    /**
     * @brief Initializes a heap by a given pointlist.
     First , allocate memory for this->nodes.
     Then  , initialize the heap structure.
     * 
     * @param pl The list of points.
     * @param np The number of points in the list.
     */
    virtual void initialize(Point *pl,int np) = 0;

    /**
     * @brief Return and delete the node with minimun distance from prioirty queue.
     * 
     * @return GeneralNode the node with minimum distance
     */
    virtual GeneralNode deleteMin() = 0;

    /**
     * @brief Insert a node with point index = idx and shortest distance 
     Actually we don't need to allocate any new memory in this function.Just link the corresponding node( this->nodes[idx] ) to the heap is ok.
     * 
     * @param idx index of point
     * @param dist the distance of this points
     */
    virtual void insert(int idx,ll dist) = 0;

    /**
     * @brief Decrease the value of a node.
     * 
     * @param idx index of point
     * @param newDist new distance
     */
    virtual void decreaseKey(int idx,ll newVal) = 0;

    virtual bool isEmpty() = 0;
    virtual void free() = 0;
};

#endif