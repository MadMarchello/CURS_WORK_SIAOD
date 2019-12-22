#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
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
#include <iomanip>
#define SIZE 4000
#define MAX 2
#define MIN 1
const int size_code = 256;
const std::string databaseName = "D:\\testBase1.dat";

struct record {
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};

struct BtreeNode {
	record* val[MAX + 1];
	int count;
	BtreeNode* link[MAX + 1];
};

struct codeShennon {
	char symbol;
	long double probality;
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
void QuickSortStruct(codeShennon* symbolFrequency, int left, int right);
int Compare(record * record1, record * record2);

void PrintDatabase(std::vector<record*> index);
void PrintDatabase(std::vector<record> record);

int bin_search(std::vector<record*> ind, char* key, int min, int max);
int BinCompare(char* key, char* title);

BtreeNode* createNode(record* val, BtreeNode* child);
void addValToNode(record* val, int pos, BtreeNode* node, BtreeNode* child);
void splitNode(record* val, record** pval, int pos, BtreeNode* node, BtreeNode* child, BtreeNode** newNode);
int setValueInNode(record* val, record** pval, BtreeNode* node, BtreeNode** child);
void insertion(record* val);
void traversal();
void traversal(BtreeNode* MyNode);

void search(BtreeNode* myNode, int data, saod::queue q);
void search(int data, saod::queue q);

void Shennon();
void CodeShennonCreate(codeShennon* symbolFrequency, int codePresent);