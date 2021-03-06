# Shortest Path Algorithm with Heaps

## Chapter 1 : Introduction 

#### The problem: 

Using Dijkstra's algorithm to solve the shortest road problem. 

Instead of using array like we used in the project 3 in fundamental data structure, this time the implementation shall be based on a min-priority queue. And in the final program, we need to use at least 2 different queue, which must contains Fibonacci heap.

####  Input: 

Download the real data of American roads on the website provided, and then read them. 

#### Output:

Output the running time of each algorithm based on different heap. 

#### Limits: 

1. No downloaded data can be modified. 
2.  The algorithm of each different heap needs to be tested at least 1000 times. 

## Chapter 2 : Algorithm Specification 

### 2.1 Data Structure 

#### 2.1.1 Class 

> In C + +, we use "class" to describe "object". The so-called "object" refers to everything in the real world. Then class can be regarded as an abstraction of similar things. Find the common ground between these different things, such as bicycles and motorcycles. First of all, they all belong to "objects", and have certain similarities and some differences. For example, they all have mass, have two wheels, and belong to vehicles. "Both have mass" and "two wheels" belong to the attributes of this object, while "both can be used as vehicles" belongs to the behavior of this object, also known as methods.

##### usage method

C + + uses the keyword class to define classes. Its basic form is as follows:

```c++
class //Class name
{
    public:
    //The act or attribute of being public
 
    private:
    //The act or property of being private
};
```

Public and private are keywords restricted by attributes / methods. 

Private means that this part of the content is private and cannot be accessed or called externally, but can only be accessed internally by this class.

Public refers to the public properties and methods, which can be directly accessed or called by the outside world.

#### 2.1.2 Node 

##### `GeneralNode` 

```c++
struct GeneralNode{
    unsigned int index;
    bool inHeap;
    unsigned long long int distance
};
```

| parameter name | purpose                 |
| -------------- | ----------------------- |
| index          | the number of the point |
| inHeap         | whether it is in heap   |
| distance       | store the distance      |

##### `2-3-4Node`

```c++
struct TTFNode : public GeneralNode {
	TTFNode* parent;
	TTFNode* childs[4];
	unsigned char nChilds;
	bool full;
};
```

| parameter name | purpose                          |
| -------------- | -------------------------------- |
| parent         | point to the parent of this node |
| childs[4]      | point to the children of it      |
| nchilds        | the number of it children        |
| full           | whether it is full               |

##### `BinaryNode`

```c++
struct BinaryNode : public GeneralNode{
    int position;
};
```

| parameter name | purpose                                                      |
| -------------- | ------------------------------------------------------------ |
| position       | store the position of this point in the heap (array subscript) |

##### `LeftistNode`

```c++
struct LeftistNode : public GeneralNode
{
    unsigned int npl;
    struct LeftistNode *leftchild;  
    struct LeftistNode *rightchild; 
    struct LeftistNode *parent;     
};
```

| parameter name | purpose                |
| -------------- | ---------------------- |
| leftchild      | pointer to left child  |
| rightchild     | pointer to right child |
| parent         | pointer to its parent  |

##### `SkewNode`

```c++
struct SkewNode : public GeneralNode
{
    struct SkewNode *leftchild;
    struct SkewNode *rightchild;
    struct SkewNode *parent;
};
```

| parameter name | purpose                |
| -------------- | ---------------------- |
| leftchild      | pointer to left child  |
| rightchild     | pointer to right child |
| parent         | pointer to its parent  |

##### `FibonacciNode`

```c++
struct FibonacciNode : public GeneralNode
{
	unsigned int degree;           
	bool mark;                      
	struct FibonacciNode* Leftsib;  
	struct FibonacciNode* Rightsib; 
	struct FibonacciNode* Parent;   
	struct FibonacciNode* Child;    
};
```

| parameter name | purpose                                 |
| -------------- | --------------------------------------- |
| degree         | the degree of this node                 |
| mark           | lose its child or not                   |
| Leftsib        | point to the left subling of this node  |
| Rightsib       | point to the right subling of this node |
| Parent         | point to the parent of this node        |
| Child          | point to a random child of the node     |

##### `BinomialNode`

```c++
struct BinomialNode : public GeneralNode
{
    struct BinomialNode *Parent;
    struct BinomialNode *Child;
    struct BinomialNode *sibling;
    unsigned int degree;
};
```

| parameter name | purpose                                    |
| -------------- | ------------------------------------------ |
| Parent         | point to the parent of this node           |
| Child          | point to the child with the biggest degree |
| sibling        | point to its right sibling, can be null    |
| degree         | the degree of this node                    |

> All the node types will integrate the parameters of general node, and add newly defined parameters on this basis. When using, you can use forced type conversion.

##### `ParingNode`

```c++
struct PairingNode : public GeneralNode {
	PairingNode* parent;
	PairingNode* left;
	PairingNode* right;
};
```

| parameter name | purpose                               |
| -------------- | ------------------------------------- |
| parent         | point to the parent of this node      |
| left           | point to the left child of this node  |
| right          | point to the right child of this node |

#### 2.1.3 Point

```c++
struct Point{
    bool visited;
    unsigned long long int distance;
    unsigned int numAdjs;
    unsigned int * adjPoints;
    unsigned long long int *edges;
};
```

| parameter name | purpose                                                      |
| -------------- | ------------------------------------------------------------ |
| visited        | whehter this point is visited                                |
| distance       | the current distance of this point                           |
| numAdjs        | number of points adjacent to this point                      |
| adjPoints      | pointer to these adjacent points                             |
| edges          | distance from the edge connected to the corresponding adjacent point |

#### 2.1.4 Heap

##### (1)GeneralHeap

```c++
class GeneralHeap{
protected:
    int max_size;

public:
    GeneralNode** nodes;
    std::string HeapName;
    
    virtual void initialize(Point *pl,int np) = 0;
    virtual GeneralNode deleteMin() = 0;
    virtual void insert(int idx,ull dist) = 0;
    virtual void decreaseKey(int idx,ull newVal) = 0;
    virtual bool isEmpty() = 0;
    virtual void free() = 0;

    virtual ~GeneralHeap(){
        //do noting just to make this virtual
    }
};
```

