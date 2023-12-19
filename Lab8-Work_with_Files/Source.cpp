#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include "list"
#include "map"
#include "iomanip";
#include "chrono"

using namespace std;

void MenuOfSolution(int*);
// Task A
int CheckIntValue(int*);
int CheckMinMembersOfCatalog(int*);
int GetRandomNumber(int);
void GenarateIntFile();
void GetDetailInfo(int*, int*);
int ReplaceFifthElements(int*);
// Task B
bool CheckIsTwoWord(string&);
string isDelimeter(string&, bool&);
void isWordwithTab(string&, istringstream&, bool&);
int RemoveFromFile();
// Task C
int SelectNotDialogue();
// Task D
void FillLib(list<string>&, map <string, list<string>>&, string&);
void CreateCatalogGoods(map <string, list<string>>&);
int GenerateDataFile(int*);
int FindMiddleValueMonitors(int*);

bool do_once = false;

/**
 * @brief Перевіряє коректне значення типу int, яке ввів користувач до системи
 * @param i Значення типу int введене з клавіатури
 * @return Повертає коректне значення для подальшої роботи системи
*/
int CheckIntValue(int* i) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cout << "You enter wrong data! Please enter correct data: \n";
			cin >> *i;
			cin.ignore(666, '\n');
		}
		else {
			return *i;
		}
	}
}

/**
 * @brief Перевіряє мінімальну кількість замовлень
 * @param n Кількість замовлень введена користувачем з клавіатури
 * @return Повертає коректне значення кількості елементів замовлень
*/
int CheckMinMembersOfCatalog(int* n) {

	if (*n <= 0) {
		cout << "You enter wrong data! Please enter correct data (min members - 1): \n";
		cin >> *n;
		*n = CheckIntValue(n);
	}
	return *n;
}

/**
 * @brief Шукає рандомне число
 * @param n Діапазон чисел від 0 до n-1
 * @return Повертає рандомне число
*/
int GetRandomNumber(int n) {
	int random;

	random = rand() % n;

	return random;
}

/**
 * @brief Генерує бінарний та текстовий файл, який містить цілі числа
*/
void GenarateIntFile() {
	int x;

	ofstream fout("Int.bin", ios::binary | ios::out);
	ofstream fout_txt("Int.txt", ios::out);
	for (int i = 0; i < GetRandomNumber(100) + 10; i++) {
		x = GetRandomNumber(10);
		fout.write((char*)&x, sizeof(int));
		fout_txt << x;
	}
	if (fout.fail() || fout_txt.fail()) {
		cerr << "File write operation failed" << endl;
	}
	fout.close();
	fout_txt.close();
}

/**
 * @brief Відображає дані, які містяться в масиві типу int
 * @param mas Масив типу int
 * @param n Кількість елементів масиву
*/
void GetDetailInfo(int* mas, int* n) {

	for (int i = 0; i < *n; i++) {
		cout << mas[i] << " | ";
	}cout << endl;
}

/**
 * @brief Замінює кожен 5 елемент на значення, яке ввів користувач
 * @param n Значення типу int, яке ввів користувач
 * @return При правильному виконанні 0, а при помилці 1
*/
int ReplaceFifthElements(int* n) {

	ifstream fin("Int.bin", ios::binary | ios::in); 
	if (!fin) {
		cerr << "Error! This file name wasn't found" << endl;
		return 1;
	}

	fin.seekg(0, ios::end);
	streampos find_length = fin.tellg();
	fin.seekg(0, ios::beg);
	int size_file = find_length / sizeof(int);
	int* buffer = new int[size_file];

	fin.read((char*)buffer, find_length);
	GetDetailInfo(buffer, &size_file);	

	for (int i = 0; i < size_file; i++) {
		if ((i + 1) % 5 == 0) {
			buffer[i] = *n;
		}
		cout << buffer[i] << " | ";
	}cout << endl;
	fin.close();

	ofstream fout("Int.bin", ios::binary | ios::out);		
	fout.write((char*)buffer, size_file* sizeof(int));
	if (fout.fail()) {
		cerr << "File write operation failed" << endl;
	}	
	fout.close();

	delete[] buffer;
	return 0;
}

/**
 * @brief Перевіряє, чи слово складається з двух літер
 * @param word Слово для перевірки
 * @return true, якщо слово складається з двух літер; інакше false
*/
bool CheckIsTwoWord(string& word) {
	
	if (word.length() == 2) return true;
	return false;
}

