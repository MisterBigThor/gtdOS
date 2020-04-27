#ifndef _string_h
#define _string_h

#include "bool.h"

typedef char* string;

//Return the size of a string
int size(string s);

//Returns true if the strings are equal
bool cmp(string a, string b);

#endif