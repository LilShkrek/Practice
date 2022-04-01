#include <iostream>
#include "Queue.h"

using namespace std;

#define INIT_QUEUE 3
#define INC_QUEUE 3

#define PEAK_FAIL_ERROR -1
#define REALLOC_FAIL_ERROR -2
#define ENQUEUE_FAIL_ERROR -3
#define DEQUEUE_FAIL_ERROR -4
#define COPY_FAIL_ERROR -5

//int success_code;

typedef int* arr_t;
struct queue {

	arr_t arr = (arr_t)malloc(INIT_QUEUE * sizeof(int));
	int size = INIT_QUEUE;
	int head = -1;
	int tail = -1;

};

int Peak(queue_t q) {	// Возвращает "голову очереди"

	if (q.head < 0) {    // q.size < 1

		throw PEAK_FAIL_ERROR;

	}

	//success_code = OK_STATUS;
	return q.arr[q.head];

}

void CleanMem(queue_t& q) {		// Очистка памяти

	free(q.arr);
	q.arr = NULL;
	q.size = 0;
	q.head = 0;
	q.tail = 0;

}

bool IsEmpty(queue_t q) {	// Проверка на пустоту очереди

	try {

		int temp = Peak(q);
		return false;

	}
	catch (int error) {		// Ловим PEAK_FAIL_ERROR

		return true;

	}

}

void Reallocation(queue_t& q, int new_size) {		// Изменение объёма выделенной памяти под очередь

	arr_t temp = (arr_t)realloc(q.arr, new_size * sizeof(int));

	if (temp == NULL && new_size != 0) {

		//success_code = REALLOC_FAIL_ERROR;
		throw REALLOC_FAIL_ERROR;

	}
	else {

		q.arr = temp;

		for (int i = q.size; i < new_size; ++i) {

			q.arr[i] = 0;

		}

		q.size = new_size;
		//success_code = OK_STATUS;

	}

}

void Enqueue(queue_t& q, int num) {		// Запись в конец очереди

	//if ((q.tail == q.head - 1) || (q.head == 0 && q.tail == q.size - 1)) { //добавить сдвиг

	//	Reallocation(q, q.size + INC_QUEUE);
	//	if (success_code == REALLOC_FAIL_ERROR) {

	//		success_code = ENQUEUE_FAIL_ERROR;
	//		return;

	//	}

	//}

	//if (q.tail == -1) q.tail = 0;
	//if (q.head == -1) q.head = 0;

	//q.tail = (q.tail + 1) % q.size;
	//q.arr[q.tail] = num;

	//====================================

	try {

		if ((q.tail == q.head - 1) || (q.head == 0 && q.tail == q.size - 1)) {

			Reallocation(q, q.size + INC_QUEUE);
			
			if (q.tail == q.head - 1) {	

				for (int j = 0; j < INC_QUEUE; ++j) {

					for (int i = q.size + INC_QUEUE - 1; i > q.tail + 1; --i) {		// Раздвигаем элементы между головой и хвостом очереди

						q.arr[i] = q.arr[i - 1];

					}

					q.arr[q.tail + 1] = 0;

				}

			}

		}

		if (q.tail == -1) {

			for (int i = 0; i < INIT_QUEUE; ++i) q.arr[i] = 0;	// Заполнение пустого массива нулями

		}

		q.tail = (q.tail + 1) % q.size;		// Перемещение позиции "хвоста"
		q.arr[q.tail] = num;	// Изменение значения "хвоста"

		if (q.head == -1) q.head = 0;

	}
	catch (int error) {		//Ловим REALLOC_FAIL_ERROR

		throw ENQUEUE_FAIL_ERROR;

	}

}

int Dequeue(queue_t& q) {		// Удаление головы очереди

	/*cout << q.head << " " << q.tail << endl;
	int first = Peak(q);
	if (success_code == PEAK_FAIL_ERROR) success_code = DEQUEUE_FAIL_ERROR;
	else {

		if (q.head == q.tail) {

			q.arr[q.head] = 0;
			q.head = -1;
			q.tail = -1;

		}
		else {

			q.arr[q.head] = 0;
			q.head = (q.head + 1) % q.size;

		}

	}

	return first;*/


	//===================

	try {

		int first = Peak(q);
		if (q.head == q.tail) {		// Проверка на то, что в очереди 1 элемент

			q.arr[q.head] = 0;
			q.head = -1;
			q.tail = -1;

		}
		else {

			q.arr[q.head] = 0;
			q.head = (q.head + 1) % q.size;

		}

		return first;

	}
	catch (int error) {		// Ловим PEAK_FAIL_ERROR

		throw DEQUEUE_FAIL_ERROR;

	}

}

void CreateCopy(queue_t old_q, queue_t& new_q) {

	/*Reallocation(new_q, old_q.size);
	if (success_code == REALLOC_FAIL_ERROR) success_code = COPY_FAIL_ERROR;
	else {

		for (int i = 0; i < new_q.size; ++i) {

			new_q.arr[i] = old_q.arr[i];

		}

		success_code = OK_STATUS;

	}*/

	//==============

	try {

		Reallocation(new_q, old_q.size);
		for (int i = 0; i < new_q.size; ++i) {

			new_q.arr[i] = old_q.arr[i];

		}
		new_q.head = old_q.head;
		new_q.size = old_q.size;
		new_q.tail = old_q.tail;

	}
	catch (int error) {		// Ловим REALLOC_FAIL_ERROR

		throw COPY_FAIL_ERROR;

	}

}