`initialize`

Initializes a heap by a given pointlist.

First , allocate memory for this->nodes.

Then  , initialize the heap structure.

`deleteMin`

Delete the Min distance from the heap and return the deleted general node.

`insert`

Insert the node with idx as its index and dist as its distance into the heap.

`decreaseKey`

Decrease the distance of the node which is already in the heap.

`isEmpty`

Determine whether the heap is empty.

`free`

Free up all used space.

> Due to the nature and operation of different heaps, some other functions need to be defined, which will be explained in detail in the subsequent introduction to heaps.

##### (2)2-3-4 heap

`Definition`

![2-3-4 Tree](8-1 Shortest Path Algorithm with Heaps.assets/20210614223323277.png)

2-3-4 tree is a B + tree with order 4.

(1) The root is either a leaf or has between 2 and M children

(2) All nonleaf nodes (except the root) have between  and M children.

(3) All leaves are at the same depth

`insert`

Insert a new node through the index. If the number of nodes is greater than 4, it will be divided into two nodes.

`deleteMin`

Delete the leftmost real data.

`decreaseKey`

Rearrange the location of real data and update satellite data.

##### (3)Binary heap

`Definition`

![image-20220328205820952](8-1 Shortest Path Algorithm with Heaps.assets/image-20220328205820952.png)

Binary heap is a complete binary tree or an approximate complete binary tree.

A binary tree with *n* nodes and height *h* is complete iff its nodes correspond to the nodes numbered from 1 to *n* in the perfect binary tree of height *h*.

![image-20220328205910488](8-1 Shortest Path Algorithm with Heaps.assets/image-20220328205910488.png)

`insert`

1. Because the inserted tree must be a complete binary tree, the insertion position is unique. No matter what value is inserted, it is directly inserted where it should be inserted. 

2. If the value of the newly inserted node does not meet the minimum heap property, float up.

`deleteMin`

1. The minimum value must be the root node. Delete the root node.

2. Find the last inserted position in the heap, delete the point at this position, and put the value stored in the point into the root node.
3. If the value of the new root node is greater than that of its child, sink.

`decreaseKey`

???	Float up.

##### (4)Leftist heap

> In addition to the standard insert and delete operations, another common operation of heap structure in practical application is merging, that is, heap a and heap B are reorganized into one heap. Leftist heap can be merged quickly.

`Definition`

![image-20220328213141003](8-1 Shortest Path Algorithm with Heaps.assets/image-20220328213141003.png)

1. The null path length, Npl(X), of any node X is the length of the shortest path from X to a node without two children. Define Npl(NULL)=-1.
2. The leftist heap property is that for every node X in the heap, the null path length of the left child is at least as large as that of the right child.

`merge(recursive version)`

1. Merge the right subtree of H1 with H2.
2. Take the merged H2 as the right subtree of H1.
3. If necessary, swap the left and right subtrees.

`insert`

Merge the newly inserted point with the original heap.

`deleteMin`

1. Delete the root.
2. Merge the subtree of the last root.

`decreaseKey`

1. If the value of the root is reduced, you can return directly after reduction without adjustment.
2. If it is still greater than the value of the parent node after reduction, it can also be returned directly.
3. If any of the above conditions are not met, percolate up.

##### (5)Skew heap

`Definition`

A simple version of the leftist heaps.

`merge`

It is basically the same as leftist heap, except that the left and right subtrees have to be exchanged without a merge.

`insert`

Merge the newly inserted point with the original heap.

`deleteMin`

1. Delete the root.
2. Merge the subtree of the last root.

`decreaseKey`

The same as leftist heap.

##### (6)Fibonacci heap

`Definition`

![img](8-1 Shortest Path Algorithm with Heaps.assets/281939267086148.png)

1. The parameters to be stored are: parent node, any child node(random one), sibling on the left, sibling on the right, degree(the number of children it has), and whether to lose a child(mark).
2. Fibonacci heap has no head node, but has a root sequence and a pointer Min to the smallest node.

`insert`

1. Create a node and initialize all parameters in the node.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/281946062863108.png)

2. Insert the new node to the left of the minimum value. If the newly inserted value is smaller than the minimum value, the minimum value pointer is updated.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/281949411777591.png)

`deleteMin`

![img](8-1 Shortest Path Algorithm with Heaps.assets/022041462249792.png)

1. If there is only one node with the minimum value, min points to null.

2. Connect the minimum child node to the root linked list.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022048225364583.png)

3. Delete the minimum node. (in the function, because the value of this node is to be returned, there is no need to reclaim the memory space occupied by it)

4. Create a pointer array to record the degree of each node connected in the root sequence, and connect the nodes with the same degree to form a new node. Until the degree of nodes in any root sequence is different.

   e.g.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022050222556708.png)

   1. The degree of 7 is 1, which is stored in the array.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022050405059066.png)

   2. The degree of 24 is 2, which is stored in the array without repetition.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022051072869717.png)

   3. The degree of 23 is 0, which is stored in the array without repetition. 

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022051404901507.png)

   4. The degree of 17 is 0. When it is to be stored in the array, it is found that there are duplicates (23). Link them.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022052141156467.png)

   5. The degree of 17 after connection becomes 1, and 7 repeat, link 7 and 17.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022052450683144.png)

   6. 7 and 24 degrees are both 2. Repeat, then link them. And point the pointer with a degree of 3 to 7

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022053268338685-164848064095213.png)

   7. The degree of 18 is 1 and is stored in the array.

   

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022054267556612.png)

   8. The degree of 50 is 0 and is stored in the array.

   ![img](8-1 Shortest Path Algorithm with Heaps.assets/022056232408324.png)

   9. The degree of 41 is 1. Link it with 18 and store it in 2. The final Fibonacci pile became the one shown above.

`decreaseKey`

