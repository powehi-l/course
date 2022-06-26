/*******************************************************************************
 * File name: data.h
 * Author: 
 * Version: 
 * Date: 2022-5-1
 * Description: definition of basic data structure
 * > Encoding: UTF-8
 ******************************************************************************/
#ifndef _DATA_H_
#define _DATA_H_

#include <string>

using namespace std;

/* including the character c and frequency f */
struct Character {
	char c;
	int f;

	Character();
	Character(char _c, int _f);
	bool operator < (const Character &y) const {return c < y.c;}

	/* Read a Character from stdin (using cin) */
	void Read();
};

/* including the character c and its 01 string code code */
struct Code {
	char c;
	string code;
	
	Code();
	Code(char _c, string _code);
	bool operator < (const Code &y) const {return c < y.c;}

	/* Read a Code from stdin (using cin) */
	void Read();
};

/* calculate the total frequency of list ch and code, the number of characters is size */
int CodeFreqCount(Character *ch, Code *code, int size);

#endif
