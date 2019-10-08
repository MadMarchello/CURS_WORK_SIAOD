#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;
//1 - ошибка
//2 - не готова функция
//по фамилиям замечательных людей, ключ поиска - первые три буквы фамилии
struct record {
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};
void openDatabase(string filename, fstream& file) {
	file.open(filename, ios::in | ios::binary);
	if (!file.is_open()) {
		throw runtime_error("File " + filename + " does not exist");
	}
}
void readDatabase(fstream& file, vector<record>& vector) {
	record input;
	file.read((char*)& input, sizeof(input));
	while (!file.eof()) {
		vector.push_back(input);
		file.read((char*)& input, sizeof(input));
	}
}

void QuickSort(vector<record*>& indexArray, int left, int right) {
/*	int i, j;
//	char* x;
	short int x;

	record* temp;

	i = left; j = right;
	x = indexArray[(left + right) / 2]->year;

	do {
		while ((indexArray[i]->year < x) && (i < right)) {
			i++;
		}
		while ((indexArray[j]->year > x) && (j > left)) {
			j--;
		}
		if (i <= j) {
			temp = indexArray[i];
			indexArray[i] = indexArray[j];
			indexArray[j] = temp;
		}
	} while (i <= j);

	if (left < j) {
		QuickSort(indexArray, left, j);
	}
	if (i < right) {
		QuickSort(indexArray, i, right);
	}*/
	/*int l = left;
	int r = right;

	int piv = indexArray[(l + r) / 2]->year;
	
	while (l <= r) {
		while(indexArray[l]->year)
	}*/
}
int Compare(record record1, record record2) {
	int SurnameBeginRecord1 = 0;
	int SurnameBeginRecord2 = 0;
	//
	while (record1.title[SurnameBeginRecord1] != ' ') {
		SurnameBeginRecord1++;
	}
	while (record1.title[SurnameBeginRecord1] != ' ') {
		SurnameBeginRecord1++;
	}
	//
	while (record2.title[SurnameBeginRecord2] != ' ') {
		SurnameBeginRecord2++;
	}
	while (record2.title[SurnameBeginRecord2] != ' ') {
		SurnameBeginRecord2++;
	}
	//
	if (record1.title[SurnameBeginRecord1] > record2.title[SurnameBeginRecord2]) {
		return 1;
	} 
	else if (record1.title[SurnameBeginRecord1] < record2.title[SurnameBeginRecord2]) {
		return -1;
	} 
	else if (record1.title[SurnameBeginRecord1 + 1] > record2.title[SurnameBeginRecord2]) {
		return 1;
	} 
	else if (record1.title[SurnameBeginRecord1 + 1] < record2.title[SurnameBeginRecord2]) {
		return -1;
	} 
	else if (record1.title[SurnameBeginRecord1 + 2] > record2.title[SurnameBeginRecord2]) {
		return 1;
	} 
	else if (record1.title[SurnameBeginRecord1 + 2] < record2.title[SurnameBeginRecord2]) {
		return -1;
	}
	else {
		return 0;
	}
}
void printDatabase(vector<record*>& index) {
	cout << " Out: \n1) One note\n2) Twenty notes\n";
	string inputStr;
	getline(cin, inputStr);
	int choice = stoi(inputStr);
	int counter = 1;
	for (int i = 0; i < index.size(); i++) {
		if (choice == 1) {
			while (_kbhit()) {
				if (!_getch()) {
					continue;
				}
				else if(_getch() == 32)  {
					continue;
				}
			}

		}
		else {
			if (counter < 20) {
				counter++;
				continue;
			}
			else {
				cout << "Continue? Y/N";
				getline(cin, inputStr);
				if ((inputStr == "y") || (inputStr == "Y")) {
					counter = 1;
					continue;
				}
				else {
					break;
				}
			}
		}
		cout << i + 1 << ". "
			<< index[i]->author
			<< index[i]->title
			<< index[i]->publisher
			<< index[i]->year
			<< index[i]->num_of_page
			<< endl;
	}
}
int main()
{
	fstream file;
	const string databaseName = "D:\\testBase1.dat";
	//getline(cin, databaseName);
	try {
		openDatabase(databaseName, file);
	}
	catch (exception e) {
		cout << e.what() << endl;
		exit(1);
	}
	vector<record> recordArray;
	readDatabase(file, recordArray);
	file.close();
	vector<record*> indexArray(recordArray.size());
	for (int i = 0; i < indexArray.size(); i++) {
		indexArray[i] = &recordArray[i];
	}
	printDatabase(indexArray);
	QuickSort(indexArray, 0, indexArray.size() - 1);
	printDatabase(indexArray);
	return 0;
}