1. If the nature of the minimum heap is not violated, it is reduced directly.
2. If the nature of the minimum heap is violated, connect the reduced node to the left of the minimum value, and then set it unmarked.
3. If its parent node is unmarked, set it to marked. If it has been marked, the parent node is also connected to the left of the minimum value and set to unmarked. Repeat this operation until the parent node is already in the root sequence or the parent node is unmarked.

##### (7)Binomial heap

`Definition`

It is a set of structures composed of binomial trees.

![img](8-1 Shortest Path Algorithm with Heaps.assets/Center.png)

For a binomial heap BK

1. There are 2 ^ k nodes in total.
2. The height of the tree is K.
3. There are exactly C (k, i) nodes at the depth i. (i=0,1,....k)
4. The degree of the root is k, which is greater than that of any other node, and if the children of the root are numbered K - 1, K - 2, 0, child I is the root of subtree Bi.

`rank`

Connect the two binomial heaps in ascending order of the degree of the root node.

`merge`

1. Rank two binomial heaps.
2. Merge them in the same order and end up in ascending order.

`link`

Connect the bk-1 tree with node y as the root and the bk-1 tree with node Z as the root, make Z become the parent node of Y, and finally merge into a BK tree.

`insert`

That is to union the newly inserted node as a binomial heap H1 and the binomial heap h to be inserted.

`deleteMin`

1. Find the node with the minimum value in the binomial heap H (in the root list). Note: be sure to modify the sibling pointer of the previous sibling node of this node (that is, the node pointing to the minimum value node sibling)

2. The children of the minimum node are concatenated into a new binomial heap H1.

`decreaseKey`

Decrease the value of this node and adjust the position of this node in the binomial heap if necessary.

##### (8)Paring heap



## Chapter 3: Testing Results

## Chapter 4: Analysis and Comments

## Declaration

***We hereby declare that all the work done in this project titled "Shortest Path Algorithm with Heaps" is of our independent effort.***

### Appendix

`test sample download link`

```
http://www.dis.uniroma1.it/challenge9/download.shtml
```

`Commons.hpp`

```c++
#ifndef COMMONS_HPP
#define COMMONS_HPP
#include <string>

template <typename T> void SWAP(T &a,T &b) {\
    T __swap_temp = (a);\
    (a) = (b);\
    (b) = (__swap_temp);\
}

template <typename T> T MIN(T const& a, T const& b) {
    return a > b ? b : a;
}

typedef unsigned long long int ull;

struct GeneralNode{
    unsigned int index;
    bool inHeap;
    ull distance;

    GeneralNode(){
        index = distance = -1;
        inHeap = false;
    }

    virtual ~GeneralNode(){
        //do noting just to make this virtual
    }
};

struct Point{
    
    bool visited;
    ull distance;
    unsigned int numAdjs;
    unsigned int * adjPoints;
    ull *edges;

    Point(){
        edges = nullptr;
        adjPoints = nullptr;
        visited = false;
        numAdjs = 0;
        distance = -1;
    }
};

class GeneralHeap{
protected:
    int max_size;

public:
    /**
     * @brief the list of pointers to all nodes in the heap. Note that this is list is allocated when the heap is initialized.
     nodes[idx] represents the pointer to the node of the point with index idx.
     * 
     */
    GeneralNode** nodes;
    std::string HeapName;

    /**
     * @brief Initializes a heap by a given pointlist.
     First , allocate memory for this->nodes.
     Then  , initialize the heap structure.
     * 
     * @param pl The list of points.
     * @param np The number of points in the list.
     */
    virtual void initialize(Point *pl,int np) = 0;

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
    virtual void insert(int idx,ull dist) = 0;

    /**
     * @brief Decrease the value of a node.
     * 
     * @param idx index of point
     * @param newDist new distance
     */
    virtual void decreaseKey(int idx,ull newVal) = 0;

    virtual bool isEmpty() = 0;
    virtual void free() = 0;

    virtual ~GeneralHeap(){
        //do noting just to make this virtual
    }
};

#endif
```

`234Heap.hpp`

