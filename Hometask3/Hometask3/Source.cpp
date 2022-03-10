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
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef int* arr_t;

void cleanmem(arr_t& arr) {    //Очистка памяти

	free(arr);
	arr = NULL;

}

void alloc(arr_t& arr, int size) {

	arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {

		cout << "ERROR. Malloc failed" << endl;
		exit(0);

	}

}

void reallocation(arr_t& arr, int size) {   //Подаю изменённый size

	if (size == 0) cleanmem(arr);
	else {

		arr_t temp = (int*)realloc(arr, size * sizeof(int));
		if (temp == NULL) {

			cout << "ERROR. Realloc failed" << endl;
			cleanmem(arr);
			exit(1);

		}
		else arr = temp;

	}

}

arr_t task2(arr_t& arr, int& size, int x) {

	++size;
	reallocation(arr, size);

	arr[size - 1] = x;
	return arr;

}

arr_t deleteWithInd(arr_t& arr, int& size, int x) {

	for (int i = x; i < size - 1; ++i) {    //Сдвиг влево

		arr[i] = arr[i + 1];

	}

	--size;
	reallocation(arr, size);

	return arr;

}

arr_t deleteWithValue(arr_t& arr, int& size, int x) {

	for (int i = 0; i < size; ++i) {

		if (arr[i] == x) {

			int temp = i;
			for (int j = temp; j < size - 1; ++j) {

				arr[j] = arr[j + 1];

			}
			--size;
			reallocation(arr, size);
			--i;

		}

	}

	return arr;

}

void print(arr_t arr, int& size) {

	cout << "Получившийся массив: ";
	for (int i = 0; i < size; ++i) cout << arr[i] << " ";
	cout << endl;

}

int main() {

	setlocale(LC_ALL, "Russian");
	int size, x;
	int menu = -1;
	arr_t arr = NULL;

	while (menu != 0) {

		cout << "Выберите задание\n" <<
			"1 - ввести массив\n" <<
			"2 - добавление в конец массива\n" <<
			"3 - удаление элемента массива по индексу\n" <<
			"4 - удаление элемента массива по значению\n" <<
			"0 - выход из программы\n";
		cin >> menu;

		switch (menu) {

		case 1:
			cout << "Задание 1: " << endl;
			cout << "Введите размер массива: ";
			cin >> size;
			alloc(arr, size);

			cout << "Введите элементы массива: ";

			for (int i = 0; i < size; ++i) {

				cin >> arr[i];

			}

			print(arr, size);
			break;

		case 2:
			cout << "Задание 2: " << endl;
			cout << "Введите элемент, который хотите добавить в конец массива: ";
			cin >> x;
			print(task2(arr, size, x), size);
			break;

		case 3:
			cout << "Задание 3: " << endl;
			cout << "Введите индекс элемента, который хотите удалить: ";
			cin >> x;
			if (x < size) {

				print(deleteWithInd(arr, size, x), size);

			}
			else cout << "Некорректное значение" << endl;
			break;

		case 4:
			cout << "Задание 4: " << endl;
			cout << "Введите значение, которое хотите удалить из массива: ";
			cin >> x;
			print(deleteWithValue(arr, size, x), size);
			break;

		case 0:
			break;

		default:
			cout << "Некорректный ввод. Попробуйте снова." << endl;

		}

	}

	cleanmem(arr);

}