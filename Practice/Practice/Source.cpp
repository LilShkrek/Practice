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

void print(int* arr, int& size) {

	cout << "������������ ������: ";
	for (int i = 0; i < size; ++i) cout << arr[i] << " ";
	cout << endl;

}

int main() {

	setlocale(LC_ALL, "Russian");
	int size, x;
	cout << "������� ������ �������: ";
	cin >> size;
	int* arr = new int[size];
	cout << "������� �������� �������: ";

	for (int i = 0; i < size; ++i) {

		cin >> arr[i];

	}

	print(arr, size);
	cout << "������� �������, ������� ������ �������� � ����� �������: ";
	cin >> x;
	print(task2(arr, size, x), size);

}