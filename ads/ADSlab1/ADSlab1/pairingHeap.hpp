#ifndef PARING_HEAP_HPP
#define PARING_HEAP_HPP
#include <cmath>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>

#include "commons.hpp"

struct PairingNode : public GeneralNode {
	PairingNode* parent;
	PairingNode* left;
	PairingNode* right;

	int rank;

	PairingNode() {
		parent = left = right = nullptr;
		rank = -1;
	}
};

class PairingHeap : public GeneralHeap {

	PairingNode** bucket;
	PairingNode* minRoot;
	PairingNode* actualNodes;
	int maxRank;

	static PairingNode* linkHalfTree(PairingNode* a, PairingNode* b) {
		if (b->distance < a->distance)SWAP(a, b);
		a->right = nullptr;
		b->parent = a;
		a->parent = nullptr;
		b->right = a->left;
		if (b->right)b->right->parent = b;
		a->left = b;
		a->rank = b->rank + 1;
		return a;
	}
	void multiPass(PairingNode* p) {
		while (bucket[p->rank]) {
			int oldRank = p->rank;
			p = linkHalfTree(p, bucket[p->rank]);
			bucket[oldRank] = nullptr;
		}
		bucket[p->rank] = p;
	}
	void insertRoot(PairingNode* r) {
		if (r == nullptr)return;
		r->parent = nullptr;
		if (r->left)r->rank = r->left->rank + 1;
		else r->rank = 0;
		if (minRoot == nullptr) {
			minRoot = r;
			minRoot->right = minRoot;
		}
		else {
			r->right = minRoot->right;
			minRoot->right = r;
			if (minRoot->distance > r->distance)minRoot = r;
		}
	}
public:
	PairingHeap(){
		HeapName = "PairingHeap";
	}
	void initialize(Point* pl, int np) {
		nodes = new GeneralNode * [np];
		max_size = np;
		actualNodes = new PairingNode[np];
		for (int i = 0; i < np; i++) {
			nodes[i] = actualNodes + i;
			nodes[i]->index = i;
		}
        maxRank = ceil(log2(np)) + 2;
        bucket = new PairingNode * [maxRank];
		minRoot = nullptr;
		for (int i = 0; i < maxRank; i++)bucket[i] = nullptr;

	}
	GeneralNode deleteMin() {
		GeneralNode n;
		if (!minRoot) throw std::runtime_error("deleteMin error : empty heap");
		n = *minRoot;
		minRoot->inHeap = false;
		memset(bucket, 0, sizeof(PairingNode*) * (maxRank));
        PairingNode *head1 = minRoot->left;
        PairingNode *temp1 = head1;
		for (PairingNode* c = minRoot->left; c;) {
			PairingNode* nxt = c->right;
			c->right = c->parent = nullptr;
			multiPass(c);
			c = nxt;
		}
		for (PairingNode* c = minRoot->right; c != minRoot;) {
			PairingNode* nxt = c->right;
			c->right = nullptr;
			multiPass(c);
			c = nxt;
		}
		minRoot = nullptr;
		for (int i = 0; i < maxRank; i++)insertRoot(bucket[i]);
		return n;
	}
	void insert(int index, ull dist) {
		if (nodes[index]->inHeap)return;
		nodes[index]->distance = dist;
		nodes[index]->inHeap = true;
		insertRoot(static_cast<PairingNode*>(nodes[index]));
	}
	void decreaseKey(int idx, ull newVal) {
		PairingNode* n = static_cast<PairingNode*>(nodes[idx]);
		if (!n->inHeap)return;
		n->distance = newVal;
		if (n->parent == nullptr) {
			if (newVal < minRoot->distance)minRoot = n;
		}
		else {
			PairingNode* p = n->parent;
			PairingNode* l = n->left;
			if (n == p->right) {
				p->right = n->right;
			}
			else {
				p->left = n->right;
				PairingNode* pp = p;
				while (pp) {
					int newRank = 0;
					if (pp->left)newRank = pp->left->rank + 1;
					else newRank = 0;
					if(newRank == pp->rank)break;
					else pp->rank = newRank;
					pp = pp->parent;
				}
			}
			if (n->right)n->right->parent = p;
			n->right = nullptr;
			insertRoot(n);
		}

	}
	bool isEmpty() {
		return minRoot == nullptr;
	}
	void free() {
		delete[] bucket;
		delete[] actualNodes;
		delete[] nodes;
		nodes = nullptr;
	}
	void reset() {
		minRoot = nullptr;
		for (int i = 0; i < maxRank; i++)bucket[i] = nullptr;
		PairingNode** pn = reinterpret_cast<PairingNode**>(nodes);
		for (int i = 0; i < max_size; i++) {
			auto& c = pn[i];
			c->distance = -1;
			c->index = i;
			c->inHeap = false;
			c->left = c->parent = c->right = nullptr;
			c->rank = -1;
		}
	}
};

#endif