```c++
#ifndef HEAP234_HPP
#define HEAP234_HPP
#include "commons.hpp"
#include <stdexcept>

struct TTFNode : public GeneralNode {
	TTFNode* parent;
	TTFNode* childs[4];
	unsigned char nChilds;
	bool full;

	TTFNode() {
		parent = nullptr;
		for (int i = 0; i < 4; i++)childs[i] = nullptr;
		nChilds = 0;
		full = false;
	}
};

class TTFHeap : public GeneralHeap {
	// int height;   since we don't need to do merge operations
	TTFNode* root;

	static void free_internal(TTFNode* n) {
		if (n && n->nChilds) {
			for (int i = 0; i < n->nChilds; i++)free_internal(n->childs[i]);
			delete n;
		}
	}
public:

	void initialize(Point* pl, int np) {
		root = nullptr;
		nodes = new GeneralNode * [np];
		TTFNode* temp = new TTFNode[np];
		for (int i = 0; i < np; i++) {
			nodes[i] = temp + i;
			nodes[i]->index = i;
		}
	}
	GeneralNode deleteMin() {
		if (!root)throw std::runtime_error("DeleteMin error : empty heap");
		TTFNode* c = root;
		while (c->nChilds) {
			auto clds = c->childs;
			int min = clds[0]->distance, minIdx = 0;
			for (int i = 1; i < c->nChilds; i++) {
				if (min > clds[i]->distance) {
					min = clds[i]->distance;
					minIdx = i;
				}
			}
			c = clds[minIdx];
		}
		GeneralNode res = *c;
		TTFNode* p = c->parent;
		while (p) {
			int ic = 0;
			for (int i = 0; i < p->nChilds; i++)if (p->childs[i] == c) {
				ic = i; break;
				assert(i < p->nChilds);
			}
			if (!c->nChilds) {
				if (c->index == -1)delete (c + 0);
				p->childs[ic] = p->childs[p->nChilds -1];
				p->childs[p->nChilds - 1] = nullptr;
				p->nChilds -= 1;
			}
			p->distance = -1;
			if (p->full)p->full = false;
			for (int i = 0; i < p->nChilds; i++)if (p->distance > p->childs[i]->distance) p->distance = p->childs[i]->distance;
			c = p;
			p = c->parent;
		}
		if (c == root && c->nChilds == 0) {
			delete c;
			root = nullptr;
		}
		return res;
	}
	void insert(int index, ull dist) {
		if (nodes[index]->inHeap)return;
		nodes[index]->inHeap = true;
		nodes[index]->distance = dist;
		if (!root) {
			root = new TTFNode;
			root->nChilds = 1;
			root->distance = dist;
			root->childs[0] = static_cast<TTFNode*>(nodes[index]);
			root->childs[0]->parent = root;
		}
		else {
			TTFNode* c = root;
			while (c->childs[0]->nChilds) {
				TTFNode** childs = c->childs;
				int tg = 0;
				for (int i = 0; i < c->nChilds; i++) {
					if (!childs[i]->full) {
						tg = i;
						break;
					}
				}
				if (c->distance > dist)c->distance = dist;
				c = c->childs[tg];
			}
			if (c->distance > dist)c->distance = dist;
			TTFNode* nc = static_cast<TTFNode*>(nodes[index]);
			while (c && c->full) {
				c->full = false;
				TTFNode* l = c, * r = new TTFNode, * p = c->parent;
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
			if (c) {
				c->childs[c->nChilds++] = nc;
				nc->parent = c;
				c->distance = MIN(c->distance, dist);
				if (c->nChilds == 4) {
					c->full = true;
					c = c->parent;
					while (c) {
						c->distance = MIN(c->distance, dist);
						bool f = true;
						for (int i = 0; i < 4; i++)if (!c->childs[i] || !c->childs[i]->full)f = false;
						c->full = f;
						c = c->parent;
					}
				}
			}
			else {
				TTFNode* newRoot = new TTFNode;
				newRoot->nChilds = 2;
				newRoot->childs[0] = root;
				newRoot->childs[1] = nc;
				newRoot->distance = MIN(root->distance, nc->distance);
				root->parent = nc->parent = newRoot;
				root = newRoot;
			}

		}
	}
	void decreaseKey(int idx, ull newVal) {
		TTFNode* c = static_cast<TTFNode*>(nodes[idx]);
		if (!c->inHeap)return;
		c->distance = newVal;
		while (c) {
			c->distance = MIN(newVal, c->distance);
			c = c->parent;
		}
	}
	bool isEmpty() {
		return root == nullptr;
	}
	void free() {
		free_internal(root);
		for (int i = 0; i < max_size; i++)delete nodes[i];
		delete[] nodes;
	}
};


#endif
```

`binaryHeap.hpp`

```c++
#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include "commons.hpp"

struct BinaryNode : public GeneralNode{
    int position;
    BinaryNode(){
        position = -1;
    }
};

class BinaryHeap : public GeneralHeap{

private:
    BinaryNode ** heap;
    BinaryNode* acutalNodes;
    int heapSize;

public:

    void initialize(Point *pl,int np){
        heapSize = 0;
        max_size = np;
        HeapName = "BinaryHeap";
        nodes = new GeneralNode*[np];
        acutalNodes = new BinaryNode[np];
        for(int i =0 ;i< np;i++){
            nodes[i] = acutalNodes + i;
            nodes[i]->index = i;
        }
        BinaryNode** bn = reinterpret_cast<BinaryNode**>(nodes);
        heap = new BinaryNode*[np];
    }
    GeneralNode deleteMin(){
        GeneralNode gn = *(heap[0]);
        heap[0] = heap[heapSize- 1];
        heap[0]->position = 0;
        int cur_pos = 0,newVal = heap[heapSize -1 ]->distance;
        heapSize --;
        int leftChild = cur_pos * 2 + 1;
        int rightChild = cur_pos * 2 + 2;
        while (cur_pos < heapSize && (leftChild < heapSize && heap[leftChild]->distance < newVal || rightChild < heapSize && heap[rightChild]->distance < newVal)) {        //percolate down
            int tg ;
            if(leftChild < heapSize && rightChild < heapSize){
                if(heap[leftChild]->distance < heap[rightChild]->distance) tg = leftChild;
                else tg = rightChild;
            }else if(leftChild < heapSize) tg = leftChild;
            else tg = rightChild;
            SWAP(heap[cur_pos],heap[tg]);
            heap[cur_pos]->position = cur_pos;
            heap[tg]->position = tg;
            cur_pos = tg;
            leftChild = cur_pos * 2 + 1;
            rightChild = cur_pos * 2 + 2;
        }
        return gn;
    }
    void insert(int index,ull dist){
        heap[heapSize] = static_cast<BinaryNode*>(nodes[index]);
        heap[heapSize]->position = heapSize;
        nodes[index]->inHeap = true;
        nodes[index]->distance = dist;
        int cur_pos = heapSize;
        int parent_pos = (cur_pos + 1)/2 - 1;
        while(cur_pos != 0 && heap[cur_pos]->distance < heap[parent_pos]->distance){
            SWAP(heap[cur_pos],heap[parent_pos]);
            heap[cur_pos]->position = cur_pos;
            heap[parent_pos]->position = parent_pos;
            cur_pos = parent_pos;
            parent_pos = (cur_pos + 1)/2 - 1;
        }
        heapSize ++;
    }
    void decreaseKey(int idx,ull newVal){
        int cur_pos = static_cast<BinaryNode*>(nodes[idx])->position;
        int parent_pos = (cur_pos + 1)/2 - 1;
        if(newVal < nodes[idx]->distance){      //percolate up
            while(cur_pos != 0 && newVal < heap[parent_pos]->distance){
                SWAP(heap[cur_pos],heap[parent_pos]);
                heap[cur_pos]->position = cur_pos;
                heap[parent_pos]->position = parent_pos;
                cur_pos = parent_pos;
                parent_pos = (cur_pos + 1)/2 - 1;
            }
        }
        nodes[idx]->distance = newVal;
    }
    bool isEmpty(){
        return heapSize == 0;
    }
    void free(){
        delete[] acutalNodes;
        delete[] nodes;
        if (heap != nullptr)delete[] heap;
        heap = nullptr;
        nodes = nullptr;
    }

};


#endif
```

