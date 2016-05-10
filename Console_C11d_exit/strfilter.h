#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include <windows.h>
#include <stdio.h>
#include <string>


class strfilter
{
public:
	string* pstr;
	int nargs;
	string keys[5];
	strfilter(int,string*);
	string ArgReplace(string);
	void print();
	~strfilter(void);
};
