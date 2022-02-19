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

using namespace std;

int* task2(int*& arr, int& size, int x) {

	++size;
	arr = (int*)realloc(arr, size * sizeof(int));
	arr[size - 1] = x;
	return arr;

}

int* deleteWithInd(int*& arr, int& size, int x) {

	for (int i = x; i < size - 1; ++i) {    //����� �����

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

	cout << "������������ ������: ";
	for (int i = 0; i < size; ++i) cout << arr[i] << " ";
	cout << endl;

}

int main() {

	setlocale(LC_ALL, "Russian");
	int size, x;

	cout << "������� 1: ";
	cout << "������� ������ �������: ";
	cin >> size;
	int* arr = new int[size];
	cout << "������� �������� �������: ";

	for (int i = 0; i < size; ++i) {

		cin >> arr[i];

	}

	print(arr, size);

	cout << "������� 2: " << endl;
	cout << "������� �������, ������� ������ �������� � ����� �������: ";
	cin >> x;
	print(task2(arr, size, x), size);

	cout << "������� 3: " << endl;
	cout << "������� ������ ��������, ������� ������ �������: ";
	cin >> x;
	if (x < size) {

		print(deleteWithInd(arr, size, x), size);

	}
	else cout << "������������ ��������" << endl;

	cout << "������� 4: " << endl;
	cout << "������� ��������, ������� ������ ������� �� �������: ";
	cin >> x;
	print(deleteWithValue(arr, size, x), size);

}