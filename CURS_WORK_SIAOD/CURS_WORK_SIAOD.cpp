#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;
//1 - ошибка
//2 - не готова функция
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
void keyboardPlay(int choice) {
	/*char stop;
	while (true) {
		stop = getch();
		if (stop == 32) {
		}
	}*/
}
/*
void QuickSort(vector<record*>& indexArray, vector<record*>& recordArray) {
	int left = 0;
	int right = indexArray.size() - 1;
	int pivot;


}
*/
void printDatabase(vector<record*>& index) {
	cout << " Out: \n1) One note\n2) Twenty notes\n";
	string inputStr;
	getline(cin, inputStr);
	int choice = stoi(inputStr);
	int counter = 1;
	for (int i = 0; i < index.size(); i++) {
		cout << i + 1 << ". "
			<< index[i]->author
			<< index[i]->title
			<< index[i]->publisher
			<< index[i]->year
			<< index[i]->num_of_page
			<< endl;
		if (choice == 1) {
			//keyboardPlay();
			exit(2)
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
	}
}
int main()
{
	fstream file;
	string databaseName;
	getline(cin, databaseName);
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
	return 0;
}
