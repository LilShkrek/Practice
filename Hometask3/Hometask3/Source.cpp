/******************************************************************************
1) ������ ������
2) �������� ������� � �����
3) ������� ������� �� �������
4) ������� �������� �� ��������
arr - ������
size - ����� �������
x - �����, �������, ��������
*******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef int* arr_t;

void cleanmem(arr_t& arr) {    //������� ������

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

void reallocation(arr_t& arr, int size) {   //����� ��������� size

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

	for (int i = x; i < size - 1; ++i) {    //����� �����

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

	cout << "������������ ������: ";
	for (int i = 0; i < size; ++i) cout << arr[i] << " ";
	cout << endl;

}

int main() {

	setlocale(LC_ALL, "Russian");
	int size, x;
	int menu = -1;
	arr_t arr = NULL;

	while (menu != 0) {

		cout << "�������� �������\n" <<
			"1 - ������ ������\n" <<
			"2 - ���������� � ����� �������\n" <<
			"3 - �������� �������� ������� �� �������\n" <<
			"4 - �������� �������� ������� �� ��������\n" <<
			"0 - ����� �� ���������\n";
		cin >> menu;

		switch (menu) {

		case 1:
			cout << "������� 1: " << endl;
			cout << "������� ������ �������: ";
			cin >> size;
			alloc(arr, size);

			cout << "������� �������� �������: ";

			for (int i = 0; i < size; ++i) {

				cin >> arr[i];

			}

			print(arr, size);
			break;

		case 2:
			cout << "������� 2: " << endl;
			cout << "������� �������, ������� ������ �������� � ����� �������: ";
			cin >> x;
			print(task2(arr, size, x), size);
			break;

		case 3:
			cout << "������� 3: " << endl;
			cout << "������� ������ ��������, ������� ������ �������: ";
			cin >> x;
			if (x < size) {

				print(deleteWithInd(arr, size, x), size);

			}
			else cout << "������������ ��������" << endl;
			break;

		case 4:
			cout << "������� 4: " << endl;
			cout << "������� ��������, ������� ������ ������� �� �������: ";
			cin >> x;
			print(deleteWithValue(arr, size, x), size);
			break;

		case 0:
			break;

		default:
			cout << "������������ ����. ���������� �����." << endl;

		}

	}

	cleanmem(arr);

}