#include <iostream>

using namespace std;

#define OK_STATUS 1
#define MALLOC_FAIL_ERROR -2
#define REALLOC_FAIL_ERROR -3
#define PEAK_FAIL_ERROR -4
#define PUSHBACK_FAIL_ERROR -5
#define POPBACK_FAIL_ERROR -6
#define EMPTY_STACK_ERROR -7
#define DESTROY_FAIL_ERROR -8
#define COPY_FAIL_ERROR -9

int success_code;

typedef int* arr_t;
typedef struct arr {

	arr_t ptr = NULL;
	int size = 0;

}stack_t;

int peak(stack_t stack) {   // Возвращает "верхушку" стека без удаления

	if (stack.size < 1) {

		success_code = PEAK_FAIL_ERROR;
		return -120321;   // Просто рандомное число. Оно не будет использоваться, т.к. сначала проверится success_code

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

void cleanmem(stack_t& stack) {   // Очистка памяти

	free(stack.ptr);
	stack.ptr = NULL;
	stack.size = 0;

}

void reallocation(stack_t& stack, int new_size) {   // Изменение размера стека

	arr_t temp = (arr_t)realloc(stack.ptr, new_size * sizeof(int));
	//int temp_size = sizeof(temp) / sizeof(temp[0]);
	if (temp == NULL && new_size != 0) {

		success_code = REALLOC_FAIL_ERROR;
		//cleanmem(stack);

	}
	else {

		stack.ptr = temp;
		stack.size = new_size;
		success_code = OK_STATUS;

	}

}

//void alloc(arr_t& arr, int size) {    // Выделение памяти под массив
//
//	arr = (int*)malloc(size * sizeof(int));
//	if (arr == NULL) {
//
//		success_code = MALLOC_FAIL_ERROR;
//
//	}else success_code = OK_STATUS;
//
//}

void pushback(stack_t& stack, int x) {   // Добавление элемента в стек

	reallocation(stack, stack.size + 1);
	if (success_code == REALLOC_FAIL_ERROR) success_code = PUSHBACK_FAIL_ERROR;
	else {

		stack.ptr[stack.size - 1] = x;
		success_code = OK_STATUS;

	}

}

int popback(stack_t& stack) {   // Удаляет верхушку и возвращает значение "верхушку"

	int top = peak(stack);
	if (success_code == PEAK_FAIL_ERROR) success_code = POPBACK_FAIL_ERROR;
	else {

		reallocation(stack, stack.size - 1);
		if (success_code == REALLOC_FAIL_ERROR) success_code = POPBACK_FAIL_ERROR;
		else success_code = OK_STATUS;

	}

	return top;

}

void destroy(stack_t& stack) {   // Очистить стек (поочерёдно удаляются и выводятся все элементы)

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

//void print(stack_t stack) {   // Вывод размера стека и самого стека( по сути - destroy() )
//
//	while (!isempty(stack)) {
//
//		cout << popback(stack) << " ";
//		if (success_code == POPBACK_FAIL_ERROR) {
//
//			success_code = DESTROY_FAIL_ERROR;
//			break;
//
//		}
//
//	}
//	cout << endl;
//
//}

void createcopy(stack_t stack, stack_t& new_stack) {	// Создание копии стека

	reallocation(new_stack, stack.size);
	if (success_code == REALLOC_FAIL_ERROR) success_code = COPY_FAIL_ERROR;
	else {

		for (int i = 0; i < new_stack.size; ++i) {

			new_stack.ptr[i] = stack.ptr[i];

		}

		success_code = OK_STATUS;

	}
	
}

void task4(stack_t& stack) {    // Поменять местами 2 верхних элемента
	
	stack_t new_stack;    // Создание копии стека
	createcopy(stack, new_stack);
	if (success_code == COPY_FAIL_ERROR) {

		return;

	}

	int top1, top2;
	top1 = popback(new_stack);  // Верхний элемент
	if (success_code == POPBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		return;

	}
	top2 = popback(new_stack);  // Второй верхний элемент
	if (success_code == POPBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		return;

	}

	//cout << "Верхний элемент: " << top1 << " " << "Второй верхний элемент: " << top2 << endl;

	pushback(new_stack, top1);
	if (success_code == PUSHBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		return;

	}
	pushback(new_stack, top2);
	if (success_code == PUSHBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		return;

	}

	createcopy(new_stack, stack);
	cleanmem(new_stack);
	success_code = OK_STATUS;

}

int task5(stack_t& stack) {  // Удалить самый нижний элемент стека (с его выводом)

	if (isempty(stack)) {

		success_code = EMPTY_STACK_ERROR;
		return 1232123;  //

	}

	stack_t new_stack;    // Создание копии стека
	createcopy(stack, new_stack);
	if (success_code == COPY_FAIL_ERROR) {

		return 1232123;

	}

	stack_t temp_stack;

	while (!isempty(new_stack)) {  // Перенос содержимого изначального стека во временный(он перевернётся)

		int top = popback(new_stack);
		if (success_code == POPBACK_FAIL_ERROR) { 

			cleanmem(new_stack);
			return 123213; //

		}

		pushback(temp_stack, top);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			cleanmem(new_stack);
			cleanmem(temp_stack);
			return 123213; //

		}

	}

	int first = popback(temp_stack);  // Удалили верхний элемент временного стека, т.е. нижний изначального
	if (success_code == POPBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		cleanmem(temp_stack);
		return 123213; //

	}

	while (!isempty(temp_stack)) {  // Переносим обратно

		int top = popback(temp_stack);
		if (success_code == POPBACK_FAIL_ERROR) {

			cleanmem(new_stack);
			cleanmem(temp_stack);
			return 123213; //

		}

		pushback(new_stack, top);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			cleanmem(new_stack);
			cleanmem(temp_stack);
			return 123213; //

		}

	}

	createcopy(new_stack, stack);
	cleanmem(new_stack);
	success_code = OK_STATUS;
	return first;

}

void task6(stack_t& stack) {  // Поменять местами верхний и нижний элемент стека (тоже с выводом)

	stack_t new_stack;    // Создание копии стека
	createcopy(stack, new_stack);
	if (success_code == COPY_FAIL_ERROR) {

		return;

	}

	int top = peak(new_stack);
	if (success_code == PEAK_FAIL_ERROR) {

		cleanmem(new_stack);
		return; //

	}

	int first;
	stack_t temp_stack;

	while (!isempty(new_stack)) {  // Перенос содержимого изначального стека во временный(он перевернётся)

		int top1 = popback(new_stack);
		if (success_code == POPBACK_FAIL_ERROR) {

			cleanmem(new_stack);
			cleanmem(temp_stack);
			return; //

		}

		pushback(temp_stack, top1);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			cleanmem(new_stack);
			cleanmem(temp_stack);
			return; //

		}

	}

	first = popback(temp_stack);
	if (success_code == POPBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		cleanmem(temp_stack);
		return; //

	}

	//cout << "Верхний элемент стека: " << top << " Нижний элемент стека: " << first << endl;

	pushback(new_stack, top);

	while (!isempty(temp_stack)) {  // Переносим обратно

		int top1 = popback(temp_stack);
		if (success_code == POPBACK_FAIL_ERROR) {

			cleanmem(new_stack);
			cleanmem(temp_stack);
			return; //

		}

		pushback(new_stack, top1);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			cleanmem(new_stack);
			cleanmem(temp_stack);
			return; //

		}

	}

	int k = popback(new_stack);
	if (success_code == POPBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		return; //

	}

	pushback(new_stack, first);
	if (success_code == PUSHBACK_FAIL_ERROR) {

		cleanmem(new_stack);
		return; //

	}

	createcopy(new_stack, stack);
	cleanmem(new_stack);
	success_code = OK_STATUS;

}

