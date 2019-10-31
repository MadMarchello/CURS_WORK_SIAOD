#include "function.h"

void OpenDatabase(std::string filename, std::fstream& file) {
	file.open(filename, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		throw std::runtime_error("File " + filename + " does not exist");
	}
}
void ReadDatabase(std::fstream & file, std::vector<record> & vector) {
	record input;
	file.read((char*)& input, sizeof(input));
	while (!file.eof()) {
		vector.push_back(input);
		file.read((char*)& input, sizeof(input));
	}
}

void QuickSortStruct(std::vector<record*> & indexArray, int left, int right)
{
	register int i, j;
	record* x;
	record* temp;

	i = left; j = right;
	x = indexArray[(left + right) / 2];
	do {
		while ((Compare(indexArray[i], x) < 0) && (i < right)) i++;
		while ((Compare(indexArray[j], x) > 0) && (j > left)) j--;
		if (i <= j) {
			temp = indexArray[i];
			indexArray[i] = indexArray[j];
			indexArray[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) QuickSortStruct(indexArray, left, j);
	if (i < right) QuickSortStruct(indexArray, i, right);
}
int Compare(record * record1, record * record2) {
	int SurnameBeginRecord1 = 0;
	int SurnameBeginRecord2 = 0;
	//цикл обработки первого слова
	while (record1->title[SurnameBeginRecord1] != ' ') {
		SurnameBeginRecord1++;
	}
	SurnameBeginRecord1++;
	while (record1->title[SurnameBeginRecord1] != ' ') {
		SurnameBeginRecord1++;
	}
	//цикл обработки второго слова
	SurnameBeginRecord1++;
	while (record2->title[SurnameBeginRecord2] != ' ') {
		SurnameBeginRecord2++;
	}
	SurnameBeginRecord2++;
	while (record2->title[SurnameBeginRecord2] != ' ') {
		SurnameBeginRecord2++;
	}
	SurnameBeginRecord2++;
	//сравнивание первой буквы
	for (size_t i = 0; i < 32; i++) {
		if (record1->title[SurnameBeginRecord1 + i] > record2->title[SurnameBeginRecord2 + i]) {
			return 1;
		}
		else if (record1->title[SurnameBeginRecord1 + i] < record2->title[SurnameBeginRecord2] + i) {
			return -1;
		}
	}
	/*//сравнивание второй буквы
	if (record1->title[SurnameBeginRecord1 + 1] > record2->title[SurnameBeginRecord2 + 1]) {
		return 1;
	}
	else if (record1->title[SurnameBeginRecord1 + 1] < record2->title[SurnameBeginRecord2 + 1]) {
		return -1;
	}
	//сравнивание третьей буквы
	else if (record1->title[SurnameBeginRecord1 + 2] > record2->title[SurnameBeginRecord2 + 2]) {
		return 1;
	}
	else if (record1->title[SurnameBeginRecord1 + 2] < record2->title[SurnameBeginRecord2 + 2]) {
		return -1;
	}*/
	else {
		return 0;
	}
}
void PrintDatabase(std::vector<record*> index) {

	std::cout << "Please, entry type output: \n1) One note\n2) Twenty notes\n";
	std::string inputStr;
	std::getline(std::cin, inputStr);
	int choice = stoi(inputStr);
	int counter = 1;
	for (int i = 0; i < index.size(); i++) {
		std::cout << i + 1 << ".| "
			<< index[i]->author << "  |  "
			<< index[i]->title << "  |  "
			<< index[i]->publisher << "  |  "
			<< index[i]->year << "  |  "
			<< index[i]->num_of_page << "  |  "
			<< std::endl;
		if (choice == 1) {
			while (_kbhit()) {
				if (!_getch()) {
					continue;
				}
				else if (_getch() == 32) {
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
				std::cout << "Continue? Y/N: ";
				std::getline(std::cin, inputStr);
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