`leftistiHeap.hpp`

```c++
#ifndef LEFTIST_HEAP_HPP
#define LEFTIST_HEAP_HPP

#include "commons.hpp"

struct LeftistNode : public GeneralNode
{
    unsigned int npl;
    LeftistNode *leftchild;  // pointer to leaeft child
    LeftistNode *rightchild; // pointer to right child
    LeftistNode *parent;     // pointer to its parent
    LeftistNode()
    {
        npl = 0;
        leftchild = rightchild = NULL;
        parent = NULL;
    }
};

class LeftistHeap : public GeneralHeap
{
private:
    struct LeftistNode *root;       // record the root of this heap

public:
    void initialize(Point *pl, int np)
    {
        nodes = new GeneralNode *[np];
        LeftistNode *temp = new LeftistNode[np];
        for (int i = 0; i < np; i++)
        {
            nodes[i] = temp + i; // make all these pointer to be NULL because there is no node in this heap yet
            nodes[i]->index = i;
        }

        root = NULL;
    }
    GeneralNode deleteMin()
    {
        LeftistNode min = *root;                         // create a node to contain that min item
        root = merge(root->leftchild, root->rightchild); // merge the rest nodes to make it a leftist heap again
        if (root != nullptr)
            root->parent = nullptr;
        return min;
    }
    void insert(int index, ull dist)
    {
        if (nodes[index]->inHeap)
            return;
        LeftistNode *inserted = static_cast<LeftistNode *>(nodes[index]);
        inserted->distance = dist;
        inserted->inHeap = true;
        inserted->index = index;
        LeftistNode *newroot = merge(root, inserted);
        root = newroot;
        // LeftistNode node; // create a new leftistNode to be added to the heap
        // node.index = index;
        // node.distance = dist;
        // node.leftchild = node.rightchild = NULL;
        // node.npl = 0;
        // LeftistNode *newnode = &node;
        // nodes[index] = newnode;                  // record the node in nodes array
        // this->root = merge(this->root, newnode); // merge this new node with origin heap
    }
    void decreaseKey(int idx, ull newVal)
    {
        LeftistNode *cur = static_cast<LeftistNode *>(nodes[idx]);
        if (!cur->inHeap)
            return;
        cur->distance = newVal; // change the state of that node
        while (cur != root && cur->distance <= cur->parent->distance)
        {
            if (cur->distance < cur->parent->distance)
                cur = percolateup(cur);
            else
            {
                if (cur->index < cur->parent->index)
                    cur = percolateup(cur);
                else
                    break;
            }
        }
    }
    // there may be many bugs, one way to implement this easily is to use merge too

    LeftistNode *percolateup(LeftistNode *cur)
    {
        LeftistNode *temp = cur;
        unsigned int tempindex = cur->index;
        ull tempdistance = cur->distance;

        cur->index = cur->parent->index;
        cur->distance = cur->parent->distance;
        nodes[cur->parent->index] = cur;

        cur = cur->parent;
        cur->index = tempindex;
        cur->distance = tempdistance;
        nodes[cur->index] = cur;
        return cur;
    }

    bool isEmpty()
    {
        return !this->root; // if root is null, return 1, else return 0
    }
    void free()
    {
        delete[] nodes;
        freenodes(root);
    }
    void freenodes(struct LeftistNode *node)
    {
        if (node == nullptr)
            return;
        else
        {
            freenodes(node->leftchild);
            freenodes(node->rightchild);
            delete node;
        }
    }
    struct LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
    {
        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;
        if (h1->distance <= h2->distance)
        {
            if (h1->distance == h2->distance && h1->index > h2->index)
                return merge1(h2, h1);
            else
                return merge1(h1, h2);
        }
        else
            return merge1(h2, h1);
    }

    struct LeftistNode *merge1(struct LeftistNode *h1, struct LeftistNode *h2)
    {
        if (h1->leftchild == nullptr) // if the left child of h1 is empty, then just lat h2 be the leftchild
        {
            h1->leftchild = h2;
            h2->parent = h1;
        }
        else
        {
            h1->rightchild = merge(h1->rightchild, h2); // recursively merge the right child and h2
            h1->rightchild->parent = h1;
        }
        if (h1->rightchild == NULL)
            return h1;
        if (h1->rightchild->npl > h1->leftchild->npl) // adjust the position of left child and right child according to npl
        {
            struct LeftistNode *temp = h1->rightchild;
            h1->rightchild = h1->leftchild;
            h1->leftchild = temp;
        }
        h1->npl = h1->rightchild->npl + 1; // update the npl of h1 with smaller npl of its right child
        return h1;
    }
};

#endif
```

`skewHeap.hpp`