/**
 * @brief Перевіряє, чи слово має розділові знаки
 * @param word Слово для перевірки
 * @param have_delimeter Чи слово має розділовий знак
 * @return Розділовий знак
*/
string isDelimeter(string& word, bool& have_delimeter) {

	istringstream isi(word);
	string only_word;
	string del = " ";
	
	if (word.find('.') != string::npos) {
		getline(isi, only_word, '.');
		if (CheckIsTwoWord(only_word)) have_delimeter = true;
		getline(isi, del);
		del = "." + del;
		return del;
	}
	else if (word.find(',') != string::npos) {
		getline(isi, only_word, ',');
		if (CheckIsTwoWord(only_word)) have_delimeter = true;
		getline(isi, del);
		del = "," + del;
		return del;
	}
	else if (word.find('!') != string::npos) {
		getline(isi, only_word, '!');
		if (CheckIsTwoWord(only_word)) have_delimeter = true;
		getline(isi, del);
		del = "!" + del;
		return del;
	}
	else if (word.find('?') != string::npos) {
		getline(isi, only_word, '?');
		if (CheckIsTwoWord(only_word)) have_delimeter = true;
		getline(isi, del);
		del = "?" + del;
		return del;
	}

	return del;
}

/**
 * @brief Перевіряє чи наступний символ в потоці вводу є табуляція
 * @param word Слово для перевірки
 * @param isi Потік вводу, який читає дані з рядка
 * @param have_tab Чи слово має табуляцію
*/
void isWordwithTab(string& word, istringstream& isi, bool& have_tab) {

	char next_symbol;
	string next_half;

	if (isi.get(next_symbol) && next_symbol == '\t') {
		isi >> word;
		have_tab = true;
		isWordwithTab(word, isi, have_tab);
	}
}

/**
 * @brief Вилучає з даного файлу всі слова, які складаються з двох літер та знаків табуляції
 * @return При правильному виконанні 0, а при помилці 1
*/
int RemoveFromFile() {

	ifstream fin("Task B.txt", ios::in);
	string txt;
	string line;

	if (!fin) {
		cerr << "Error! This file name wasn't found" << endl;
		return 1;
	}
	cout << "\nOriginal Text:" << endl;
	while (getline(fin, line)) {
		istringstream is(line);
		string word;
		string update_line;
		cout << line << endl;
		while (is >> word) {
			bool have_delimeter = false;
			bool have_tab = false;
			isWordwithTab(word, is, have_tab);
			string del = isDelimeter(word, have_delimeter);
			if (!CheckIsTwoWord(word)) {
				if (del != " " && (have_delimeter || have_tab)) {
					update_line.pop_back();
					update_line += del + " ";
					continue;
				}
				if (have_tab) continue;
				update_line += word + " ";
			}
		}
		if (!update_line.empty()) {
			txt += update_line + "\n";
		}		
	}
	cout << "\nRedacted Text:\n";
	cout << txt << endl;
	fin.close();

	ofstream fout("Task B(Redacted).txt", ios::out);
	fout << txt;
	if (fout.fail()) {
		cerr << "File write operation failed" << endl;
	}
	fout.close();

	return 0;
}

/**
 * @brief Структура, яка містить в собі дані про монітори
*/
struct Monitor {
	string name_company;
	string model;
	int diagonal;
	string matrix_type;
	int brightness;
	float cost;

	void ShowInfo() {
		cout << setw(10) << name_company << " | " << setw(15) << model << " | " << setw(6) << diagonal << " inches | " << setw(6) << matrix_type << " | " << setw(6) << brightness << " nt" << " | " << setw(6) << cost << "$" << endl;
	}
};

