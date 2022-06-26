/*******************************************************************************
 * File name: main.cpp
 * Author: 
 * Version: 
 * Date: 2022-5-1
 * Description: main task of 
 ******************************************************************************/
#include <iostream>
#include <algorithm>

#include "data.h"
#include "huffman.h"

using namespace std;

const int kMaxChNum = 63; // the max number of different characters

/* for some characters and their code, judge if exists some code being other code's prefix
 * if exists, return true, else return false
 * size is the number of characters with codes */
bool JudgePrefix(Code *code, int size);

int main(int argc, char const *argv[])
{
	int n, m;
	Character ch[kMaxChNum+5];

	// input the n characters with frequency, and sort them in ASCII ascending order
	cin>>n;
	for (int i = 0; i < n; ++i) ch[i].Read();
	sort(ch, ch+n);

	HuffmanTree ht(ch, n); // huffman tree build from ch[]

	Code huffman_code[kMaxChNum+5];
	ht.GenCode(huffman_code); // get the code of huffman tree, store into huffman_code[]
	sort(huffman_code, huffman_code+n); // sort in ASCII ascending order

	int huffman_freq_count;
	huffman_freq_count = CodeFreqCount(ch, huffman_code, n); // get the total frequency of huffman code
	#ifdef DEBUG
	for (int i = 0; i < n; ++i) cout<<"("<<huffman_code[i].c<<","<<huffman_code[i].code<<")"<<endl;
	#endif

	// deal with each student's submission
	cin>>m;
	while (m--) {
		// read and sort the code
		Code code[kMaxChNum+5];
		for (int i = 0; i < n; ++i) code[i].Read();
		sort(code, code+n);

		// two judgments:
		// 1. multiply each character's frequency and code's length, sum them up
		//    if this total frequency is greater than huffman code's total frequency, the submission is incorrect
		// 2. judge if some code can be another code's prefix
		//    if this situation exits, the submission is incorrect
		if (CodeFreqCount(ch, code, n) > huffman_freq_count || JudgePrefix(code, n)) {
			cout<<"No"<<endl;
		} else {
			cout<<"Yes"<<endl;
		}
	}

	return 0;
}

bool JudgePrefix(Code *code, int size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = i+1; j < size; ++j) {
			// strl: the longer code
			// strs: the shorter code
			string strl(code[i].code), strs(code[j].code);
			if (strl.length() < strs.length()) swap(strl, strs);

			// if strs is the prefix of strl, return true
			if (strl.substr(0, strs.length()) == strs) {
				return true;
			}
		}
	}
	return false;
}
