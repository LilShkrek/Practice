#include <iostream>
//#include <windows.h>
//#include "Queue.h"
#include "Queue.cpp"

using namespace std;

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
    catch (int error) {		// Catching DEQUEUE_FAIL_ERROR

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

void task5(queue_t& q) {    // Delete the tail of the queue

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
        task5(copy_q);		// ������� "�����" �������
        Dequeue(copy_q);	// ������� "������" �������

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

int main() {

    /*setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001");*/
    queue_t q;
    int x, menu;

    try {

        cout << "Enter elements of queue\n";

        while (cin.peek() != '\n') {

            cin >> x;
            Enqueue(q, x);

        }

        do {

            cout << "\nChoose an action:\n1 - Clean the queue\n2 - Add to queue\n3 - Remove from queue\n\
4 - Place 0 after each element of queue. For example: 1, 2, 3 -> 1, 0, 2, 0, 3, 0\n\
5 - Delete the last element of queue (tail)\n6 - Swap the first and the last elements of the queue\n\
0 - Close programm\n";
            cin >> menu;

            switch (menu) {

                case 1:
                    Destroy(q);
                    break;

                case 2:
                    cout << "Enter the num, you want to add: ";
                    cin >> x;
                    Enqueue(q, x);
                    PrintQueue(q);
                    break;

                case 3:
                    cout << "The \"head\" of the queue - " << Dequeue(q) << endl;
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
                    cout << "Wrong input. Try again\n";

            }

        } while (menu != 0);

    }
    catch (int error) {

        PrintError(error);

    }

}