```c++
#ifndef SKEW_HEAP_HPP
#define SKEW_HEAP_HPP

#include "commons.hpp"

struct SkewNode : public GeneralNode
{
    struct SkewNode *leftchild;
    struct SkewNode *rightchild;
    struct SkewNode *parent;
    SkewNode()
    {
        leftchild = rightchild = NULL;
        parent = NULL;
    }
};

class SkewHeap : public GeneralHeap
{
private:
    struct SkewNode *root; // record the root of this heap
public:
    void initialize(Point *pl, int np)
    {
        nodes = new GeneralNode *[np];
        SkewNode *temp = new SkewNode[np];
        for (int i = 0; i < np; i++)
        {
            nodes[i] = temp + i; // make all these pointer to be NULL because there is no node in this heap yet
            nodes[i]->index = i;
        }

        root = NULL;
    }
    GeneralNode deleteMin()
    {
        SkewNode min = *root;                            // create a node to contain that min item
        root = merge(root->leftchild, root->rightchild); // merge the rest nodes to make it a leftist heap again
        if (root != nullptr)
            root->parent = nullptr;
        return min;
    }
    void insert(int index, ull dist)
    {
        if (nodes[index]->inHeap)
            return;
        SkewNode *inserted = static_cast<SkewNode *>(nodes[index]);
        inserted->distance = dist;
        inserted->inHeap = true;
        inserted->index = index;
        SkewNode *newroot = merge(root, inserted);
        root = newroot;
    }
    void decreaseKey(int idx, ull newVal)
    {
        SkewNode *cur = static_cast<SkewNode *>(nodes[idx]);
        if (!cur->inHeap)
            return;
        cur->distance = newVal; // change the state of that node
        while (cur != root && cur->distance <= cur->parent->distance)
        {
            if (cur->distance < cur->parent->distance)
                cur = percolateup(cur);
            else
            {
                if (cur->index < cur->parent->index)
                    cur = percolateup(cur);
                else
                    break;
            }
        }
    }

    SkewNode *percolateup(SkewNode *cur)
    {
        SkewNode *temp = cur;
        unsigned int tempindex = cur->index;
        ull tempdistance = cur->distance;

        cur->index = cur->parent->index;
        cur->distance = cur->parent->distance;
        nodes[cur->parent->index] = cur;

        cur = cur->parent;
        cur->index = tempindex;
        cur->distance = tempdistance;
        nodes[cur->index] = cur;
        return cur;
    }
    bool isEmpty()
    {
        return !this->root;
    }
    void free()
    {
        delete[] nodes;
        freenodes(root);
    }
    void freenodes(struct SkewNode *node)
    {
        if (node == nullptr)
            return;
        else
        {
            freenodes(node->leftchild);
            freenodes(node->rightchild);
            delete node;
        }
    }
    SkewNode *merge(SkewNode *h1, SkewNode *h2)
    {
        SkewNode *temp;
        if (h1 == NULL)
            return h2;
        if (h2 == nullptr)
            return h1;
        if (h1->distance <= h2->distance)
        {
            if (h1->distance == h2->distance && h1->index > h2->index)
                return merge1(h2, h1);
            else
                return merge1(h1, h2);
        }
        else
            return merge1(h2, h1);
    }

    SkewNode *merge1(SkewNode *h1, SkewNode *h2)
    {
        SkewNode *temp = h1->leftchild;
        h1->leftchild = merge(h1->rightchild, h2);
        h1->leftchild->parent = h1;
        h1->rightchild = temp;
        if (h1->rightchild != nullptr)
            h1->rightchild->parent = h1;
        return h1;
    }
};

#endif
```

`FibonacciHeap.hpp`

```c++
#ifndef FIBONACCI_HEAP_HPP
#define FIBONACCI_HEAP_HPP

#include "commons.hpp"
#include <cmath>
#include <assert.h>

struct FibonacciNode : public GeneralNode
{
	unsigned int degree;            // the degree of this node
	bool mark;                      // lose its child or not
	struct FibonacciNode* Leftsib;  // the left subling of this node
	struct FibonacciNode* Rightsib; // the right subling of this node
	struct FibonacciNode* Parent;   // the parent of this node
	struct FibonacciNode* Child;    // a random child of the node

	FibonacciNode() {
		degree = 0;
		mark = false;
		Leftsib = Rightsib = Parent = Child = nullptr;
	}
};

class FibonacciHeap : public GeneralHeap
{
	struct FibonacciNode** degree_count;
	struct FibonacciNode* Min; // point to the minest distance in this heap
	ull node_count;
	ull max_nodes;
	ull max_degree;
public:


	void initialize(Point* pl, int np)
	{
		Min = nullptr;
		max_nodes = np;
		nodes = new GeneralNode * [np];
		static const float phi = (sqrt(5) + 1) / 2;
		FibonacciNode* temp = new FibonacciNode[np];
		max_degree = ceil(log(np) / log(phi)) + 3;
		degree_count = new FibonacciNode * [max_degree];
		for (int i = 0; i < np; i++) {
			nodes[i] = temp + i;
			nodes[i]->index = i;
		}
		for (int i = 0; i < max_degree; i++)degree_count[i] = nullptr;
		node_count = 0;
		return;
	}

	GeneralNode deleteMin()
	{
		node_count--;
		struct FibonacciNode* p;
		struct FibonacciNode* pr;
		GeneralNode res;
		if (Min->Child != nullptr)
		{
			p = Min->Child;
			Min->Child = nullptr;
			int i;
			for (i = 0; i < Min->degree; i++)
			{
				pr = p->Rightsib;
				p->Leftsib = Min->Leftsib;
				p->Leftsib->Rightsib = p;
				p->Rightsib = Min;
				Min->Leftsib = p;
				p->Parent = nullptr;
				p = pr;
			}
		}
		//If there's only one node in the heap
		if (Min->Rightsib == Min) {
			res = *Min;
			Min->inHeap = false;
			Min = nullptr;
			return res;
		}
		Min->Rightsib->Leftsib = Min->Leftsib;
		Min->Leftsib->Rightsib = Min->Rightsib;
		Min->inHeap = false;
		res = *Min;
		if (res.index == 1396) {
			int i = 0;
			i += 30;
		}
		Min = Min->Rightsib;
		p = Min;
		FibonacciNode* last = Min->Leftsib;
		FibonacciNode* pr_old;
		memset(degree_count, 0, (max_degree) * sizeof(FibonacciNode*));
		do
		{
			pr_old = pr = p;
			p = p->Rightsib;
			while (degree_count[pr->degree]) {
				if (pr->degree == 6) {
					int i = 0;
					i += 30;
				}
				int oldDegree = pr->degree;
				pr = link(degree_count[pr->degree], pr);
				if (pr->degree == 6) {
					int i = 0;
					i += 30;
				}
				degree_count[oldDegree] = nullptr;
			}
			degree_count[pr->degree] = pr;
			if (pr && pr->distance <= Min->distance)Min = pr;
		} while (pr_old != last);
		return res;
	}

	void insert(int index, ull dist)
	{
		if (nodes[index]->inHeap) {
			decreaseKey(index, dist);
			return;
		}
		// if it is not in the heap, insert the node into the left of the min
		node_count++;
		nodes[index]->inHeap = true;
		struct FibonacciNode* n1 = static_cast<FibonacciNode*>(nodes[index]);
		n1->distance = dist;
		if (Min == nullptr)
		{
			Min = n1;
			n1->Leftsib = n1;
			n1->Rightsib = n1;
		}
		else
		{
			n1->Leftsib = Min->Leftsib;
			n1->Leftsib->Rightsib = n1;
			n1->Rightsib = Min;
			Min->Leftsib = n1;
			if (n1->distance <= Min->distance)
				Min = n1; // update the Min
		}

	}

	void decreaseKey(int idx, ull newVal)
	{
		FibonacciNode** fn = reinterpret_cast<FibonacciNode**>(nodes);
		struct FibonacciNode* p = fn[idx];
		p->distance = newVal;
		if (p->Parent == nullptr) {
			if(newVal <= Min->distance)Min = p;
			return;
		}
		else if (p->distance >= p->Parent->distance)return;
		struct FibonacciNode* n;
		do
		{
			n = p->Parent;
			p->Parent = nullptr;

			//remove p from its parent's childs and the links from p's siblings
			if (p->Rightsib)p->Rightsib->Leftsib = p->Leftsib;
			if (p->Leftsib)p->Leftsib->Rightsib = p->Rightsib;
			if (n && n->Child == p) n->Child = p->Rightsib ? p->Rightsib : p->Leftsib;
			if (n)n->degree--;

			p->Leftsib = Min->Leftsib;
			p->Leftsib->Rightsib = p;
			Min->Leftsib = p;
			p->Rightsib = Min;
			p->mark = false;

			//update the Min pointer
			if (Min->distance >= p->distance)Min = p;
			p = n;
		} while (p && p->mark);
		if (p && p->Parent) p->mark = true;
		return;
	}

	bool isEmpty()
	{
		return Min == nullptr;
	}

	static FibonacciNode* link(FibonacciNode* p1, FibonacciNode* p2)
	{
		if (p1 == nullptr && p2 == nullptr) return nullptr;
		if (p1 == nullptr) return p2;
		if (p2 == nullptr) return p1;

		if (p1->distance < p2->distance) return link1(p1, p2);
		else return link1(p2, p1);
	}

	static FibonacciNode* link1(FibonacciNode* p1, FibonacciNode* p2)
	{
		//I think we should always keep p1->child the leftmost children .
		// Since you iterated from left to right in DeleteMin().
		p2->Leftsib->Rightsib = p2->Rightsib;
		p2->Rightsib->Leftsib = p2->Leftsib;
		p2->Rightsib = p1->Child;
		p2->Leftsib = nullptr;
		if (p1->Child)p1->Child->Leftsib = p2;
		p1->Child = p2;
		p2->Parent = p1;
		p1->degree++;
		assert(p1->Leftsib != nullptr);
		return p1;
	}

	void free()
	{
		for (int i = 0; i < max_nodes; i++) nodes[i];
		delete[] degree_count;
		delete[] nodes;
	}
};

#endif
```

