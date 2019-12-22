#include "function.h"
//ФУНКЦИЯ ЗАПОЛНЕНИЯ ИНФОРМАЦИОННЫХ ПОЛЕЙ СТРУКТУРЫ NODE И ДОБАВЛЕНИЯ ЭТОЙ СТРУКТУРЫ В СПИСОК
BtreeNode* root;

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
	int sizeTitle = 0;
	int surnameSize1 = 0;
	int surnameSize2 = 0;

	/*ПЕРВАЯ ЗАПИСЬ*/
	while (record1->title[surnameBeginRecord1] != ' ') {	//цикл обработки первого слова первой записи
		surnameBeginRecord1++;
	}
	surnameBeginRecord1++;//пробел 1 и 2
	while (record1->title[surnameBeginRecord1] != ' ') {	//цикл обработки второго слова первой записи 
		surnameBeginRecord1++;
	};
	surnameBeginRecord1++;//пробел 2 и 3
	sizeTitle = surnameBeginRecord1;
	while (record1->title[sizeTitle] != ' ') {	//цикл обработки третьего слова первой записи 
		surnameSize1++;
		sizeTitle++;
	};
	/*ВТОРАЯ ЗАПИСЬ ЗАПИСЬ*/
	while (record2->title[surnameBeginRecord2] != ' ') {   // цикл обработки первого слова второй записи 
		surnameBeginRecord2++;
	}
	surnameBeginRecord2++;
	while (record2->title[surnameBeginRecord2] != ' ') { //цикл обрабоки второго слова второй записи
		surnameBeginRecord2++;
	}
	surnameBeginRecord2++;
	sizeTitle = surnameBeginRecord2;
	while (record2->title[sizeTitle] != ' ') {	//цикл обработки третьего слова второй записи 
		surnameSize2++;
		sizeTitle++;
	}

	char* titleBuffSurnameRecord1 = new char[32];//буфер
	char* titleBuffSurnameRecord2 = new char[32];

	/*-------ЗАПОЛНЕНИЕ ПЕРВОГО БУФЕРА-------*/
	for (size_t i = 0; i < 32; i++) {
		titleBuffSurnameRecord1[i] = ' ';
	}
	for (size_t i = 0; i < 32; i++) {
		titleBuffSurnameRecord1[i] = record1->title[surnameBeginRecord1 + i];
	}
	/*-------ЗАПОЛНЕНИЕ ВТОРОГО БУФЕРА-------*/
	for (size_t i = 0; i < 32; i++) {
		titleBuffSurnameRecord2[i] = ' ';
	}
	for (size_t i = 0; i < 32; i++) {
		titleBuffSurnameRecord2[i] = record2->title[surnameBeginRecord2 + i];
	}
	if (strcmp(titleBuffSurnameRecord1, titleBuffSurnameRecord2) < 0) {
		delete[] titleBuffSurnameRecord1;
		delete[] titleBuffSurnameRecord2;
		return -1;
	}
	if (strcmp(titleBuffSurnameRecord1, titleBuffSurnameRecord2) == 0) {
		delete[] titleBuffSurnameRecord1;
		delete[] titleBuffSurnameRecord2;
		return 0;
	}
	if (strcmp(titleBuffSurnameRecord1, titleBuffSurnameRecord2) > 0) {
		delete[] titleBuffSurnameRecord1;
		delete[] titleBuffSurnameRecord2;
		return 1;
	}
}

