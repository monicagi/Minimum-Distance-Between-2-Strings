
#ifndef EDITDISTHEADER_H
#define EDITDISTHEADER_H

//#include<iostream>
//#include <algorithm>
//#include <stdio.h>
//#include<stdlib.h>
#include <string>
//#include <iomanip>

using namespace std;

int min(int x, int y, int z);
int editDist(string str1, string str2, int m, int n);
void addSpace(string str, int index);
void delLetter(string str, int index);
void addEdits(int index, char c);
void displayFormats(string str2, string str1);
void displayTable(int v[50][50], string s1, string s2);
void findEdits(string s1, string s2);
int count(string s1, string s2);


#endif