`binomialHeap.hpp`

```c++
#ifndef BINOMIAL_HEAP2_HPP
#define BINOMIAL_HEAP2_HPP

#include "commons.hpp"
#include <cmath>
#include <stdexcept>

struct BinomialNode : public GeneralNode {
	BinomialNode* child;
	BinomialNode* right;
	BinomialNode* parent;
	int degree;

	BinomialNode() {
		parent = child = right = nullptr;
		degree = 0;
	}
};

class BinomialHeap : public GeneralHeap {
private:
	BinomialNode** roots;
	int max_nodes;
	int max_degree;
	int node_count;

	static BinomialNode* link(BinomialNode* a, BinomialNode* b) {
		if (a->degree != b->degree)return nullptr;
		if (a->distance > b->distance)SWAP(a, b);
		a->degree++;
		b->right = a->child;
		a->child = b;
		b->parent = a;
		return a;
	}
	void insertRoot(BinomialNode* node) {
		while (roots[node->degree]) {
			int deg = node->degree;
			node = link(node, roots[node->degree]);
			roots[deg] = nullptr;
		}
		roots[node->degree] = node;
	}
public:

	void initialize(Point* pl, int np)
	{
		max_degree = ceil(log2(np)) + 2;
		max_nodes = node_count;
		roots = new BinomialNode * [max_degree];
		nodes = new GeneralNode * [np];
		BinomialNode* temp_node = new BinomialNode[np];
		for (int i = 0; i < np; i++) {
			nodes[i] = temp_node + i;
			nodes[i]->index = i;
		}
		for (int i = 0; i < max_degree; i++)roots[i] = nullptr;
		node_count = 0;
		return;
	}
	GeneralNode deleteMin()
	{
		if (!node_count) throw std::runtime_error("DeleteMin error : empty heap");
		node_count--;
		int min_idx = 0;
		ull min = -1;
		for (int i = 0; i < max_degree; i++) {
			if (roots[i] && roots[i]->distance < min) {
				min_idx = i;
				min = roots[i]->distance;
			}
		}
		BinomialNode* pMin = roots[min_idx];
		pMin->inHeap = false;
		roots[min_idx] = nullptr;
		GeneralNode res = *pMin;
		if (pMin->degree) {
			BinomialNode* n = pMin->child;
			while (n) {
				BinomialNode* nxt = n->right;
				n->right = n->parent = nullptr;
				insertRoot(n);
				n = nxt;
			}
		}
		return res;
	}
	void insert(int index, ull dist)
	{
		if (nodes[index]->inHeap)return;
		node_count++;
		nodes[index]->inHeap = true;
		nodes[index]->distance = dist;
		insertRoot(static_cast<BinomialNode*>(nodes[index]));
	}
	void decreaseKey(int idx, ull newVal)
	{
		if (!nodes[idx]->inHeap)return;
		if (nodes[idx]->distance < newVal)return;
		BinomialNode* n = static_cast<BinomialNode*>(nodes[idx]), * p = n->parent;
		n->distance = newVal;
		while (p && n->distance < p->distance) {
			SWAP(nodes[n->index], nodes[p->index]);
			SWAP(nodes[n->index]->index, nodes[p->index]->index);
			SWAP(nodes[n->index]->distance, nodes[p->index]->distance);
			n = p;
			p = n->parent;
		}
	}
	bool isEmpty()
	{
		return !node_count;
	}
	void free()
	{
		for(int i = 0;i < max_nodes;i++)delete nodes[i];
		delete[] nodes;
		delete[] roots;
		nodes = NULL;
	}

};


#endif
```

