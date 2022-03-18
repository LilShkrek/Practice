#include <iostream>

using namespace std;

#define OK_STATUS 1
#define MALLOC_FAIL_ERROR -2
#define REALLOC_FAIL_ERROR -3
#define PEAK_FAIL_ERROR -4
#define PUSHBACK_FAIL_ERROR -5
#define POPBACK_FAIL_ERROR -6
#define TASK4_FAIL_ERROR -7
#define TASK5_FAIL_ERROR -8
#define TASK6_FAIL_ERROR -9
#define DESTROY_FAIL_ERROR -10

int success_code;

typedef int* arr_t;
typedef struct arr {

	arr_t ptr = NULL;
	int size = 0;

}stack_t;

int peak(stack_t stack) {   // ���������� "��������" ����� ��� ��������

	if (stack.size < 1) {

		success_code = PEAK_FAIL_ERROR;
		return -120321;   // ������ ��������� �����. ��� �� ����� ��������������, �.�. ������� ���������� success_code

	}
	else {

		success_code = OK_STATUS;
		return stack.ptr[stack.size - 1];

	}

}

bool isempty(stack_t stack) {

	int temp = peak(stack);
	if (success_code == PEAK_FAIL_ERROR) return true;
	return false;

}

void cleanmem(stack_t& stack) {   // ������� ������

	free(stack.ptr);
	stack.ptr = NULL;
	stack.size = 0;

}

void reallocation(stack_t& stack) {   // ��������� ������� �����

	arr_t temp = (int*)realloc(stack.ptr, stack.size * sizeof(int));
	//int temp_size = sizeof(temp) / sizeof(temp[0]);
	if (temp == NULL && stack.size != 0) {

		success_code = REALLOC_FAIL_ERROR;
		cleanmem(stack);

	}
	else {

		stack.ptr = temp;
		success_code = OK_STATUS;

	}

}

//void alloc(arr_t& arr, int size) {    // ��������� ������ ��� ������
//
//	arr = (int*)malloc(size * sizeof(int));
//	if (arr == NULL) {
//
//		success_code = MALLOC_FAIL_ERROR;
//
//	}else success_code = OK_STATUS;
//
//}

void pushback(stack_t& stack, int x) {   // ���������� �������� � ����

	++stack.size;
	reallocation(stack);
	if (success_code == REALLOC_FAIL_ERROR) {

		--stack.size;
		success_code = PUSHBACK_FAIL_ERROR;

	}
	else {

		stack.ptr[stack.size - 1] = x;
		success_code = OK_STATUS;

	}

}

int popback(stack_t& stack) {   // ������� �������� � ���������� �������� "��������"

	int top = peak(stack);
	if (success_code == PEAK_FAIL_ERROR) success_code = POPBACK_FAIL_ERROR;
	else {

		--stack.size;
		reallocation(stack);
		if (success_code == REALLOC_FAIL_ERROR) {

			++stack.size;
			success_code = POPBACK_FAIL_ERROR;

		}
		else {

			success_code = OK_STATUS;

		}

	}

	return top;

}

void destroy(stack_t& stack) {   // �������� ���� (��������� ��������� � ��������� ��� ��������)

	//cout << "DESTROOOY" << endl;
	
	while (!isempty(stack)) {

		cout << popback(stack) << " ";
		if (success_code == POPBACK_FAIL_ERROR) {

			success_code = DESTROY_FAIL_ERROR;
			break;

		}

	}
	cout << endl;

}

void print(stack_t stack) {   // ����� ������� ����� � ������ �����( �� ���� - destroy() )

	while (!isempty(stack)) {

		cout << popback(stack) << " ";
		if (success_code == POPBACK_FAIL_ERROR) {

			success_code = DESTROY_FAIL_ERROR;
			break;

		}

	}
	cout << endl;

}

void task4(stack_t& stack) {    // �������� ������� 2 ������� ��������

	int top1, top2;
	top1 = popback(stack);  // ������� �������
	if (success_code == POPBACK_FAIL_ERROR) {

		success_code = TASK4_FAIL_ERROR;
		return;

	}
	top2 = popback(stack);  // ������ ������� �������
	if (success_code == POPBACK_FAIL_ERROR) {

		success_code = TASK4_FAIL_ERROR;
		return;

	}

	//cout << "������� �������: " << top1 << " " << "������ ������� �������: " << top2 << endl;

	pushback(stack, top1);
	if (success_code == PUSHBACK_FAIL_ERROR) {

		success_code = TASK4_FAIL_ERROR;
		return;

	}
	pushback(stack, top2);
	if (success_code == PUSHBACK_FAIL_ERROR) {

		success_code = TASK4_FAIL_ERROR;
		return;

	}

}

