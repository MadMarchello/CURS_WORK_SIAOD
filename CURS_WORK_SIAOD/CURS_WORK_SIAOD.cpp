#include "function.h"

//1 - ошибка
//2 - не готова функция
//по фамилиям замечательных людей, ключ поиска - первые три буквы фамилии
using namespace std;
int main()
{
	fstream file;
	const string databaseName = "D:\\testBase1.dat";
	cout <<
		"Welcome.\n";
	Sleep(1000);
	cout << "This is the course work of a 2 - year student Mark Belousov\n";
	Sleep(1000);
	cout << "on the subject of Structure and Data Processing Algorithms\n\n";
	Sleep(1000);
	//getline(cin, databaseName);
	try {
		OpenDatabase(databaseName, file);
	}
	catch (exception e) {
		cout << e.what() << endl;
		exit(1);
	}
	vector<record> recordArray;
	ReadDatabase(file, recordArray);
	file.close();
	vector<record*> indexArray(recordArray.size());
	for (int i = 0; i < indexArray.size(); i++) {
		indexArray[i] = &recordArray[i];
	}
	PrintDatabase(indexArray);
	QuickSortStruct(indexArray, 0, indexArray.size() - 1);
	PrintDatabase(indexArray);
	return 0;
}
