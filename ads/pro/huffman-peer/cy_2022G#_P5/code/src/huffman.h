/*******************************************************************************
 * File name: huffman.h
 * Author: 
 * Version: 
 * Date: 2022-5-1
 * Description: implement huffman tree and the algorithm
 * > Encoding: UTF-8
 ******************************************************************************/
#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "data.h"

using namespace std;

/* Huffman Tree */
class HuffmanTree {
public:
	HuffmanTree();
	HuffmanTree(Character *ch, int size); // initialize the tree with a set of characters and their frequency
	~HuffmanTree();

	struct HuffmanNode {
		Character data;
		HuffmanNode *lch, *rch;

		HuffmanNode();
		HuffmanNode(Character c);

		/* using for priority_queue, min heap
		 * first compare the frequency
		 * then compare the ASCII character (not necessary) */
		bool operator < (const HuffmanNode &y) const {
			if (data.f != y.data.f) return data.f > y.data.f;
			return data.c > y.data.c;
		}
	};

	/* build the tree with a set of characters and their frequency */
	void Build(Character *ch, int size);

	/* generate the 01 string code from huffman tree
	 * the characters are not sorted */
	void GenCode(Code *code);
	
	#ifdef DEBUG
	void Print();
	#endif
private:
	HuffmanNode root;

	/* using recursive function to travere tree nodes in preorder
	 * when reach the leaf node, store the 01 string code into code[] */
	void GenCodeNode(HuffmanNode *hn, Code *code);
	
	#ifdef DEBUG
	void PrintNode(HuffmanNode *hn);
	#endif
};

#endif