int task5(stack_t& stack) {  // ������� ����� ������ ������� ����� (� ��� �������)

	if (isempty(stack)) {

		success_code = TASK5_FAIL_ERROR;
		return 0;  //

	}
	else {

		stack_t temp_stack;

		while (!isempty(stack)) {  // ������� ����������� ������������ ����� �� ���������(�� �����������)

			int top = popback(stack);
			if (success_code == POPBACK_FAIL_ERROR) { 

				success_code = TASK5_FAIL_ERROR;
				return 123213; //

			}

			pushback(temp_stack, top);
			if (success_code == PUSHBACK_FAIL_ERROR) {

				success_code = TASK5_FAIL_ERROR;
				return 123213; //

			}

		}

		int first = popback(temp_stack);  // ������� ������� ������� ���������� �����, �.�. ������ ������������
		if (success_code == POPBACK_FAIL_ERROR) {

			success_code = TASK5_FAIL_ERROR;
			return 123213; //

		}

		while (!isempty(temp_stack)) {  // ��������� �������

			int top = popback(temp_stack);
			if (success_code == POPBACK_FAIL_ERROR) {

				success_code = TASK5_FAIL_ERROR;
				return 123213; //

			}

			pushback(stack, top);
			if (success_code == PUSHBACK_FAIL_ERROR) {

				success_code = TASK5_FAIL_ERROR;
				return 123213; //

			}

		}

		cleanmem(temp_stack);
		return first;

	}

}

void task6(stack_t& stack) {  // �������� ������� ������� � ������ ������� ����� (���� � �������)

	int top = peak(stack);
	if (success_code == PEAK_FAIL_ERROR) {

		success_code = TASK6_FAIL_ERROR;
		return; //

	}

	int first;
	stack_t temp_stack;

	while (!isempty(stack)) {  // ������� ����������� ������������ ����� �� ���������(�� �����������)

		int top1 = popback(stack);
		if (success_code == POPBACK_FAIL_ERROR) {

			success_code = TASK6_FAIL_ERROR;
			return; //

		}

		pushback(temp_stack, top1);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			success_code = TASK6_FAIL_ERROR;
			return; //

		}

	}

	first = popback(temp_stack);
	if (success_code == POPBACK_FAIL_ERROR) {

		success_code = TASK6_FAIL_ERROR;
		return; //

	}

	//cout << "������� ������� �����: " << top << " ������ ������� �����: " << first << endl;

	pushback(stack, top);

	while (!isempty(temp_stack)) {  // ��������� �������

		int top1 = popback(temp_stack);
		if (success_code == POPBACK_FAIL_ERROR) {

			success_code = TASK6_FAIL_ERROR;
			return; //

		}

		pushback(stack, top1);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			success_code = TASK6_FAIL_ERROR;
			return; //

		}

	}

	int k = popback(stack);
	if (success_code == POPBACK_FAIL_ERROR) {

		success_code = TASK6_FAIL_ERROR;
		return; //

	}

	pushback(stack, first);
	if (success_code == PUSHBACK_FAIL_ERROR) {

		success_code = TASK6_FAIL_ERROR;
		return; //

	}

	cleanmem(temp_stack);

}

int main() {

	setlocale(LC_ALL, "Russian");
	int menu, x, top, first;

	stack_t stack;

	cout << "������� �������� �����" << endl;

	while (cin.peek() != '\n') {

		cin >> x;
		pushback(stack, x);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			cout << "NO MORE MEMORY!! STOP PLS!" << endl;
			break;

		}

	}

	cout << "�������� ��������\n" <<
		"1 - �������� ���� (��������� ��������� � ��������� ��� ��������)\n" <<
		"2 - �������� � ����\n" <<
		"3 - ������� �� ����� �������� (� � �������)\n" <<
		"4 - �������� ������� ��� ������� �������� (� �� �������)\n" <<
		"5 - ������� ����� ������ ������� ����� (� ��� �������)\n" <<
		"6 - �������� ������� ������� � ������ ������� ����� (���� � �������)\n" <<
		"0 - ����� �� ���������\n";

	do {

		cin >> menu;

		switch (menu) {

		case 1:
			destroy(stack);
			if (success_code == DESTROY_FAIL_ERROR) cout << "Destroy error" << endl;
			break;

		case 2:
			cout << "������� �������, ������� ������ �������� � ����: ";
			cin >> x;
			pushback(stack, x);
			if (success_code == PUSHBACK_FAIL_ERROR) cout << "Pushback error" << endl;
			break;

		case 3:
			top = popback(stack);
			if (success_code == POPBACK_FAIL_ERROR) cout << "Popback error" << endl;
			else cout << "������� ������� �����: " << top << endl;
			break;

		case 4:
			task4(stack);
			if (success_code == TASK4_FAIL_ERROR) cout << "Task 4 failed" << endl;
			//print(stack);
			break;

		case 5:
			first = task5(stack);
			if (success_code == TASK5_FAIL_ERROR) cout << "Task 5 failed" << endl;
			else cout << "������ ������� �����: " << first << endl;
			//print(stack);
			break;

		case 6:
			task6(stack);
			if (success_code == TASK6_FAIL_ERROR) cout << "Task 6 failed" << endl;
			//print(stack);
			break;

		case 0:
			break;

		default:
			cout << "������� ������������ ��������. ���������� �����" << endl;
			break;

		}

	} while (menu != 0);

	cleanmem(stack);

}