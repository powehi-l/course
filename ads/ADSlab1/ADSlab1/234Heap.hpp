#ifndef HEAP234_HPP
#define HEAP234_HPP
#include "commons.hpp"
#include <stdexcept>

struct TTFNode : public GeneralNode
{
	TTFNode *parent;
	TTFNode *childs[4];
	unsigned char nChilds;
	bool full;

	TTFNode()
	{
		parent = nullptr;
		for (int i = 0; i < 4; i++)
			childs[i] = nullptr;
		nChilds = 0;
		full = false;
	}
};

class TTFHeap : public GeneralHeap
{
	// int height;   since we don't need to do merge operations
	TTFNode *root;
	TTFNode *actualNodes;

	static void free_internal(TTFNode *n)
	{
		if (n && n->nChilds)
		{
			for (int i = 0; i < n->nChilds; i++)
				free_internal(n->childs[i]);
			delete n;
		}
	}

public:
	TTFHeap()
	{
		HeapName = "TTFHeap";
	}
	void initialize(Point *pl, int np)
	{
		root = nullptr;
		nodes = new GeneralNode *[np];
		max_size = np;
		actualNodes = new TTFNode[np];
		for (int i = 0; i < np; i++)
		{
			nodes[i] = actualNodes + i;
			nodes[i]->index = i;
		}
	}
	GeneralNode deleteMin()
	{
		if (!root)
			throw std::runtime_error("DeleteMin error : empty heap");
		TTFNode *c = root;
		while (c->nChilds)
		{
			auto clds = c->childs;
			int min = clds[0]->distance, minIdx = 0;
			for (int i = 1; i < c->nChilds; i++)
			{
				if (min > clds[i]->distance)
				{
					min = clds[i]->distance;
					minIdx = i;
				}
			}
			c = clds[minIdx];
		}
		GeneralNode res = *c;
		TTFNode *p = c->parent;
		while (p)
		{
			int ic = 0;
			for (int i = 0; i < p->nChilds; i++)
				if (p->childs[i] == c)
				{
					ic = i;
					break;
				}
			if (!c->nChilds)
			{
				if (c->index == -1)
					delete (c + 0);
				p->childs[ic] = p->childs[p->nChilds - 1];
				p->childs[p->nChilds - 1] = nullptr;
				p->nChilds -= 1;
			}
			p->distance = -1;
			if (p->full)
				p->full = false;
			for (int i = 0; i < p->nChilds; i++)
				if (p->distance > p->childs[i]->distance)
					p->distance = p->childs[i]->distance;
			c = p;
			p = c->parent;
		}
		if (c == root && c->nChilds == 0)
		{
			delete c;
			root = nullptr;
		}
		return res;
	}
	void insert(int index, ull dist)
	{
		if (nodes[index]->inHeap)
			return;
		nodes[index]->inHeap = true;
		nodes[index]->distance = dist;
		if (!root)
		{
			root = new TTFNode;
			root->nChilds = 1;
			root->distance = dist;
			root->childs[0] = static_cast<TTFNode *>(nodes[index]);
			root->childs[0]->parent = root;
		}
		else
		{
			TTFNode *c = root;
			while (c->childs[0]->nChilds)
			{
				TTFNode **childs = c->childs;
				int tg = 0;
				for (int i = 0; i < c->nChilds; i++)
				{
					if (!childs[i]->full)
					{
						tg = i;
						break;
					}
				}
				if (c->distance > dist)
					c->distance = dist;
				c = c->childs[tg];
			}
			if (c->distance > dist)
				c->distance = dist;
			TTFNode *nc = static_cast<TTFNode *>(nodes[index]);
			while (c && c->full)
			{
				c->full = false;
				TTFNode *l = c, *r = new TTFNode, *p = c->parent;
				nc->parent = r;
				l->nChilds = 3;
				r->nChilds = 2;
				r->childs[0] = l->childs[3];
				r->childs[1] = nc;
				r->parent = p;
				l->childs[3] = nullptr;
				r->childs[0]->parent = r->childs[1]->parent = r;
				l->distance = MIN(l->childs[0]->distance, MIN(l->childs[1]->distance, l->childs[2]->distance));
				r->distance = MIN(r->childs[0]->distance, r->childs[1]->distance);
				nc = r, c = p;
			}
			if (c)
			{
				c->childs[c->nChilds++] = nc;
				nc->parent = c;
				c->distance = MIN(c->distance, dist);
				if (c->nChilds == 4)
				{
					c->full = true;
					c = c->parent;
					while (c)
					{
						c->distance = MIN(c->distance, dist);
						bool f = true;
						for (int i = 0; i < 4; i++)
							if (!c->childs[i] || !c->childs[i]->full)
								f = false;
						c->full = f;
						c = c->parent;
					}
				}
			}
			else
			{
				TTFNode *newRoot = new TTFNode;
				newRoot->nChilds = 2;
				newRoot->childs[0] = root;
				newRoot->childs[1] = nc;
				newRoot->distance = MIN(root->distance, nc->distance);
				root->parent = nc->parent = newRoot;
				root = newRoot;
			}
		}
	}
	void decreaseKey(int idx, ull newVal)
	{
		TTFNode *c = static_cast<TTFNode *>(nodes[idx]);
		if (!c->inHeap)
			return;
		c->distance = newVal;
		while (c)
		{
			c->distance = MIN(newVal, c->distance);
			c = c->parent;
		}
	}
	bool isEmpty()
	{
		return root == nullptr;
	}
	void free()
	{
		free_internal(root);
		delete[] actualNodes;
		delete[] nodes;
	}
	void reset()
	{
		free_internal(root);
		root = nullptr;
		TTFNode **bn = reinterpret_cast<TTFNode **>(nodes);
		for (int i = 0; i < max_size; i++)
		{
			auto c = bn[i];
			c->distance = -1;
			c->index = i;
			c->inHeap = false;
			c->parent = nullptr;
			for (int i = 0; i < 4; i++)
				c->childs[i] = nullptr;
			c->nChilds = 0;
			c->full = false;
		}
	}
};

#endif