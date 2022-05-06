//
// Created by danya on 06.05.2022.
//

#include <iostream>
#include "Queue.h"
#include <malloc.h>

using namespace std;

#define INIT_QUEUE 3
#define INC_QUEUE 3

#define PEAK_FAIL_ERROR -1
#define REALLOC_FAIL_ERROR -2
#define ENQUEUE_FAIL_ERROR -3
#define DEQUEUE_FAIL_ERROR -4
#define COPY_FAIL_ERROR -5

typedef struct tree_node {

    int value = 0;
    tree_node* left = NULL;
    tree_node* right = NULL;

}tree_node_t;

typedef int* arr_t;
typedef struct queue {

    //arr_t arr = (arr_t)malloc(INIT_QUEUE * sizeof(int));
    tree_node_t* arr = (tree_node_t*)malloc(INIT_QUEUE * sizeof(tree_node_t));
    int size = INIT_QUEUE;
    int head = -1;
    int tail = -1;

}queue_t;

tree_node_t Peak(queue_t q) {	// Return the "head" of the queue

    if (q.head < 0) {    // q.size < 1

        throw PEAK_FAIL_ERROR;

    }

    //success_code = OK_STATUS;
    return q.arr[q.head];

}

void CleanMem(queue_t& q) {		// Cleaning memory

    free(q.arr);
    q.arr = NULL;
    q.size = 0;
    q.head = 0;
    q.tail = 0;

}

bool IsEmpty(queue_t q) {	// Checking for empty queue

    try {

        tree_node_t temp = Peak(q);
        return false;

    }
    catch (int error) {		// Catching PEAK_FAIL_ERROR

        return true;

    }

}

void Reallocation(queue_t& q, int new_size) {		// Changing the amount of allocated memory for the queue

    tree_node_t* temp = (tree_node_t*)realloc(q.arr, new_size * sizeof(tree_node_t));

    if (temp == NULL && new_size != 0) {

        //success_code = REALLOC_FAIL_ERROR;
        throw REALLOC_FAIL_ERROR;

    }
    else {

        q.arr = temp;

        for (int i = q.size; i < new_size; ++i) {

            q.arr[i].value = 0;

        }

        q.size = new_size;
        //success_code = OK_STATUS;

    }

}

void Enqueue(queue_t& q, tree_node_t num) {		// Adding to the end of the queue

    try {

        if ((q.tail == q.head - 1) || (q.head == 0 && q.tail == q.size - 1)) {

            Reallocation(q, q.size + INC_QUEUE);

            if (q.tail == q.head - 1) {

                for (int j = 0; j < INC_QUEUE; ++j) {

                    for (int i = q.size + INC_QUEUE - 1; i > q.tail + 1; --i) {		// Moving the head away from the tail

                        q.arr[i] = q.arr[i - 1];

                    }

                    q.arr[q.tail + 1].value = 0;

                }

                q.head += INC_QUEUE;

            }

        }

        if (q.tail == -1) {

            for (int i = 0; i < INIT_QUEUE; ++i) q.arr[i].value = 0;	// Filling the empty queue with 0s

        }

        q.tail = (q.tail + 1) % q.size;		// Moving the "tail's" position
        q.arr[q.tail] = num;	// Changing the value of the "tail"

//        cout << "THAT'S A HEAD " << q.head << endl;
//        cout << "THAT'S A TAIL " << q.tail << endl;

        if (q.head == -1) q.head = 0;

    }
    catch (int error) {		// Catching REALLOC_FAIL_ERROR

        throw ENQUEUE_FAIL_ERROR;

    }

}

tree_node_t Dequeue(queue_t& q) {		// Removing the "head" of the queue

    try {

        tree_node_t first = Peak(q);
        if (q.head == q.tail) {		// Check if there is only 1 element in the queue

            q.arr[q.head].value = 0;
            q.head = -1;
            q.tail = -1;

        }
        else {

            q.arr[q.head].value = 0;
            q.head = (q.head + 1) % q.size;

        }

        return first;

    }
    catch (int error) {		// Catching PEAK_FAIL_ERROR

        throw DEQUEUE_FAIL_ERROR;

    }

}

void CreateCopy(queue_t old_q, queue_t& new_q) {

    try {

        Reallocation(new_q, old_q.size);
        for (int i = 0; i < new_q.size; ++i) {

            new_q.arr[i] = old_q.arr[i];

        }
        new_q.head = old_q.head;
        new_q.size = old_q.size;
        new_q.tail = old_q.tail;

    }
    catch (int error) {		// Catching REALLOC_FAIL_ERROR

        throw COPY_FAIL_ERROR;

    }

}

void PrintQueue(queue_t q) {

    for (int i = 0; i < q.size; ++i) {

        cout << q.arr[i].value << " ";

    }

    cout << endl;

}