void PrintDatabase(std::vector<record> record) {
	std::cout << "Please, entry type output: \n1) One note\n2) Twenty notes\n";
	std::string inputStr;
	int choice;
	std::cin >> choice;
	int counter = 1;
	for (int i = 0; i < record.size(); i++) {
		std::cout << i << ".| "
			<< record[i].author << "  |  "
			<< record[i].title << "  |  "
			<< record[i].publisher << "  |  "
			<< record[i].year << "  |  "
			<< record[i].num_of_page << "  |  "
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

void PrintDatabase(std::vector<record*> index) {
	std::cout << "Please, entry type output: \n1) One note\n2) Twenty notes\n";
	std::string inputStr;
	int choice;
	std::cin >> choice;
	int counter = 1;
	for (int i = 0; i < index.size(); i++) {
		std::cout << i << ".| "
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

int BinCompare(char* key, char* title) {
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
		//std::cout << "1 ";
		return 1;
	}
	else if (title[SurnameBeginRecord1] < key[0]) {
		//std::cout << "-1 ";
		return -1;
	}
	else if (title[SurnameBeginRecord1 + 1] > key[1]) {
		//std::cout << "1 ";
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

int bin_search(std::vector<record*> ind, char* key, int min, int max) {
	int mid = (min + max) / 2;
	if (min < max) {
		if (BinCompare(key, ind[mid]->title) >= 0) {
			return bin_search(ind, key, min, mid);
		}
		else {
			return bin_search(ind, key, mid + 1, max);
		}
	}
	else {
		min++;
		return mid;
	}
}

void saod::queue::remove()
{
	if (isEmpty())
	{
		std::cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Removing " << arr[front] << '\n';

	front = (front + 1) % capacity;
	count--;
}

void saod::queue::add(record * item)
{
	if (isFull())
	{
		std::cout << "OverFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Inserting " << item->author << "|"
		<< item->title << "|"
		<< item->publisher << "|"
		<< item->year << "|"
		<< item->num_of_page << "|" << std::endl;

	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
}

record * saod::queue::peek()
{
	if (isEmpty())
	{
		std::cout << "UnderFlow\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}
	return arr[front];
}

int saod::queue::size()
{
	return count;
}

bool saod::queue::isEmpty()
{
	return (size() == 0);

}

bool saod::queue::isFull()
{
	return (size() == capacity);
}

/* creating new node */
BtreeNode* createNode(record* val, BtreeNode * child) {
	BtreeNode* newNode = new BtreeNode;
	newNode->val[1] = val;
	newNode->count = 1;
	newNode->link[0] = root;
	newNode->link[1] = child;
	return newNode;
}
/* Places the value in appropriate position */
void addValToNode(record* val, int pos, BtreeNode * node, BtreeNode * child) {
	int j = node->count;
	while (j > pos) {
		node->val[j + 1] = node->val[j];
		node->link[j + 1] = node->link[j];
		j--;
	}
	node->val[j + 1] = val;
	node->link[j + 1] = child;
	node->count++;
}
/* split the node */
void splitNode(record* val, record** pval, int pos, BtreeNode * node, BtreeNode * child,
	BtreeNode * *newNode) {
	int median, j;

	if (pos > MIN) {
		median = MIN + 1;
	}
	else {
		median = MIN;
	}

	*newNode = new BtreeNode;
	j = median + 1;
	while (j <= MAX) {
		(*newNode)->val[j - median] = node->val[j];
		(*newNode)->link[j - median] = node->link[j];
		j++;
	}
	node->count = median;
	(*newNode)->count = MAX - median;

	if (pos <= MIN) {
		addValToNode(val, pos, node, child);
	}
	else {
		addValToNode(val, pos - median, *newNode, child);
	}
	*pval = node->val[node->count];
	(*newNode)->link[0] = node->link[node->count];
	node->count--;
}
/* sets the value val in the node */
int setValueInNode(record* val, record** pval, BtreeNode * node, BtreeNode * *child) {
	int pos;
	if (!node) {
		*pval = val;
		*child = NULL;
		return 1;
	}

	if (val->year < node->val[1]->year) {
		pos = 0;
	}
	else {
		for (pos = node->count; (val->year < node->val[pos]->year && pos > 1); pos--)
			;
	}
	if (setValueInNode(val, pval, node->link[pos], child)) {
		if (node->count < MAX) {
			addValToNode(*pval, pos, node, *child);
		}
		else {
			splitNode(*pval, pval, pos, node, *child, child);
			return 1;
		}
	}
	return 0;
}
/* insert val in B-Tree */
void insertion(record* val) {
	int flag;
	record* i;
	BtreeNode* child;

	flag = setValueInNode(val, &i, root, &child);
	if (flag)
		root = createNode(i, child);
}
void traversal() {
	traversal(root);
}
/* B-Tree Traversal */
int it = 0;

void traversal(BtreeNode * myNode) {
	int i;
	if (myNode) {
		for (i = 0; i < myNode->count; i++) {
			traversal(myNode->link[i]);
			std::cout << it << " " << myNode->val[i + 1]->year << " \n";
			it++;
		}
		traversal(myNode->link[i]);
	}
}
void search(int data, saod::queue q) {
	search(root, data, q);
}
void search(BtreeNode* myNode, int data, saod::queue q)
{
	int i;
	if (myNode) {
		for (i = 0; i < myNode->count; i++) {
			search(myNode->link[i], data, q);
			if (data == myNode->val[i + 1]->year) {
				q.add(myNode->val[i + 1]);
			}
			it++;
		}
		search(myNode->link[i], data, q);
	}
}

void Shennon() {
	FILE* file = fopen("D:\\testBase1.dat", "rb");

	codeShennon* symbolProbality = new codeShennon[size_code];
	
	int* repeat = new int[size_code];//массив всех повторений каких либо сиволов

	for (int i = 0; i < size_code; i++) {
		repeat[i] = 0;
	}

	int countPresent = 0;//количетсво символов в базе
	int count = 0;//общее количество символов в базе

	unsigned char ch;//считываемый символ

	while (!feof(file)) {
		ch = getc(file);
		
		if (ch != -1) { 
			repeat[(int)ch]++; // Сколько повторов символа в БД
		} 
		if (repeat[(int)ch] == 1) {
			countPresent++;  // Количество символов без повторов                
		}
	}

	fclose(file);
	
	for (int i = 0; i < size_code; i++) {
		count += repeat[i];
	}
	//std::cout << std::endl << repeat[i] << std::endl;
	for (int i = 0, j = 0; i < size_code; i++) {
		if (repeat[i] != 0) {
			symbolProbality[j].symbol = i;
			symbolProbality[j].probality = (double)repeat[i] / (double)count;
			j++;
		}
	}

	double entr = 0;//энтропия
	for (int i = 0; i < size_code; i++) {
		entr += symbolProbality[i].probality * log2(symbolProbality[i].probality);
		std::cout << symbolProbality[i].probality << " " << i << '\n';
	}
	entr = -entr;
	std::cout << "Entropy: " << entr << std::endl;
	QuickSortStruct(symbolProbality, 0, size_code);
	std::cout << std::endl;
	CodeShennonCreate(symbolProbality, countPresent);
}
void CodeShennonCreate(codeShennon* symbolProbality, int codePresent) {
	double *SumProbality = new double[codePresent];//Нарастающие суммы вероятностей
	double MidLenght = 0;

	int* Lenght = new int[codePresent];//длина кодовых слов

	int** CodeMatrix = new int* [codePresent];//Матрица кодов
	for (int i = 1; i <= codePresent; i++) {
		CodeMatrix[i] = new int[codePresent];
	}

	for (int i = 1; i <= codePresent; i++) {
		for (int j = 1; j <= codePresent; j++) {
			CodeMatrix[i][j] = 0;
		}
	}

	double* BuffProbality = new double[codePresent];//Хранение массива вероятностей

	for (int i = 1; i <= codePresent; i++) {
		BuffProbality[i] = symbolProbality[i - 1].probality;
	}

	SumProbality[0] = 0; BuffProbality[0] = 0;
	for (int i = 1; i <= codePresent; i++) {
		SumProbality[i] = SumProbality[i - 1] + BuffProbality[i];
		Lenght[i] = -log2(BuffProbality[i]);
	}
	for (int i = 1; i <= codePresent; i++) {
		for (int j = 1; j <= Lenght[i]; j++) {
			SumProbality[i - 1] *= 2;
			CodeMatrix[i][j] = floor(SumProbality[i - 1]);
			while (SumProbality[i - 1] > 1) {
				SumProbality[i - 1] -= 1;
			}
		}
	}

	std::cout << std::setw(8) << std::left << "SYMBOL"
		<< std::setw(14) << "PROBALITY"
		<< std::setw(8) << "LENGHT"
		<< std::setw(10) << "CODEWORD"
		<< std::endl;

	for (int i = 1; i <= codePresent; i++) {
		std::cout << std::setw(8) << (int)symbolProbality[i - 1].symbol <<
		std::setw(14) << BuffProbality[i] << std::setw(8) << Lenght[i];
		for (int j = 1; j <= Lenght[i]; j++) {
			std::cout << CodeMatrix[i][j];
		}
		std::cout << std::endl;
		MidLenght += Lenght[i] * BuffProbality[i];
	}
	std::cout << "\nMid Lenght = " << MidLenght << std::endl;
}
void QuickSortStruct(codeShennon * symbolProbality, int left, int right)
{
	register int i, j;
	double x;
	codeShennon temp;

	i = left; j = right;
	x = symbolProbality[(left + right) / 2].probality;
	do {
		while ((symbolProbality[i].probality > x) && (i < right)) i++;
		while ((symbolProbality[j].probality < x) && (j > left)) j--;
		if (i <= j) {
			temp = symbolProbality[i];
			symbolProbality[i] = symbolProbality[j];
			symbolProbality[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) QuickSortStruct(symbolProbality, left, j);
	if (i < right) QuickSortStruct(symbolProbality, i, right);
}