void PrintQueue(queue_t q) {

	for (int i = 0; i < q.size; ++i) {

		cout << q.arr[i] << " ";

	}

	cout << endl;

}


//======================================================

void ThrowError(int error) {

	switch (error) {

	case PEAK_FAIL_ERROR:
		throw PEAK_FAIL_ERROR;
		break;

	case REALLOC_FAIL_ERROR:
		throw REALLOC_FAIL_ERROR;
		break;

	case ENQUEUE_FAIL_ERROR:
		throw ENQUEUE_FAIL_ERROR;
		break;

	case DEQUEUE_FAIL_ERROR:
		throw DEQUEUE_FAIL_ERROR;
		break;

	case COPY_FAIL_ERROR:
		throw COPY_FAIL_ERROR;
		break;

	}

}

void PrintError(int error) {

	switch (error) {

	case PEAK_FAIL_ERROR:
		cout << "Peak failed\n";
		break;

	case REALLOC_FAIL_ERROR:
		cout << "Realloc failed\n";
		break;

	case ENQUEUE_FAIL_ERROR:
		cout << "Enqueue failed\n";
		break;

	case DEQUEUE_FAIL_ERROR:
		cout << "Dequeue failed\n";
		break;

	case COPY_FAIL_ERROR:
		cout << "Copy failed\n";
		break;

	}

}

void Destroy(queue_t& q) {

	try {

		while (!IsEmpty(q)) {

			cout << Dequeue(q) << " ";

		}

		cout << endl;

	}
	catch (int error) {		// Ловим DEQUEUE_FAIL_ERROR

		throw DEQUEUE_FAIL_ERROR;

	}

}

void task4(queue_t& q) {

	queue_t new_q, copy_q;

	try {

		CreateCopy(q, copy_q);

		while (!IsEmpty(copy_q)) {

			Enqueue(new_q, Dequeue(copy_q));
			Enqueue(new_q, 0);

		}

		CreateCopy(new_q, q);
		CleanMem(new_q);
		//CleanMem(copy_q);

	}
	catch (int error) {

		CleanMem(new_q);
		//CleanMem(copy_q);
		ThrowError(error);

	}

}

void task5(queue_t& q) {

	queue_t new_q, copy_q;

	try {

		CreateCopy(q, copy_q);

		while (!IsEmpty(copy_q)) {

			int head = Dequeue(copy_q);
			if (!IsEmpty(copy_q)) Enqueue(new_q, head);

		}

		CreateCopy(new_q, q);
		CleanMem(new_q);

	}
	catch (int error) {

		CleanMem(new_q);
		ThrowError(error);

	}

}

void task6(queue_t& q) {

	queue_t new_q, copy_q;

	try {

		CreateCopy(q, copy_q);

		int tail, head = Peak(copy_q);

		while (!IsEmpty(copy_q)) {

			tail = Dequeue(copy_q);

		}

		CreateCopy(q, copy_q);
		Enqueue(new_q, tail);
		task5(copy_q);		// Удалили "хвост" очереди
		Dequeue(copy_q);	// Удалили "голову" очереди

		while (!IsEmpty(copy_q)) {

			Enqueue(new_q, Dequeue(copy_q));

		}

		Enqueue(new_q, head);
		CreateCopy(new_q, q);
		CleanMem(new_q);
		
	}
	catch (int error) {

		CleanMem(new_q);
		ThrowError(error);

	}

}

void temp(){

	queue_t q;
	int x, menu;

	try {

		cout << "Введите элементы очереди\n";

		while (cin.peek() != '\n') {

			cin >> x;
			Enqueue(q, x);

		}

		//Dequeue(q);
		//task4(q);
		//task5(q);
		/*task6(q);
		PrintQueue(q);
		Destroy(q);*/

		do {

			cout << "\nВыберите действие:\n1 - Очистить очередь\n2 - Добавить в очередь\n3 - Извлечь из очереди\n\
4 - После каждого элемента элемента очереди поставить 0. Пример: 1, 2, 3 -> 1, 0, 2, 0, 3, 0\n\
5 - Удалить последний элемент (хвост)\n6 - Поменять местами первый и последний элемент очереди\n0 - Выйти из программы\n";
			cin >> menu;

			switch (menu) {

			case 1:
				Destroy(q);
				break;

			case 2:
				cout << "Введите элемент, который хотите добавить: ";
				cin >> x;
				Enqueue(q, x);
				PrintQueue(q);
				break;

			case 3:
				cout << "\"Голова\" очереди - " << Dequeue(q) << endl;
				PrintQueue(q);
				break;

			case 4:
				task4(q);
				PrintQueue(q);
				break;

			case 5:
				task5(q);
				PrintQueue(q);
				break;

			case 6:
				task6(q);
				PrintQueue(q);
				break;

			default:
				cout << "Введено некорректное значение, попробуйте снова\n";

			}

		} while (menu != 0);

	}
	catch (int error) {

		PrintError(error);

	}

}