`main.cpp`

```c++
#include <iostream>
#include <cstdio>
#include <fstream>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

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

GeneralHeap* HeapList[] = {
	new BinaryHeap,
	//new LeftistHeap ,
	//new SkewHeap , 
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
	string heapNames[HEAP_COUNT];		//current heap name
	ull time[HEAP_COUNT];				//time usage (in milliseconds)
};

void loadFile(string filename, Point*& pointList, long long int& nPoints, long long int& nEdges) {
	//first run
	FILE* file = fopen(filename.c_str(), "r");
	char sbuf[100];
	int tot_edges = 0;
	while (!feof(file)) {
		char op;
		op = fgetc(file);
		if (op == 'c') {
			fgets(sbuf, 100, file);
			continue;
		}
		else if (op == 'a') {
			int a, b, l;
			fscanf(file, "%d%d%d", &a, &b, &l);
			pointList[a - 1].numAdjs++;
			pointList[b - 1].numAdjs++;
			tot_edges += 2;
		}
		else if (op == 'p') {
			fscanf(file, "%s", sbuf);
			fscanf(file, "%d%d", &nPoints, &nEdges);
			pointList = new Point[nPoints];
		}
		else continue;
	}
	ull* edgePool = new ull[tot_edges];
	ull* edgeCursor = edgePool;
	unsigned int* adjPool = new unsigned int[tot_edges];
	unsigned int* adjCursor = adjPool;
	for (int i = 0; i < nPoints; i++) {
		pointList[i].edges = edgeCursor;
		pointList[i].adjPoints = adjCursor;
		edgeCursor += pointList[i].numAdjs;
		adjCursor += pointList[i].numAdjs;
		pointList[i].numAdjs = 0;
	}
	rewind(file);
	clearerr(file);
	//second run
	while (!feof(file)) {
		char op;
		op = fgetc(file);
		if (op == 'c') {
			fgets(sbuf, 100, file);
			continue;
		}
		else if (op == 'a') {
			int a, b, l;
			fscanf(file, "%d%d%d", &a, &b, &l);
			int na = pointList[a - 1].numAdjs;
			int nb = pointList[b - 1].numAdjs;
			pointList[a - 1].adjPoints[na] = b - 1;
			pointList[b - 1].adjPoints[nb] = a - 1;
			pointList[a - 1].edges[na] = l;
			pointList[b - 1].edges[nb] = l;

			pointList[a - 1].numAdjs++;
			pointList[b - 1].numAdjs++;
		}
		else if (op == 'p') {
			fgets(sbuf, 100, file);
			continue;
		}
		else continue;
	}
	fclose(file);
}


clock_t dijk(Point* pl, int np, int o, GeneralHeap* heap) {
	for (int i = 0; i < np; i++) {
		pl[i].distance = -1;
		pl[i].visited = 0;
	}
	pl[o].distance = 0;
	heap->initialize(pl, np);
	heap->insert(o, 0);
	clock_t clk = clock();
#ifdef DEBUG
	ofstream ofs("test.log");
#endif
	while (!heap->isEmpty()) {
		GeneralNode node = heap->deleteMin();
#ifdef DEBUG
		ofs << "dequeue " << node.index << " " << node.distance << endl;
#endif
		auto& p = pl[node.index];
		p.visited = true;
		p.distance = node.distance;
		for (int i = 0; i < pl[node.index].numAdjs; i++) {
			ull d2 = p.edges[i] + node.distance;
			GeneralNode* adjNode = heap->nodes[p.adjPoints[i]];
			if (pl[adjNode->index].visited)continue;
			if (d2 < adjNode->distance) {
#ifdef DEBUG
				ofs << "decrease " << node.index << "->" << adjNode->index << " = " << d2 << endl;
#endif
				if (!adjNode->inHeap) heap->insert(adjNode->index, d2);
				else heap->decreaseKey(adjNode->index, d2);
			}
		}
	}
	clk = clock() - clk;
	heap->free();
	return clk;
}

Record runTest(string filename, int numIters) {
	Point* pointList;
	Record result;
	result.numIters = numIters;
	long long int nv = 0, ne = 0;
	loadFile(filename, pointList, nv, ne);
	result.nv = nv;
	result.ne = ne;
	for (int i = 0; i < HEAP_COUNT; i++) {
		result.heapNames[i] = HeapList[i]->HeapName;
		result.time[i] = 0;
		for (int it = 0; it < numIters; it++) {
			clock_t start = clock();
			dijk(pointList, nv, it % nv, HeapList[i]);
			result.time[i] += clock() - start;
			for (int i = 0; i < nv; i++) {
				pointList[i].distance = -1;
				pointList[i].visited = false;
			}
		}
		result.time[i] /= numIters;
	}

	return result;
}

int main() {
	// string filenames[] = {
	// 	"USA-road-d.NY.gr",
	// 	"USA-road-d.COL.gr",
	// 	"USA-road-d.FLA.gr",
	// 	"USA-road-d.CAL.gr",
	// 	"USA-road-d.E.gr",
	// 	"USA-road-d.W.gr",
	// 	"USA-road-d.CTR.gr",
	// 	"USA-road-d.USA.gr"
	// };

	string filenames[] = {
		"1.in",
		"2.in",
		"3.in",
		"4.in",
		"5.in"
	};

	Record stats[5];
	for (int i = 0; i < 5; i++)stats[i] = runTest(filenames[i], 1);
	ofstream ofs("stats.out");
	ofs << "Statistics Results" << endl;
	for (int i = 0; i < 5; i++) {
		ofs << stats[i].fileName << "\t" << stats[i].nv << "\t" << stats[i].ne << "\t" << stats[i].numIters;
		for (int j = 0; j < HEAP_COUNT; j++)ofs << "\t" << stats[i].time[j] ;
		ofs << endl;
	}
	ofs.close();
	return 0;
}
```

