/******************************************************************************
1) Ввести массив
2) Добавить элемент в конец
3) Удалить элемент по позиции
4) Удалить элементы по значению
arr - массив
size - длина массива
x - Число, позиция, значение
*******************************************************************************/

#include <iostream>

using namespace std;

void print(int* arr, int size) {

	cout << "Получившийся массив: ";
	for (int i = 0; i < size; ++i) cout << arr[i] << " ";
	cout << endl;

}

int main() {

	setlocale(LC_ALL, "Russian");
	int size;
	cout << "Введите размер массива: ";
	cin >> size;
	int* arr = new int[size];
	cout << "Введите элементы массива: ";

	for (int i = 0; i < size; ++i) {

		cin >> arr[i];

	}

	print(arr, size);

}