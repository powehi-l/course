/*******************************************************************************
 * File name: data.cpp
 * Author: 
 * Version: 
 * Date: 2022-5-1
 * Description: definition of basic data structure
 * > Encoding: UTF-8
 ******************************************************************************/
#include "data.h"

#include <iostream>

Character::Character() {}
Character::Character(char _c, int _f) : c(_c), f(_f) {}
void Character::Read() {cin>>c>>f;}

Code::Code() {}
Code::Code(char _c, string _code) : c(_c), code(_code) {}
void Code::Read() {cin>>c>>code;}

int CodeFreqCount(Character *ch, Code *code, int size)
{
	int count = 0;
	for (int i = 0; i < size; ++i) {
		// multiply each character's frequency and code's length, sum them up to get total frequency
		count += ch[i].f * code[i].code.length();
	}
	return count;
}
