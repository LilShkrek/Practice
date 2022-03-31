#include <iostream>
#include "Queue.h"

using namespace std;

#define INIT_QUEUE 3
#define INC_QUEUE 3

#define OK_STATUS 1
#define PEAK_FAIL_ERROR -1
#define REALLOC_FAIL_ERROR -2
#define ENQUEUE_FAIL_ERROR -3
#define DEQUEUE_FAIL_ERROR -4
#define DESTROY_FAIL_ERROR -5
#define COPY_FAIL_ERROR -6

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

	}
	catch (int error) {		// Ловим REALLOC_FAIL_ERROR

		throw COPY_FAIL_ERROR;

	}

}

//void Destroy(queue_t& q) {
//
//	while (!IsEmpty(q)) {
//
//		cout << Dequeue(q) << " ";
//		if (success_code == DEQUEUE_FAIL_ERROR) {
//
//			success_code = DESTROY_FAIL_ERROR;
//			break;
//
//		}
//
//	}
//
//	cout << endl;
//
//}

void PrintQueue(queue_t q) {

	for (int i = 0; i < q.size; ++i) {

		cout << q.arr[i] << " ";

	}

	cout << endl;

}

void temp(){

	queue_t q;
	int x;
	while (cin.peek() != '\n') {

		cin >> x;
		Enqueue(q, x);

	}

	Dequeue(q);

	PrintQueue(q);

}