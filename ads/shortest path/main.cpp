#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <time.h>

#include "commons.hpp"
#include "fibonacciHeap.hpp"
#include "binaryHeap.hpp"
#include "binomialHeap.hpp"
#include "leftistHeap.hpp"
#include "skewHeap.hpp"
#include "paringHeap.hpp"
#include "234Heap.hpp"

using namespace std;

long long int nPoints;
long long int nEdges;

Point *pointList;
GeneralHeap *HeapList[] = {
    new BinaryHeap, new LeftistHeap, new SkewHeap, new BinomialHeap, new FibonacciHeap, new ParingHeap, new TTFHeap};

void loadFile(string file)
{
    char mark;
    unsigned int source, destination;
    unsigned distance;

    while (cin >> mark)
    {
    }
}

clock_t dijk(Point *pl, int np, int o, GeneralHeap *heap)
{
    for (int i = 0; i < np; i++)
    {
        pl[i].distance = -1;
        pl[i].visited = 0;
    }
    pl[o].distance = 0;
    heap->initialize(pl, np);
    heap->insert(o, 0);
    clock_t clk = clock();
    while (!heap->isEmpty())
    {
        GeneralNode node = heap->deleteMin();
        pointList[node.index].visited = 1;
        pointList[node.index].distance = node.distance;
        for (int i = 0; i < pointList[node.index].numAdjs; i++)
        {
            ll d2 = pointList[node.index].edges[i] + node.distance;
            GeneralNode *adjNode = heap->nodes[i];
            if (d2 < adjNode->distance)
            {
                adjNode->distance = d2;
                heap->insert(adjNode->index, adjNode->distance);
            }
        }
    }
    clk = clock() - clk;
    heap->free();
    return clk;
}

int main()
{
    string filename;
    cin >> filename;
    loadFile(filename);
    for (int i = 0; i < sizeof(HeapList) / sizeof(GeneralHeap *); i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            clock_t time = dijk(pointList, nPoints, j, HeapList[i]);
            cout << HeapList[i]->HeapName << " : " << time << endl;
        }
    }
    return 0;
}