/**
 * @brief Створю бінарний файл, який містить інформацію про монітори
 * @param n Кількість елементів 
 * @return 0 при правильному виконанні, 1 - при помилці
*/
int GenerateDataFile(int* n) {
	Monitor* inform_monitor = new Monitor[*n];
	map<string, list<string>> catalog;
	list<string> matrix = { "IPS", "TN", "PLS" };

	CreateCatalogGoods(catalog);

	for (int i = 0; i < *n; i++) {
		map<string, list<string>>::iterator it = next(catalog.begin(), GetRandomNumber(6));
		(inform_monitor + i)->name_company = it->first;
		list<string>::iterator its = next(it->second.begin(), GetRandomNumber(it->second.size()));
		(inform_monitor + i)->model = *its;
		(inform_monitor + i)->diagonal = GetRandomNumber(40) + 1;
		(inform_monitor + i)->cost = (float)(GetRandomNumber(2000) + 100) + (float)(GetRandomNumber(100) / 100) + (float)(GetRandomNumber(10) / 100);
		(inform_monitor + i)->brightness = GetRandomNumber(1000) + 400;
		list<string>::iterator iti = next(matrix.begin(), GetRandomNumber(matrix.size()));
		(inform_monitor + i)->matrix_type = *iti;
		//(inform_monitor + i)->ShowInfo();
	}
	
	auto start_bin = chrono::high_resolution_clock::now();
	ofstream fout("Monitors_data.bin", ios::out | ios::binary);
	for (int i = 0; i < *n; i++){
		fout.write((char*)&(inform_monitor[i]), sizeof(Monitor));
	}
	if (fout.fail()) {
		cerr << "File write operation failed" << endl;
		delete[] inform_monitor;
		return 1;
	}
	else cout << "Save Generate Data -> successfully" << endl;
	fout.close();
	auto fin_bin = chrono::high_resolution_clock::now();
	auto dir_bin = chrono::duration_cast<chrono::milliseconds>(fin_bin - start_bin);

	auto start_txt = chrono::high_resolution_clock::now();
	ofstream fout_txt("Monitors_data.txt", ios::out);
	for (int i = 0; i < *n; i++) {
		fout_txt << (inform_monitor + i)->name_company;
		fout_txt << (inform_monitor + i)->model;
		fout_txt << (inform_monitor + i)->diagonal;
		fout_txt << (inform_monitor + i)->matrix_type;
		fout_txt << (inform_monitor + i)->brightness;
		fout_txt << (inform_monitor + i)->cost;
		fout_txt << endl;
	}
	if (fout_txt.fail()) {
		cerr << "File write operation failed" << endl;
		delete[] inform_monitor;
		return 1;
	}
	fout_txt.close();
	auto fin_txt = chrono::high_resolution_clock::now();
	auto dir_txt = chrono::duration_cast<chrono::milliseconds>(fin_txt - start_txt);

	cout << "Bin file takes: " << (float)dir_bin.count() / 1000 << "s to write data\n";
	cout << "Txt file takes: " << (float)dir_txt.count() / 1000 << "s to write data\n";

	delete[] inform_monitor;
	return 0;
}

/**
 * @brief Визначає з бінарного файлу середню вартість моніторів з діагоналлю не більше 27 дюймів
 * @param n Кількість елементів
 * @return 0 при правильному виконанні, 1 - при помилці
*/
int FindMiddleValueMonitors(int* n) {
	int amount = 0;
	int count = 0;
	
	Monitor* buffer = new Monitor[*n];
	ifstream fin("Monitors_data.bin", ios::in | ios::binary);
	if (!fin) {
		cerr << "Error! This file name wasn't found" << endl;
		delete[] buffer;
		return 1;
	} cout << "File is reading..." << endl;
	fin.seekg(0, ios::end);
	size_t file_size = fin.tellg();
	fin.seekg(0, ios::beg);
	if (file_size != sizeof(Monitor) * *n) {
		cerr << "Error! File isn't consist of current struct\n";
	}
	else {
		fin.read((char*)buffer, sizeof(Monitor) * *n);
		for (int i = 0; i < *n; i++) {
			(buffer + i)->ShowInfo();
			if ((buffer + i)->diagonal <= 27) {
				amount += (buffer + i)->cost;
				count++;
			}
		}
	}	
	fin.close();

	if (count > 0) {
		cout << "The middle value of monitors with no more than 27 inches: " << amount / count << "$" << endl;
	}
	else cout << "Dont't found monitors with no more than 27 inches\n";
	
	//delete[] buffer; //Why error!!??
	return 0;
}

