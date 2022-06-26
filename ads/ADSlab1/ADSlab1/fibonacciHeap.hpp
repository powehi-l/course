#ifndef FIBONACCI_HEAP_HPP
#define FIBONACCI_HEAP_HPP

#include "commons.hpp"
#include <cmath>
#include <assert.h>
#include <map>
struct FibonacciNode : public GeneralNode
{
	unsigned int degree;			// the degree of this node
	bool mark;						// lose its child or not
	struct FibonacciNode *Leftsib;	// the left subling of this node
	struct FibonacciNode *Rightsib; // the right subling of this node
	struct FibonacciNode *Parent;	// the parent of this node
	struct FibonacciNode *Child;	// a random child of the node

	FibonacciNode()
	{
		degree = 0;
		mark = false;
		Leftsib = Rightsib = Parent = Child = nullptr;
	}
};

class FibonacciHeap : public GeneralHeap
{
	struct FibonacciNode **degree_count;
	FibonacciNode *actualNodes;
	struct FibonacciNode *Min; // point to the minest distance in this heap
	ull node_count;
	ull max_degree;

	// link two trees in fibonacci heap
	static FibonacciNode *link(FibonacciNode *p1, FibonacciNode *p2)
	{
		if (p1 == nullptr && p2 == nullptr)
			return nullptr;
		if (p1 == nullptr)
			return p2;
		if (p2 == nullptr)
			return p1;

		if (p1->distance < p2->distance)
			return link1(p1, p2); // make the smaller root to be new root
		else
			return link1(p2, p1);
	}

	static FibonacciNode *link1(FibonacciNode *p1, FibonacciNode *p2)
	{
		// I think we should always keep p1->child the leftmost children .
		//  Since you iterated from left to right in DeleteMin().
		p2->Rightsib = p1->Child;
		p2->Leftsib = nullptr;
		if (p1->Child)
			p1->Child->Leftsib = p2;
		p1->Child = p2;
		p2->Parent = p1;
		p1->degree++;
		p1->Rightsib = p1->Leftsib = nullptr;
		return p1;
	}

	void insertRoot(FibonacciNode *node)
	{
		if (!node)
			return;
		node->mark = false;
		node->Parent = nullptr;
		if (Min == nullptr)
		{
			Min = node;
			node->Leftsib = node->Rightsib = node;
		}
		else
		{
			node->Rightsib = Min->Rightsib;
			node->Leftsib = Min;
			Min->Rightsib->Leftsib = node;
			Min->Rightsib = node;
			if (Min->distance > node->distance)
				Min = node;
		}
	}
	void multiPass(FibonacciNode *pr)
	{
		while (degree_count[pr->degree])
		{
			int oldDegree = pr->degree;
			pr = link(degree_count[pr->degree], pr);
			degree_count[oldDegree] = nullptr;
		}
		degree_count[pr->degree] = pr;
	}

public:
	FibonacciHeap()
	{
		HeapName = "FibonacciHeap";
	}
	// initialize the heap
	void initialize(Point *pl, int np)
	{
		Min = nullptr; // no min nodes after initialize
		max_size = np;
		nodes = new GeneralNode *[np]; // allocate space for pointers pointing to the nodes
		static const float phi = (sqrt(5) + 1) / 2;
		actualNodes = new FibonacciNode[np]; // allocate space for those nodes
		max_degree = ceil(log(np) / log(phi)) + 3;
		degree_count = new FibonacciNode *[max_degree];
		for (int i = 0; i < np; i++)
		{
			nodes[i] = actualNodes + i; // make every pointer pointing to corresponding nodes
			nodes[i]->index = i;		// make the index of nodes and pointer the same
		}
		for (int i = 0; i < max_degree; i++)
			degree_count[i] = nullptr;
		node_count = 0; // the number of nodes
		return;
	}

	GeneralNode deleteMin()
	{
		node_count--;
		struct FibonacciNode *p;
		struct FibonacciNode *pr;
		GeneralNode res = *Min;
		Min->inHeap = false;

		memset(degree_count, 0, (max_degree) * sizeof(FibonacciNode *));
		if (Min->Child != nullptr)
		{
			p = Min->Child;
			Min->Child = nullptr;
			for (int i = 0; i < Min->degree; i++)
			{
				pr = p->Rightsib;
				p->Parent = nullptr;
				multiPass(p);
				p = pr;
			}
		}
		p = Min->Rightsib;
		while (p != Min)
		{
			pr = p;
			p = p->Rightsib;
			multiPass(pr);
		};
		Min = nullptr;
		for (int i = 0; i < max_degree; i++)
			insertRoot(degree_count[i]);
		return res;
	}
	// insert a node to the heap whose index is index and distance is dist
	void insert(int index, ull dist)
	{
		if (nodes[index]->inHeap)
		{ // if this node is already in heap then update its distance
			decreaseKey(index, dist);
			return;
		}
		// update the state of this node and the heap
		node_count++;
		nodes[index]->inHeap = true;
		nodes[index]->distance = dist;
		insertRoot(static_cast<FibonacciNode *>(nodes[index])); // isert this node into the heap
	}
	// decrease the distanceof a key with index idx to newVal
	void decreaseKey(int idx, ull newVal)
	{
		FibonacciNode **fn = reinterpret_cast<FibonacciNode **>(nodes);
		struct FibonacciNode *p = fn[idx];
		p->distance = newVal;
		if (p->Parent == nullptr)
		{
			if (newVal < Min->distance)
				Min = p;
			return;
		}
		else if (p->distance >= p->Parent->distance)
			return;
		struct FibonacciNode *n;
		do
		{
			n = p->Parent;
			p->Parent = nullptr;

			// remove p from its parent's childs and the links from p's siblings
			if (p->Rightsib)
				p->Rightsib->Leftsib = p->Leftsib;
			if (p->Leftsib)
				p->Leftsib->Rightsib = p->Rightsib;
			if (n && n->Child == p)
				n->Child = p->Rightsib ? p->Rightsib : p->Leftsib;
			if (n)
				n->degree--;
			insertRoot(p);
			p = n;
		} while (p && p->mark);
		if (p && p->Parent)
			p->mark = true;
		return;
	}

	bool isEmpty()
	{
		return Min == nullptr;
	}

	void free()
	{
		delete[] actualNodes;
		delete[] degree_count;
		delete[] nodes;
	}
	void reset()
	{
		FibonacciNode **bn = reinterpret_cast<FibonacciNode **>(nodes);
		for (int i = 0; i < max_size; i++)
		{
			auto &c = bn[i];
			c->distance = -1;
			c->index = i;
			c->inHeap = false;
			c->degree = 0;
			c->mark = false;
			c->Leftsib = c->Rightsib = c->Parent = c->Child = nullptr;
		}
		node_count = 0;
		for (int i = 0; i < max_degree; i++)
			degree_count[i] = nullptr;
	}
};

#endif