void printerror() {

	switch (success_code) {

	case -2:
		cout << "MALLOC FAILED" << endl;
		break;
	case -3:
		cout << "REALLOC FAILED" << endl;
		break;
	case -4:
		cout << "PEAK FAILED" << endl;
		break;
	case -5:
		cout << "PUSHBACK FAILED" << endl;
		break;
	case -6:
		cout << "POPBACK FAILED" << endl;
		break;
	case -7:
		cout << "STACK IS EMPTY" << endl;
		break;
	case -8:
		cout << "DESTROY FAILED" << endl;
		break;
	case -9:
		cout << "COPY FAILED" << endl;
		break;

	}

}

int main() {

	setlocale(LC_ALL, "Russian");
	int menu, x, top, first;

	stack_t stack;

	cout << "Введите элементы стека" << endl;

	while (cin.peek() != '\n') {

		cin >> x;
		pushback(stack, x);
		if (success_code == PUSHBACK_FAIL_ERROR) {

			cout << "NO MORE MEMORY!! STOP PLS!" << endl;
			break;

		}

	}

	cout << "Выберите действие\n" <<
		"1 - Очистить стек (поочерёдно удаляются и выводятся все элементы)\n" <<
		"2 - Добавить в стек\n" <<
		"3 - Извлечь из стека верхушку (с её выводом)\n" <<
		"4 - Поменять местами два верхних элемента (с их выводом)\n" <<
		"5 - Удалить самый нижний элемент стека (с его выводом)\n" <<
		"6 - Поменять местами верхний и нижний элемент стека (тоже с выводом)\n" <<
		"0 - Выход из программы\n";

	do {

		cin >> menu;

		switch (menu) {

		case 1:
			destroy(stack);
			if (success_code == DESTROY_FAIL_ERROR) printerror();
			break;

		case 2:
			cout << "Введите элемент, который хотите добавить в стек: ";
			cin >> x;
			pushback(stack, x);
			if (success_code == PUSHBACK_FAIL_ERROR) printerror();
			break;

		case 3:
			top = popback(stack);
			if (success_code == POPBACK_FAIL_ERROR) printerror();
			else cout << "Верхний элемент стека: " << top << endl;
			break;

		case 4:
			task4(stack);
			if (success_code < 0) printerror();
			//print(stack);
			break;

		case 5:
			first = task5(stack);
			if (success_code < 0) printerror();
			else cout << "Нижний элемент стека: " << first << endl;
			//print(stack);
			break;

		case 6:
			task6(stack);
			if (success_code < 0) printerror();
			//print(stack);
			break;

		case 0:
			break;

		default:
			cout << "Введено некорректное значение. Попробуйте снова" << endl;
			break;

		}

	} while (menu != 0);

	cleanmem(stack);

}