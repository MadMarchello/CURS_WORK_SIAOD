#include "function.h"
#include <locale.h>
//1 - ошибка
//2 - не готова функция

using namespace std;
int main()
{
	/*найти настрйоку принимающую старую кодировку*/
	fstream file;

	cout << "Welcome.\n";
	cout << "This is the course work of a 2 - year student Mark Belousov\n";
	cout << "on the subject of Structure and Data Processing Algorithms\n\n";
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
	QuickSortStruct(indexArray, 0, indexArray.size() - 1);
	int answer;

	while (true) {
		cout << "1. Not sorted database\n";
		cout << "2. Sorted QuickSort database\n";
		cout << "3. BinSearch\n";
		cout << "4. Shannon coding\n\n";
		cout << "5. Exit\n";
		cout << "Answer: ";
		cin >> answer;
		switch (answer) {
		case 1: {
			PrintDatabase(recordArray);
			break;
		}
		case 2: {
			PrintDatabase(indexArray);
			break;
		}
		case 3: {
			char* key = new char[3];
			cout << "Key search: ";
			cin >> key;

			int min = 0;
			int max = indexArray.size() - 1;
			int beginSearchRecord = bin_search(indexArray, key, min, max);//нахождение самого левого элемента
			int i = 0;
			int sizeQueue = 0;

			saod::queue QueueRecord;
			while ((BinCompare(key, indexArray[beginSearchRecord]->title) == 0)) {
				if (beginSearchRecord + 1 > indexArray.size() - 1) {
					break;
				}
				else if ((BinCompare(key, indexArray[beginSearchRecord + 1]->title) == 0)) {
					cout << i << " ";
					QueueRecord.add(indexArray[beginSearchRecord]);
					insertion(indexArray[beginSearchRecord]);
					beginSearchRecord++;
					i++;
				}
				else {
					break;
				}
			}
			cout << "BTREE: \n";
			traversal();
			int key_search;
			cout << "Input search key in BNode: ";
			cin >> key_search;
			cout << endl;
			saod::queue search_succ;
			search(key_search, search_succ);
			break;
		}
		case 4: {
			cout << "Coding in Shenon\n";
			Shennon();
			break;
		}
		case 5: {
			exit(0);
			break;
		}

		default: {
			cout << "\nNot declaraed you're answer\n"; exit(1);
		}
		}

		}

		return 0;
	}