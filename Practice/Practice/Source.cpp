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

void print(int* arr, int size) {

	cout << "������������ ������: ";
	for (int i = 0; i < size; ++i) cout << arr[i] << " ";
	cout << endl;

}

int main() {

	setlocale(LC_ALL, "Russian");
	int size;
	cout << "������� ������ �������: ";
	cin >> size;
	int* arr = new int[size];
	cout << "������� �������� �������: ";

	for (int i = 0; i < size; ++i) {

		cin >> arr[i];

	}

	print(arr, size);

}