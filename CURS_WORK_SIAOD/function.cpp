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
		std::cout << i  << ".| "
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
BtreeNode* createNode(int val, BtreeNode* child) {
	BtreeNode* newNode = new BtreeNode;
	newNode->val[1] = val;
	newNode->count = 1;
	newNode->link[0] = root;
	newNode->link[1] = child;
	return newNode;
}
/* Places the value in appropriate position */
void addValToNode(int val, int pos, BtreeNode* node, BtreeNode* child) {
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
void splitNode(int val, int* pval, int pos, BtreeNode* node, BtreeNode* child,
	BtreeNode** newNode) {
	int median, j;

	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

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
int setValueInNode(int val, int* pval, BtreeNode* node, BtreeNode** child) {
	int pos;
	if (!node) {
		*pval = val;
		*child = NULL;
		return 1;
	}

	if (val < node->val[1]) {
		pos = 0;
	}
	else {
		for (pos = node->count; (val < node->val[pos] && pos > 1); pos--)
			;
/*		if (val == node->val[pos]) {
			std::cout << "Duplicates not allowed\n";
			return 0;
		}*/
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
void insertion(int val) {
	int flag, i;
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

void traversal(BtreeNode* myNode) {
	int i;
	if (myNode) {
		for (i = 0; i < myNode->count; i++) {
			traversal(myNode->link[i]);
			std::cout << it << " " << myNode->val[i + 1] << " \n";
			it++;
		}
		traversal(myNode->link[i]);
	}
}

int search(BtreeNode* myNode, int data)
{
	if (myNode == NULL) {
		return -1;
	}
	if (data < myNode->val[0]) {
		return search(myNode->link[0], data);
	}
	else if(data < myNode->val[1]){
		return search(myNode->link[1], data);
	}
	else if (data > myNode->val[1]) {
		return search(myNode->link[2], data);
	}
	else {
		if (myNode->val[0] == data) {
			return myNode->val[0];
		}
		else if (myNode->val[1] == data) {
			return myNode->val[1];
		}
		else return -1;
	}
}

/*ЗАПОЛНЕНИЕ МАССИВА ВЕРОЯТНОСТЕЙ*/
codeShennon* symbolFrequency(codeShennon* symbolFreq, int size, int counter, int* freq) {
	double s = 0;
	for (int i = 0; i < size; i++) {
		symbolFreq[i].symbol = i;
		symbolFreq[i].frequency = (double)freq[i] / counter;
		std::cout << symbolFreq[i].frequency;
	}
	return symbolFreq;
}

























































































































void search(int data) {
	//return search(root, data);
	for (int i = 0; i < rand()%(34-7)+7; i++) {
		std::cout << data << std::endl;
	}
}













