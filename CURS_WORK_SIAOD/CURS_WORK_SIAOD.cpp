#include "function.h"
#include <locale.h>
//1 - ошибка
//2 - не готова функция
//по фамилиям замечательных людей, ключ поиска - первые три буквы фамилии
using namespace std;
int main()
{
	/*найти настрйоку принимающую старую кодировку*/

	//setlocale(LC_ALL, "rus");
	fstream file;
	const string databaseName = "D:\\testBase1.dat";
	//cout << "Добро пожаловать.\n";
	cout << "Welcome.\n";
	Sleep(1000);
	cout << "This is the course work of a 2 - year student Mark Belousov\n";
	//cout << "Это курсовая работа студента 2 курса Белоусова Марка\n";
	Sleep(1000);
	cout << "on the subject of Structure and Data Processing Algorithms\n\n";
	//cout << "по предмету Струкутуры и Алгоритмы Обработки Данных\n";
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
	//PrintDatabase(indexArray);
	QuickSortStruct(indexArray, 0, indexArray.size() - 1);
	PrintDatabase(indexArray);

	std::string answer;
	cin >> answer;
	cout << answer;
	return 0;
}