/**
 * @brief Виділяє з заданого текстового файлу речення, які не є репліками в діалозі
 * @return 0 при правильному виконанні, 1 - при помилці
*/
int SelectNotDialogue() {

	ifstream fin("Task C.txt", ios::in);
	if (!fin) {
		cerr << "Error! This file name wasn't found" << endl;
		return 1;
	}
	string line;
	string only_text;
	string only_dialogue;
	while (getline(fin, line)) {
		istringstream isi(line);
		string word;		
		while (isi >> word) {
			if (word.find('"') != string::npos) {
				string dialogue;
				dialogue += word + " ";
				if (word[word.size() - 1] != '"') {
					getline(isi, word, '"');
					dialogue += word + '"' + " ";
				}
				if (dialogue[dialogue.size() - 3] == '.' || dialogue[dialogue.size() - 3] == ',' || dialogue[dialogue.size() - 3] == '!' || dialogue[dialogue.size() - 3] == '?') {
					dialogue.pop_back();
					only_dialogue += dialogue + '\n';
				}
				else only_text += dialogue;
			}
			else {
				only_text += word + " ";
			}
		}
		only_text += '\n';
	}
	cout << "\n-----------Only dialogues---------------" << endl;
	cout << only_dialogue << endl;
	cout << "\n----------Without dialogues-------------" << endl;
	cout << only_text << endl;
	
	return 0;
}

/**
 * @brief Інтерфейс який дає змогу користувачу працювати з додатком
 * @param q Вибір виконуваного завдання, яке задається користувачем з клавіатури
*/
void MenuOfSolution(int* q) {
	int n;
	
	srand(time(0));
	switch (*q) {
	case 1:
		cout << "\n__Task A__\n";
		cout << "Enter an element to replace the fifth elements: ";
		cin >> n;
		n = CheckIntValue(&n);
		if (!do_once) {
			GenarateIntFile();
			do_once = true;
		}
		ReplaceFifthElements(&n);
		break;
	case 2:
		cout << "\n__Task B__\n";
		RemoveFromFile();
		break;
	case 3:
		cout << "\n__Task C__\n";
		SelectNotDialogue();
		break;
	case 4:
		cout << "\n__Task D__\n";
		cout << "Enter amount of monitors: ";
		cin >> n;
		n = CheckIntValue(&n);
		n = CheckMinMembersOfCatalog(&n);
		GenerateDataFile(&n);
		FindMiddleValueMonitors(&n);
		break;
	default:
		cout << "\n__You don't enter any task for execution__\n";
		break;
	}
	if (*q == 1 || *q == 4) {
		MenuOfSolution(q);
	}
}

int main() {
	int q;

	cout << "--------Select task:--------\n";
	cout << "Task A) Replace Fifth Elements - Enter 1\n";
	cout << "Task B) Remove From File 2 Length Words and Tab Marks - Enter 2\n";
	cout << "Task C) Select the Sentences That are not lines of dialoque - Enter 3\n";
	cout << "Task D) Determine the Average Cost of 27-inches Monitors - Enter 4\n";
	cout << "------------------------------------------------------------\n";
	cin >> q;
	q = CheckIntValue(&q);
	MenuOfSolution(&q);

	return main();
}

/**
 * @brief Створює колекцію за виробником
 * @param current_list Поточний список назв модельного ряду
 * @param current_lib Поточний каталог товарів
 * @param autor Поточний виробник
*/
void FillLib(list<string>& current_list, map <string, list<string>>& current_lib, string& autor) {

	for (int i = 0; i < current_list.size(); i++) {
		list<string>::iterator it = next(current_list.begin(), i);
		current_lib[autor].push_back(*it);
	}
}

/**
 * @brief Заповнює каталог товарів
 * @param catalog Поточний каталог
*/
void CreateCatalogGoods(map <string, list<string>>& catalog) {
	string sumsung = "Samsung";
	string dell = "Dell";
	string asus = "Asus";
	string acer = "Acer";
	string hp = "HP";
	string benq = "BenQ";
	list<string> sumsung_models{ "Odyssey G7", "Curved", "Professional", "Odyssey Neo", "ViewFinity S9"};
	list<string> dell_models{ "Alienware", "UltraSharp", "U27722D" };
	list<string> asus_models{ "TUF Gaming", "ProArt Display", "ZenScreen Ink", "ROG Strix", "ROG Swift"};
	list<string> acer_models{ "Vero", "Predator", "Nitro" };
	list<string> hp_models{ "Omen", "P22 G4", "EliteDisplay" };
	list<string> benq_models{ "MOBIUZ", "Zowie", "PD", "GW" };

	FillLib(sumsung_models, catalog, sumsung);
	FillLib(dell_models, catalog, dell);
	FillLib(asus_models, catalog, asus);
	FillLib(acer_models, catalog, acer);
	FillLib(hp_models, catalog, hp);
	FillLib(benq_models, catalog, benq);
}