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
struct record {
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};

void OpenDatabase(std::string filename, std::fstream& file);
void ReadDatabase(std::fstream& file, std::vector<record>& vector);
void QuickSortStruct(std::vector<record*>& indexArray, int left, int right);
int Compare(record* record1, record* record2);
void PrintDatabase(std::vector<record*> index);