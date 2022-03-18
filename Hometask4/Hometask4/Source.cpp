#include <iostream>

using namespace std;

typedef int* arr_t;
typedef struct arr {

	int size;
	arr_t ptr;

}stack_t;

int peak(stack_t stack) {   //Возвращает "верхушку" стека без удаления

	return stack.ptr[stack.size - 1]; //сделать проверку на размер

}

void cleanmem(stack_t& stack) {   //Очистка памяти

	free(stack.ptr);
	stack.ptr = NULL;
	stack.size = 0;

}

void reallocation(stack_t& stack) {   //Изменение размера стека

	if (stack.size == 0) cleanmem(stack);
	else {

		arr_t temp = (int*)realloc(stack.ptr, stack.size * sizeof(int));
		if (temp == NULL) {

			cout << "ERROR. Realloc failed" << endl;
			cleanmem(stack);
			//exit(0);

		}
		else stack.ptr = temp;

	}

}

void alloc(arr_t& arr, int size) {    //Выделение памяти под массив

	arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {

		cout << "ERROR. Malloc failed" << endl;
		exit(0);

	}

}

void pushback(stack_t& stack, int x) {   //Добавление элемента в стек

	++stack.size;
	reallocation(stack);
	stack.ptr[stack.size - 1] = x;

}

void popback(stack_t& stack) {   //Удаляет верхушку

	//int top;

	if (stack.size == 0) {

		cout << "Error. Stack is already empty" << endl;
		//exit(0);

	}
	else {

		//cout << "Top element of stack: " << peak(stack) << endl;
		//top = peak(stack);
		--stack.size;
		reallocation(stack);

	}

}

void destroy(stack_t& stack) {   //Очистить стек (поочерёдно удаляются и выводятся все элементы)

	//cout << "DESTROOOY" << endl;
	
	for (int i = stack.size; i > 0; --i) {   //Вывод в мейне

		cout << peak(stack) << " ";
		popback(stack);

	}

	cout << endl;

}

void print(stack_t stack) {   //Вывод размера стека и самого стека

	if (stack.size == 0) cout << "Stack is empty" << endl;
	else {

		cout << "Size: " << stack.size << endl;
		for (int i = 0; i < stack.size; ++i) {

			cout << stack.ptr[i] << " ";

		}
		cout << endl;

	}

}

void task4(stack_t& stack) {   

	if (stack.size < 2) { //Так нельзя

		cout << "Error. Not enough elements" << endl;
		exit(0);

	}else {

		int top1, top2;
		top1 = peak(stack);  //Верхний элемент
		popback(stack);
		top2 = peak(stack);  //Второй верхний элемент
		popback(stack);
		pushback(stack, top1);
		pushback(stack, top2);

	}

}

int task5(stack_t& stack) {

	if (stack.size < 1) {

		cout << "Error. Stack is empty" << endl;
		exit(0);

	}else {

		arr_t arr1 = NULL;
		alloc(arr1, 0);        //Должен принимать стек
		stack_t temp_stack = { 0, arr1 };

		for (int i = stack.size; i > 0; --i) {   //Перенос содержимого изначального стека во временный(он перевернётся)

			pushback(temp_stack, peak(stack));  //цикл до ошибки
			popback(stack);

		}

		int first = peak(temp_stack);
		popback(temp_stack);  //Удалили верхний элемент временного стека, т.е. нижний изначального

		for (int i = temp_stack.size; i > 0; --i) {  //цикл до ошибки

			pushback(stack, peak(temp_stack));  
			popback(temp_stack);

		}

		//cleanmem(temp_stack);

		return first;

	}//сделать реалок

}

void task6(stack_t& stack) {  //некорректно работает

	int top = peak(stack);
	int first;

	arr_t arr1 = NULL;
	alloc(arr1, 0);
	stack_t temp_stack = { 0, arr1 };

	for (int i = stack.size; i > 0; --i) {

		pushback(temp_stack, peak(stack));
		popback(stack);

	}

	first = peak(temp_stack);
	//popback(temp_stack);
	pushback(stack, top);

	for (int i = temp_stack.size; i > 2; --i) {

		pushback(stack, peak(temp_stack));
		popback(temp_stack);

	}
	pushback(stack, first);

	cleanmem(temp_stack);

}

int main() {

	setlocale(LC_ALL, "Russian");
	int menu, x;

	arr_t arr = NULL;
	alloc(arr, 0);
	stack_t stack = { 0, arr };

	cout << "Введите элементы стека" << endl;

	while (cin.peek() != '\n') {

		cin >> x;
		pushback(stack, x);

	}

	cout << "Выберите действие\n" <<
		"1 - Очистить стек (поочерёдно удаляются и выводятся все элементы)\n" <<
		"2 - Добавить в стек\n" <<
		"3 - Извлечь из стека верхушку (с её выводом)\n" <<
		"4 - Поменять местами два верхних элемента (с их выводом)\n" <<
		"5 - Удалить самый нижний элемент стека (с его выводом)\n" <<
		"6 - Поменять местами верхний и нижний элемент стека (тоже с выводом)\n" <<
		"0 - Выход из программы\n";
	cin >> menu;

	switch (menu) {

	case 1:
		destroy(stack);
		break;

	case 2:
		cout << "Введите элемент, который хотите добавить в стек: ";
		cin >> x;
		pushback(stack, x);
		break;

	case 3:
		cout << "Верхний элемент стека: " << peak(stack) << endl;
		popback(stack);
		break;

	case 4:
		task4(stack);
		print(stack);
		break;

	case 5:
		cout << "Нижний элемент стека: " << task5(stack) << endl;
		print(stack);
		break;

	case 6:
		task6(stack);
		print(stack);
		break;

	case 0:
		break;

	default:
		cout << "Введено некорректное значение. Попробуйте снова" << endl;
		break;

	}

	cleanmem(stack);

}