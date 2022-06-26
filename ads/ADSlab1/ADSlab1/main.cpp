
#include <iostream>
#include <cstdio>
#include <fstream>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <malloc.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <vector>

#include "commons.hpp"
#include "fibonacciHeap.hpp"
#include "binaryHeap.hpp"
#include "binomialHeap_2.hpp"
#include "leftistHeap.hpp"
#include "skewHeap.hpp"
#include "pairingHeap.hpp"
#include "234Heap.hpp"

#define NUM_ITER 1000

using namespace std;
chrono::high_resolution_clock::duration time_deleteMin;
chrono::high_resolution_clock::duration time_decreaseKey;


GeneralHeap* HeapList[] = {
   new BinaryHeap,
	new LeftistHeap ,
	new SkewHeap ,
	new BinomialHeap ,
	new FibonacciHeap ,
	 new PairingHeap ,
	new TTFHeap
};

#define HEAP_COUNT (sizeof(HeapList)/sizeof(GeneralHeap*))

struct Record {
	string fileName;			//input filename
	ull nv;						//number of veritces
	ull ne;						//number of edges
	ull numIters;
	string heapNames[HEAP_COUNT];		//current heap name			//time usage (in milliseconds)
	chrono::high_resolution_clock::duration avgTime[HEAP_COUNT];
};

Record runTest(string filename, int numIters) {
	Point* pointList;
	Record result;
	long long int nv = 0, ne = 0;
	cout << "*** Reading file " << filename << " ... " << endl;
	loadFile(filename, pointList, nv, ne);
    numIters = 60000000 / nv + 1;
	result.fileName = filename;
	result.numIters = numIters;
	cout << "Vertex : " << nv << " \tEdge : " << ne << endl;
	result.nv = nv;
	result.ne = ne;
	vector<ull> checksums;
	checksums.resize(numIters);
	for (int i = 0; i < HEAP_COUNT; i++) {
		result.heapNames[i] = HeapList[i]->HeapName;
		HeapList[i]->initialize(pointList, nv);
		cout << endl << "*** Running " << numIters << " iterations on " << HeapList[i]->HeapName << "..." << endl;
		result.avgTime[i] = chrono::high_resolution_clock::duration::zero();
		for (int it = 0; it < numIters; it++) {
			for (int i = 0; i < nv; i++) {
				pointList[i].distance = -1;
				pointList[i].visited = false;
			}
			auto clk = chrono::high_resolution_clock::now();
			dijk(pointList, nv, it % nv, HeapList[i]);
			result.avgTime[i] += chrono::high_resolution_clock::now() - clk;
			HeapList[i]->reset();
			cout << it << " ";
			ull r = 0;
			for (int k = 0; k < nv; k++)r += pointList[k].distance;
			if (i == 0)checksums[it] = r;
			else if (checksums[it] != r)cout << endl << HeapList[i]->HeapName << " failed." << endl;
		}
		cout << endl;
		HeapList[i]->free();
		result.avgTime[i] /= numIters;

		//        ofstream ofs(filename + "-" + HeapList[i]->HeapName + ".log");
		//        for(int i= 0;i < nv;i++)ofs  <<i <<  " "<<pointList[i].distance << endl;
		//        ofs.close();
	}
	cout << endl;
	clearPoints();
	delete[] pointList;
	return result;
}

int main() {
	string filenames[] = {
		"USA-road-d.NY.gr",
		"USA-road-d.COL.gr",
		"USA-road-d.FLA.gr",
		"USA-road-d.CAL.gr",
		"USA-road-d.E.gr",
		"USA-road-d.W.gr",
		"USA-road-d.CTR.gr",
		"USA-road-d.USA.gr"
	 };

    //  string filenames[] = {
    //      "1.in",
    //      "2.in",
    //      "3.in",
    //      "4.in",
    //      "5.in",
    //      "6.in",
    //      "7.in",
    //      "8.in",
    //      "9.in",
    //      "10.in",
    //      "11.in",
    //      "12.in",
    //       "13.in",
    //       "14.in",
    //       "15.in",
    //       "16.in",
    //       "17.in",
    //       "18.in",
    //       "19.in",
    //       "20.in"
    //  };

	// string filenames[] = {
	//     "USA-road-d.USA.gr",
	// 	//"2.in",
	// 	//"3.in",
	// 	//"4.in",
	// 	//"5.in"
	// };
	const int fileCount = sizeof(filenames) / sizeof(string);
	Record stats[fileCount];
    for (int i = 0; i < fileCount; i++)stats[i] = runTest(filenames[i], 100);
	cout << "\t\t\t\t";
	for (int i = 0; i < HEAP_COUNT; i++)cout << HeapList[i]->HeapName << "\t";
	ofstream ofs("stats.out");
	ofs << "Statistics Results" << endl;
	for (int i = 0; i < fileCount; i++) {
		ofs << endl << stats[i].fileName << "\t" << stats[i].nv << "\t" << stats[i].ne << "\t" << stats[i].numIters;
		for (int j = 0; j < HEAP_COUNT; j++) {
			ofs << "\t" << stats[i].avgTime[j].count();
			cout << HeapList[j]->HeapName << " Average time :" << std::chrono::duration_cast<std::chrono::microseconds>(stats[i].avgTime[j]).count() << endl;
		}
		ofs << endl;
	}

	ofs.close();
	return 0;
}
