#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

class Line
{
public:
	int len;
	char *String;
	char time_buf[9];

public:
	Line();
	Line(int, char*);
	Line(const Line&);
	~Line();
	void Sum(Line, Line);
	void Print();
	void Change(char*);
};
