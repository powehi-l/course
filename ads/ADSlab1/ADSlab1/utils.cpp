#include "commons.hpp"
#include <iostream>
using namespace std;
inline bool isEmpty(char ch) {
	return ch == '\t' || ch == ' ';
}
inline bool isNewline(char ch) {
	return ch == '\n' || ch == '\r';
}
inline bool isNumeric(char ch) {
	return ch >= '0' && ch <= '9';
}
inline int rd(char* &f) {
	char ch = *(f++);
	int x = 0, w = 1;
	while (ch < '0' || ch>'9')
	{
		if (ch == '-') w = -1;
		ch = *(f++);
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = *(f++);
	}
	return x * w;

}


ull* edgePool;
unsigned int* adjPool;
void clearPoints(){
	if(edgePool)delete[] edgePool;
	if(adjPool)delete[] adjPool;
	edgePool = nullptr;
	adjPool = nullptr;
}

void loadFile(string filename, Point*& pointList, long long int& nPoints, long long int& nEdges) {

	FILE* file = fopen(filename.c_str(), "r");
	fseek(file, 0, SEEK_END);
	ull szFile = ftell(file);
	rewind(file);
	clearerr(file);
	char* fbuf = new char[szFile];
	fread(fbuf, 1, szFile, file);
	char* fbuf_current = fbuf;
	char* fbuf_end = fbuf + szFile;
	int tot_edges = 0;
	char ch_now;
	cout << "start file parsing..." << endl;
	while (fbuf_current < fbuf_end) {
		char op = *fbuf_current;
		if (op == 'a') {
			int a, b, l;
			while (!isEmpty(*fbuf_current))fbuf_current++;
			if (fbuf_current >= fbuf_end) break;
			a = rd(fbuf_current);
			b = rd(fbuf_current);
			l = rd(fbuf_current);
			if (fbuf_current >= fbuf_end) break;
			pointList[a - 1].numAdjs++;
			pointList[b - 1].numAdjs++;
			tot_edges += 2;
		}
		else if (op == 'p') {
			while (!isNumeric(*fbuf_current))fbuf_current++;
			if (fbuf_current >= fbuf_end) break;
			nPoints = rd(fbuf_current);
			nEdges = rd(fbuf_current);
			if (fbuf_current >= fbuf_end) break;
			pointList = new Point[nPoints];
		}
		else while(!isNewline(*fbuf_current))fbuf_current++;
		if (fbuf_current >= fbuf_end) break;
		while (isNewline(*fbuf_current))fbuf_current++;
		if (fbuf_current >= fbuf_end) break;
	}
	edgePool = new ull[tot_edges];
	adjPool = new unsigned int[tot_edges];
	ull* edgeCursor = edgePool;
	unsigned int* adjCursor = adjPool;
	for (int i = 0; i < nPoints; i++) {
		pointList[i].edges = edgeCursor;
		pointList[i].adjPoints = adjCursor;
		edgeCursor += pointList[i].numAdjs;
		adjCursor += pointList[i].numAdjs;
		pointList[i].numAdjs = 0;
	}
	fbuf_current = fbuf;
	//second run
	while (fbuf_current < fbuf_end) {
		char op = *fbuf_current;
		if (op == 'a') {
			int a, b, l;
			while (!isEmpty(*fbuf_current))fbuf_current++;
			a = rd(fbuf_current);
			b = rd(fbuf_current);
			l = rd(fbuf_current);
			if (fbuf_current >= fbuf_end) break;
			int na = pointList[a - 1].numAdjs;
			int nb = pointList[b - 1].numAdjs;
			pointList[a - 1].adjPoints[na] = b - 1;
			pointList[b - 1].adjPoints[nb] = a - 1;
			pointList[a - 1].edges[na] = l;
			pointList[b - 1].edges[nb] = l;

			pointList[a - 1].numAdjs++;
			pointList[b - 1].numAdjs++;
		}
		else while (!isNewline(*fbuf_current))fbuf_current++;
		if (fbuf_current >= fbuf_end) break;
		while (isNewline(*fbuf_current))fbuf_current++;
		if (fbuf_current >= fbuf_end) break;
	}
	delete[] fbuf;
}

