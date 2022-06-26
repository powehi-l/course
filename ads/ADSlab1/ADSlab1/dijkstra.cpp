#include "commons.hpp"

#ifdef DEBUG
#include <fstream>
using namespace std;
#endif
void dijk(Point* pl, int np, int o, GeneralHeap* heap) {
	pl[o].distance = 0;
	heap->insert(o, 0);
#ifdef DEBUG
    ofstream ofs("fib.log");
#endif
	while (!heap->isEmpty()) {
		GeneralNode node = heap->deleteMin();
#ifdef DEBUG
        ofs << "dequeue " << node.distance << endl;
#endif
		auto& p = pl[node.index];
		p.visited = true;
		p.distance = node.distance;
		for (int i = 0; i < pl[node.index].numAdjs; i++) {
			ull d2 = p.edges[i] + node.distance;
			GeneralNode* adjNode = heap->nodes[p.adjPoints[i]];
            auto aidx = adjNode->index;
			if (pl[aidx].visited)continue;
			if (d2 < adjNode->distance) {
#ifdef DEBUG
                //ofs << "decrease " << node.index << "->" << adjNode->index << " = " << d2 << endl;
#endif
				if (!adjNode->inHeap) heap->insert(aidx, d2);
				else heap->decreaseKey(aidx, d2);
			}
		}
	}
#ifdef DEBUG
    ofstream ofs2("fib.out");
	ofs2 << o << endl;
	for (int i = 0; i < np; i++)ofs2 << i << " " << pl[i].distance << endl;
	ofs2.close();
#endif
}
