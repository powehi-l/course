#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include "commons.hpp"

struct BinomialNode : public GeneralNode
{
    struct BinomialNode *Parent;
    struct BinomialNode *Child;
    struct BinomialNode *sibling;
    unsigned int degree;
};

class BinomialHeap : public GeneralHeap
{
private:
    struct BinomialNode *head;
    ull node_count;

public:
    void initialize(Point *pl, int np)
    {
        head = NULL;
        nodes = new GeneralNode *[np];
        BinomialNode * temp_node = new BinomialNode[np];
        for(int i =0;i<np;i++)nodes[i] = temp_node + i;
        node_count = 0;
        return;
    }
    GeneralNode deleteMin()
    {
        struct BinomialNode *p;
        p = head;
        struct BinomialNode *now;
        struct BinomialNode *now_left;
        struct BinomialNode *p_left;
        ull min;

        if (p == NULL)
        {
            return *p;
        }

        now = p;
        min = p->distance;
        p = p->sibling;
        while (p != NULL)
        {
            if (p->distance < min)
            {
                now_left = p_left;
                now = p;
                min = p->distance;
            }
            p_left = p;
            p = p->sibling;
        }
        if (now == head)
        {
            head = now->sibling;
        }
        else if (now->sibling == NULL)
        {
            now_left = NULL;
        }
        else
        {
            now_left->sibling = now->sibling;
        }

        struct BinomialNode *now_child;
        now_child = now->Child;

        if (now_child != NULL)
        {
            struct BinomialNode *h1;
            h1->Child = NULL;
            h1->degree = 0;
            h1->Parent = NULL;
            h1->sibling = NULL;
            now_child->Parent = NULL;
            h1 = now_child;
            p = now_child->sibling;
            now_child->sibling = NULL;
            while (p != NULL)
            {
                p_left = p;
                p = p->sibling;
                p_left->sibling = h1;
                h1 = p_left;
                p_left->Parent = NULL;
            }
            head = Union(head, h1);
        }
        return *now;
    }
    struct BinomialNode *Union(struct BinomialNode *h, struct BinomialNode *p)
    {
        head = rank(h, p);
        if (head == NULL)
            return NULL;

        struct BinomialNode *left;
        struct BinomialNode *next;
        struct BinomialNode *now;
        now = head;
        next = head->sibling;
        left = NULL;
        while (next != NULL)
        {
            if (now->degree != next->degree || (next->sibling != NULL && now->degree == next->sibling->degree))
            {
                left = now;
                now = next;
            }
            else if (now->distance <= next->distance)
            {
                now->sibling = next->sibling;
                link(next, now);
            }
            else
            {
                if (left == NULL)
                    head = next;
                else
                    left->sibling = next;
                link(now, next);
            }
        }
        return head;
    }
    void insert(int index, ull dist)
    {
        struct BinomialNode *p = static_cast<BinomialNode*>(nodes[index]);
        p->Child = NULL;
        p->Parent = NULL;
        p->degree = 0;
        p->inHeap = true;
        p->distance = dist;
        p->sibling = NULL;
        head = Union(head, p);
    }
    void decreaseKey(int idx, ull newVal)
    {
        if (nodes[idx] == NULL)
        {
            insert(idx, newVal);
            return;
        }
        if (newVal >= nodes[idx]->distance)
            return;
        nodes[idx]->distance = newVal;
        struct BinomialNode *y;
        struct BinomialNode *p;
        y = static_cast<BinomialNode*>(nodes[idx]);
        p = y->Parent;
        while (p != NULL && y->distance < p->distance)
        {
            y->distance = p->distance;
            p->distance = newVal;
            y = p;
            p = y->Parent;
        }
        // you cannot change the distances of nodes whose index is not idx
        return;
    }
    bool isEmpty()
    {
        if (head == NULL)
            return true;
        else
            return false;
    }
    void free()
    {
        delete[] nodes;
        nodes = NULL;
    }
    // link p1 into p2
    void link(struct BinomialNode *p1, struct BinomialNode *p2)
    {
        p1->Parent = p2;
        p1->sibling = p2->Child;
        p2->Child = p1;
        p2->degree++;
    }

    struct BinomialNode *rank(struct BinomialNode *h1, struct BinomialNode *h2)
    {
        struct BinomialNode *firstNode = NULL;
        struct BinomialNode *p = NULL;
        if (h1 == NULL || h2 == NULL)
        {
            if (h1 == NULL)
                firstNode = h2;
            else
                firstNode = h1;
            return firstNode;
        }
        if (h1->degree < h2->degree)
        {
            firstNode = h1;
            p = firstNode;
            h1 = h1->sibling;
        }
        else
        {
            firstNode = h2;
            p = firstNode;
            h2 = h2->sibling;
        }

        while (h1 != NULL && h2 != NULL)
        {
            if (h1->degree < h2->degree)
            {
                p->sibling = h1;
                p = h1;
                h1 = h1->sibling;
            }
            else
            {
                p->sibling = h2;
                p = h2;
                h2 = h2->sibling;
            }
        }
        if (h1 != NULL)
            p->sibling = h1;
        else
            p->sibling = h2;
        return firstNode;
    }
    void reset(){
		
	}
};

#endif