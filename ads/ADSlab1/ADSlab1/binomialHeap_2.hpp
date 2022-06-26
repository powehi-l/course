#ifndef BINOMIAL_HEAP2_HPP
#define BINOMIAL_HEAP2_HPP

#include "commons.hpp"
#include <cmath>
#include <stdexcept>

struct BinomialNode : public GeneralNode
{
	BinomialNode *child;  // pointer to first child
	BinomialNode *right;  // pointer to the sibling
	BinomialNode *parent; // pointer to its parent
	int degree;			  // numbers of children

	BinomialNode()
	{
		parent = child = right = nullptr;
		degree = 0;
	}
};

class BinomialHeap : public GeneralHeap
{
private:
	BinomialNode **roots; // record the root of this heap
	BinomialNode *actualNodes;
	int max_degree;
	int node_count;

	// link two nodes, make the smaller root to be parent and another to next child
	static BinomialNode *link(BinomialNode *a, BinomialNode *b)
	{
		if (a->degree != b->degree)
			return nullptr;
		if (a->distance > b->distance)
			SWAP(a, b);
		a->degree++;		 // plus one child
		b->right = a->child; // add b to be the first child of a
		a->child = b;
		b->parent = a;
		return a;
	}
	// insert a root into the array
	void insertRoot(BinomialNode *node)
	{
		while (roots[node->degree]) // while this degree already have a tree, then link them
		{
			int deg = node->degree;
			node = link(node, roots[node->degree]);
			roots[deg] = nullptr; // update the state of this degree
		}
		roots[node->degree] = node; // update root
	}

public:
	BinomialHeap()
	{
		HeapName = "BinomialHeap";
	}
	void initialize(Point *pl, int np)
	{
		max_degree = ceil(log2(np)) + 2;
		max_size = np;
		roots = new BinomialNode *[max_degree]; // allocate space for pointers pointing to the nodes
		nodes = new GeneralNode *[np];
		actualNodes = new BinomialNode[np]; // allocate space for those nodes
		for (int i = 0; i < np; i++)
		{
			nodes[i] = actualNodes + i; // make every pointer pointing to corresponding nodes
			nodes[i]->index = i;
		}
		for (int i = 0; i < max_degree; i++)
			roots[i] = nullptr; // make all the tree to be null
		node_count = 0;
		return;
	}
	// delete the root of the heap
	GeneralNode deleteMin()
	{
		if (!node_count)
			throw std::runtime_error("DeleteMin error : empty heap"); // if there is no node, then we can't delete
		node_count--;
		int min_idx = 0;
		ull min = -1;
		// create a new heap
		for (int i = 0; i < max_degree; i++)
		{
			if (roots[i] && roots[i]->distance < min)
			{
				min_idx = i;
				min = roots[i]->distance;
			}
		}
		BinomialNode *pMin = roots[min_idx];
		pMin->inHeap = false;
		roots[min_idx] = nullptr;
		GeneralNode res = *pMin;
		if (pMin->degree)
		{
			BinomialNode *n = pMin->child;
			// insert if both have tree in that degree
			while (n)
			{
				BinomialNode *nxt = n->right;
				n->right = n->parent = nullptr;
				insertRoot(n);
				n = nxt;
			}
		}
		return res;
	}
	void insert(int index, ull dist)
	{
		if (nodes[index]->inHeap) // if this node is already in the heap, then no need to insert
			return;
		node_count++; // update the number of nodes
		// update state of node to be inserted
		nodes[index]->inHeap = true;
		nodes[index]->distance = dist;
		insertRoot(static_cast<BinomialNode *>(nodes[index])); // insert this node
	}
	// decrease the distanceof a key with index idx to newVal
	void decreaseKey(int idx, ull newVal)
	{
		if (!nodes[idx]->inHeap)
			return;
		if (nodes[idx]->distance < newVal)
			return;
		BinomialNode *n = static_cast<BinomialNode *>(nodes[idx]), *p = n->parent;
		n->distance = newVal;
		// percolate up iteratively
		while (p && n->distance < p->distance)
		{
			// swap this two node including index, distance
			SWAP(nodes[n->index], nodes[p->index]);
			SWAP(nodes[n->index]->index, nodes[p->index]->index);
			SWAP(nodes[n->index]->distance, nodes[p->index]->distance);
			n = p;
			p = n->parent;
		}
	}
	// determine whether this heap is empty
	bool isEmpty()
	{
		return !node_count;
	}
	// free all the memory
	void free()
	{
		delete[] actualNodes;
		delete[] nodes;
		delete[] roots;
		nodes = NULL;
	}
	void reset()
	{
		BinomialNode **bn = reinterpret_cast<BinomialNode **>(nodes);
		for (int i = 0; i < max_size; i++)
		{
			auto &c = bn[i];
			c->distance = -1;
			c->index = i;
			c->inHeap = false;
			c->child = c->right = c->parent = nullptr;
			c->degree = 0;
		}
		node_count = 0;
		for (int i = 0; i < max_degree; i++)
			roots[i] = nullptr;
	}
};

#endif