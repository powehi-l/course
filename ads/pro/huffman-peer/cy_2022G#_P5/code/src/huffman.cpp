/*******************************************************************************
 * File name: huffman.cpp
 * Author: 
 * Version: 
 * Date: 2022-5-1
 * Description: implement huffman tree and the algorithm
 * > Encoding: UTF-8
 ******************************************************************************/
#include "huffman.h"

#include <queue>
#include <stack>
#ifdef DEBUG
#include <iostream>
#endif

HuffmanTree::HuffmanTree() {}
HuffmanTree::HuffmanTree(Character *ch, int size) {Build(ch, size);}

HuffmanTree::HuffmanNode::HuffmanNode() {}
/* initialize: the data (character) is c, lch and rch is NULL */
HuffmanTree::HuffmanNode::HuffmanNode(Character c) : data(c), lch(NULL), rch(NULL) {}
HuffmanTree::~HuffmanTree() {}

void HuffmanTree::Build(Character *ch, int size)
{
	priority_queue<HuffmanNode> htree;

	// push all leaf node into priority_queue
	for (int i = 0; i < size; ++i)
		htree.push(HuffmanNode(ch[i]));

	while (htree.size() > 1) {
		// hn1, hn2: the two minimum node
		// newhn: the node of hn1 + hn2 (add up the two nodes' frequency)
		HuffmanNode hn1, hn2, newhn;

		// new the space for newhn's two children
		newhn.lch = new HuffmanNode;
		newhn.rch = new HuffmanNode;

		*newhn.lch = htree.top(); htree.pop();
		*newhn.rch = htree.top(); htree.pop();
		// the character of interval nodes is '\0' 
		newhn.data = Character('\0', newhn.lch->data.f + newhn.rch->data.f);

		htree.push(newhn);
	}

	root = htree.top(); // set the root
}

// static global variables for tree traversal and answer recoding
static int code_size; // the subscript of code[]
static string code_str; // 01 string code generated from tree traversal
void HuffmanTree::GenCode(Code *code)
{
	// initialize
	code_size = 0;
	code_str = "";

	GenCodeNode(&root, code);
}
void HuffmanTree::GenCodeNode(HuffmanNode *hn, Code *code)
{
	if (hn->data.c) { // leaf node
		code[code_size++] = Code(hn->data.c, code_str);
		return;
	}
	if (hn->lch != NULL) { // left child
		code_str.push_back('0');
		GenCodeNode(hn->lch, code);
		code_str.pop_back();
	}
	if (hn->rch != NULL) { // right child
		code_str.push_back('1');
		GenCodeNode(hn->rch, code);
		code_str.pop_back();
	}
}

#ifdef DEBUG
void HuffmanTree::Print()
{
	PrintNode(&root);
}
void HuffmanTree::PrintNode(HuffmanNode *hn)
{
	if (hn == NULL) return;
	cout<<"("<<hn->data.c<<","<<hn->data.f<<") beg"<<endl;
	cout<<"lch:"<<endl;
	PrintNode(hn->lch);
	cout<<"rch:"<<endl;
	PrintNode(hn->rch);
	cout<<"("<<hn->data.c<<","<<hn->data.f<<") ret"<<endl;
}
#endif
