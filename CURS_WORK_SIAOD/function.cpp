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
	int surnameBeginRecord1 = 0;
	int surnameBeginRecord2 = 0;

	/*ПЕРВАЯ ЗАПИСЬ*/
	while (record1->title[surnameBeginRecord1] != ' ') {	//цикл обработки первого слова первой записи
		surnameBeginRecord1++;
	}
	surnameBeginRecord1++;
	while (record1->title[surnameBeginRecord1] != ' ') {	//цикл обработки второго слова первой записи 
		surnameBeginRecord1++;
	};
	surnameBeginRecord1++;

	/*ВТОРАЯ ЗАПИСЬ ЗАПИСЬ*/
	while (record2->title[surnameBeginRecord2] != ' ') {   // цикл обработки первого слова второй записи 
		surnameBeginRecord2++;
	}
	surnameBeginRecord2++;
	while (record2->title[surnameBeginRecord2] != ' ') { //цикл обрабоки второго слова второй записи
		surnameBeginRecord2++;
	}
	surnameBeginRecord2++;

	char* titleBuffSurnameRecord1;//буфер
	char* titleBuffSurnameRecord2;

	titleBuffSurnameRecord1 = new char[32];
	titleBuffSurnameRecord2 = new char[32];
	/*-------ЗАПОЛНЕНИЕ ПЕРВОГО БУФЕРА-------*/
	for (size_t i = 0; i < 32; i++) {
		titleBuffSurnameRecord1[i] = ' ';
	}
	for (size_t i = 0; i < 32 - surnameBeginRecord1; i++) {
		titleBuffSurnameRecord1[i] = record1->title[surnameBeginRecord1 + i];
	}
	/*-------ЗАПОЛНЕНИЕ ВТОРОГО БУФЕРА-------*/
	for (size_t i = 0; i < 32; i++) {
		titleBuffSurnameRecord2[i] = ' ';
	}
	for (size_t i = 0; i < 32 - surnameBeginRecord2; i++) {
		titleBuffSurnameRecord2[i] = record2->title[surnameBeginRecord2 + i];
		//std::cout << titleBuffSurnameRecord2[i] << "-";
	}
	//std::cout << "___";
	for (size_t i = 0; i < 32 - surnameBeginRecord2; i++) {
		//std::cout << record2->title[surnameBeginRecord2 + i] << "-";
	}

	if (strcmp(titleBuffSurnameRecord1, titleBuffSurnameRecord2) < 0) {//str1 < str2
		//std::cout << titleBuffSurnameRecord1 << "<" << titleBuffSurnameRecord2 << std::endl;
		delete[] titleBuffSurnameRecord1;
		delete[] titleBuffSurnameRecord2;
		return -1;
	}
	if (strcmp(titleBuffSurnameRecord1, titleBuffSurnameRecord2) == 0) {//str1 == str2
		//std::cout << titleBuffSurnameRecord1 << "==" << titleBuffSurnameRecord2 << std::endl;
		delete[] titleBuffSurnameRecord1;
		delete[] titleBuffSurnameRecord2;
		return 0;
	}
	if (strcmp(titleBuffSurnameRecord1, titleBuffSurnameRecord2) > 0) {//str1 > str2
		//std::cout << titleBuffSurnameRecord1 << "<" << titleBuffSurnameRecord2 << std::endl;
		delete[] titleBuffSurnameRecord1;
		delete[] titleBuffSurnameRecord2;
		return 1;
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
int BinCompare(char* key, char title[32]) {
	int SurnameBeginRecord1 = 0;
	int SurnameBeginRecord2 = 0;
	//Первая cлово 
	while (title[SurnameBeginRecord1] != ' ') {
		SurnameBeginRecord1++;
	}
	SurnameBeginRecord1++;
	//Второе слово
	while (title[SurnameBeginRecord1] != ' ') {
		SurnameBeginRecord1++;
	}
	SurnameBeginRecord1++;

	if (title[SurnameBeginRecord1] > key[0]) {
		return 1;
	}
	else if (title[SurnameBeginRecord1] < key[0]) {
		return -1;
	}
	else if (title[SurnameBeginRecord1 + 1] > key[1]) {
		return 1;
	}
	else if (title[SurnameBeginRecord1 + 1] < key[1]) {
		return -1;
	}
	else if (title[SurnameBeginRecord1 + 2] > key[2]) {
		return 1;
	}
	else if (title[SurnameBeginRecord1 + 2] < key[2]) {
		return -1;
	}
	else {
		return 0;
	}

}

int BinSearch(std::vector<record*> & index, char* key, int& left, int right) {
	int middle;
	while (left <= right) {
		middle = left + (right - left) / 2;

		if (BinCompare(key, index[middle]->title) == 0) {
		/*	for (int i = 0; i < exception.size(); i++) {
				if (exception[i] == middle) {
				}
				else {
					exception.push_back(i);//добавили элемент в исключение
					return middle;// вернули
				}
			}
			*/
			left = middle;
			return middle;
		}

		if (BinCompare(key, index[middle]->title) < 0) {
			left = middle + 1;//двигает левую часть вправо
		}
		else {
			right = middle - 1;//двигает правую часть влево
		}
	}
	return -1;// не найден
}