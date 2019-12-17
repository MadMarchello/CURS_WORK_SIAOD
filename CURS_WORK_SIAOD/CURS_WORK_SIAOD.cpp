#include "function.h"
#include <locale.h>
//1 - ошибка
//2 - не готова функция

using namespace std;
int main()
{
	/*найти настрйоку принимающую старую кодировку*/
	fstream file;
	const string databaseName = "D:\\testBase1.dat";
	const int size = 256;
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
		cout << "3. BinSearch\n\n";
		cout << "4. Exit\n";
		cout << "Answer: ";
		cin >> answer;
		switch (answer) {
		case 1: {
			system("CLS");
			PrintDatabase(recordArray);
			system("CLS");
			break;
		}
		case 2: {
			//	system("CLS");
			PrintDatabase(indexArray);
			//	system("CLS");
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
					insertion(indexArray[beginSearchRecord]->year);
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
			search(key_search);

			break;
		}
		case 4: {
			system("CLS");
			cout << "Coding in Shenon\n";
			double counter = 0;
			double summary = 0;
			unsigned char ch;
			int* freq = new int[size];

			for (int i = 0; i < size; i++) {
				freq[i] = 0;
			}
			FILE* file1 = fopen(databaseName, "rb");
			while (true) {
				ch = fgetc(file1);
				if (!feof(file1)) {
					freq[ch]++;
					counter++;
				}
				else {
					break;
				}
			}
			fclose(file1);
			break;
			codeShennon* symbolFreq = new codeShennon[size];
			symbolFreq = symbolFrequency(symbolFreq, size, counter, freq);
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