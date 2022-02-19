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

int* task2(int*& arr, int& size, int x) {

	++size;
	arr = (int*)realloc(arr, size * sizeof(int));
	arr[size - 1] = x;
	return arr;

}

int* deleteWithInd(int*& arr, int& size, int x) {

	for (int i = x; i < size - 1; ++i) {    //Сдвиг влево

		arr[i] = arr[i + 1];

	}

	--size;
	arr = (int*)realloc(arr, size * sizeof(int));
	return arr;

}

int* deleteWithValue(int*& arr, int& size, int x) {

	for (int i = 0; i < size; ++i) {

		if (arr[i] == x) {

			int temp = i;
			for (int j = temp; j < size - 1; ++j) {

				arr[j] = arr[j + 1];

			}
			--size;
			arr = (int*)realloc(arr, size * sizeof(int));
			--i;

		}

	}

	return arr;

}

void print(int* arr, int& size) {

	cout << "Получившийся массив: ";
	for (int i = 0; i < size; ++i) cout << arr[i] << " ";
	cout << endl;

}

int main() {

	setlocale(LC_ALL, "Russian");
	int size, x;

	cout << "Задание 1: ";
	cout << "Введите размер массива: ";
	cin >> size;
	int* arr = new int[size];
	cout << "Введите элементы массива: ";

	for (int i = 0; i < size; ++i) {

		cin >> arr[i];

	}

	print(arr, size);

	cout << "Задание 2: " << endl;
	cout << "Введите элемент, который хотите добавить в конец массива: ";
	cin >> x;
	print(task2(arr, size, x), size);

	cout << "Задание 3: " << endl;
	cout << "Введите индекс элемента, который хотите удалить: ";
	cin >> x;
	if (x < size) {

		print(deleteWithInd(arr, size, x), size);

	}
	else cout << "Некорректное значение" << endl;

	cout << "Задание 4: " << endl;
	cout << "Введите значение, которое хотите удалить из массива: ";
	cin >> x;
	print(deleteWithValue(arr, size, x), size);

}