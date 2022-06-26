#ifndef COMMONS_HPP
#define COMMONS_HPP
#include <string>
#include <cstring>
template <typename T>
void SWAP(T &a, T &b)
{
    T __swap_temp = (a);
    (a) = (b);
    (b) = (__swap_temp);
}

template <typename T>
T MIN(T const &a, T const &b)
{
    return a > b ? b : a;
}

typedef unsigned long long int ull;

struct GeneralNode
{
    unsigned int index; // index in the array
    bool inHeap;        // whether in heap
    ull distance;       // distance

    GeneralNode()
    {
        index = distance = -1;
        inHeap = false;
    }
    bool operator>(GeneralNode &b)
    {
        return distance > b.distance;
    }
    bool operator<(GeneralNode &b)
    {
        return distance < b.distance;
    }

    virtual ~GeneralNode()
    {
        // do noting just to make this virtual
    }
};

struct Point
{

    bool visited;
    ull distance;
    unsigned int numAdjs;    // numbers of adjacent point
    unsigned int *adjPoints; // pointers pointing to the adjacent point
    ull *edges;              // array of edges

    Point()
    {
        edges = nullptr;
        adjPoints = nullptr;
        visited = false;
        numAdjs = 0;
        distance = -1;
    }
};

class GeneralHeap
{
protected:
    int max_size;

public:
    /**
     * @brief the list of pointers to all nodes in the heap. Note that this is list is allocated when the heap is initialized.
     nodes[idx] represents the pointer to the node of the point with index idx.
     *
     */
    GeneralNode **nodes;
    std::string HeapName;

    /**
     * @brief Initializes a heap by a given pointlist.
     First , allocate memory for this->nodes.
     Then  , initialize the heap structure.
     *
     * @param pl The list of points.
     * @param np The number of points in the list.
     */
    virtual void initialize(Point *pl, int np) = 0;

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
    virtual void insert(int idx, ull dist) = 0;

    /**
     * @brief Decrease the value of a node.
     *
     * @param idx index of point
     * @param newDist new distance
     */
    virtual void decreaseKey(int idx, ull newVal) = 0;

    virtual bool isEmpty() = 0;
    virtual void free() = 0;
    virtual void reset() = 0;

    virtual ~GeneralHeap()
    {
        // do noting just to make this virtual
    }
};

void dijk(Point *pl, int np, int o, GeneralHeap *heap);
void loadFile(std::string filename, Point *&pointList, long long int &nPoints, long long int &nEdges);
void clearPoints();
#endif