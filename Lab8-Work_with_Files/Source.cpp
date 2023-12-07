#include "iostream"

using namespace std;

/**
 * @brief Інтерфейс який дає змогу користувачу працювати з додатком
 * @param q Вибір виконуваного завдання, яке задається користувачем з клавіатури
*/
void MenuOfSolution(int* q) {
	int n;
	int* car_price;

	srand(time(0));
	switch (*q) {
	case 1:
		cout << "\n__Task A__\n";
		cout << "Enter n amount of Cars: ";
		cin >> n;
		n = CheckIntValue(&n);
		n = CheckMinMembersOfOrder(&n);
		car_price = new int[n];
		FindMiddlePriceOfCars(car_price, &n);
		delete[] car_price;
		break;
	case 2:
		cout << "\n__Task C__\n";
		cout << "Enter n amount of data: ";
		cin >> n;
		n = CheckIntValue(&n);
		n = CheckMinMembersOfOrder(&n);
		SortingDataMassive(&n);
		break;
	default:
		cout << "\n__You don't enter any task for execution__\n";
		break;
	}
	if (*q == 1 || *q == 2) {
		MenuOfSolution(q);
	}
}

int main() {
	int q;

	cout << "\nCreated by Vladislav Samoilov / KNT - 223\n";
	cout << "--------Select task:--------\n";
	cout << "Task A) Find Middle Price Of Cars - Enter 1\n";
	cout << "Task C) Sorting massive data - Enter 2\n";
	cout << "------------------------------------------------------------\n";
	cin >> q;
	q = CheckIntValue(&q);
	MenuOfSolution(&q);

	return main();
}