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
