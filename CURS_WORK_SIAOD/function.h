#pragma once
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include <list>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 4000
#define MAX 2
#define MIN 1

struct record {
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};

struct BtreeNode {
	int val[MAX + 1];
	int count;
	BtreeNode* link[MAX + 1];
};

struct codeShennon {
	int symbol;
	double frequency;
};

namespace saod {
	class queue
	{
		record* arr[SIZE];
		int capacity = SIZE;
		int front = 0;
		int rear = -1;
		int count = 0;

	public:
		// queue(int size = SIZE);
		void remove();
		void add(record* x);
		record* peek();
		int size();
		bool isEmpty();
		bool isFull();
	};
}
void OpenDatabase(std::string filename, std::fstream& file);
void ReadDatabase(std::fstream& file, std::vector<record>& vector);
void QuickSortStruct(std::vector<record*>& indexArray, int left, int right);
int Compare(record * record1, record * record2);
void PrintDatabase(std::vector<record*> index);
void PrintDatabase(std::vector<record> record);
int bin_search(std::vector<record*> ind, char* key, int min, int max);
int BinCompare(char* key, char* title);

/* creating new node */
BtreeNode* createNode(int val, BtreeNode* child);
/* Places the value in appropriate position */
void addValToNode(int val, int pos, BtreeNode* node, BtreeNode* child);

/* split the node */
void splitNode(int val, int* pval, int pos, BtreeNode* node, BtreeNode* child,
	BtreeNode** newNode);

/* sets the value val in the node */
int setValueInNode(int val, int* pval, BtreeNode* node, BtreeNode** child);

/* insert val in B-Tree */
void insertion(int val);

/* B-Tree Traversal */
void traversal();
void traversal(BtreeNode* MyNode);
int search(BtreeNode* myNode, int data);
void search(int data);

codeShennon* symbolFrequency(codeShennon* symbolFreq, int size, int counter, int* freq);

