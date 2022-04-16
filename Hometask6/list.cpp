//
// Created by danya on 14.04.2022.
//
#include "list.h"
#include <iostream>
//#include <algorithm>

using namespace std;

#define MALLOC_FAIL_ERROR -1
#define PUSHBACK_FAIL_ERROR -2
#define EMPTY_LIST_ERROR -3

struct list {

    int data = 0;
    List_t* next = NULL;

};

void PushBack(List_t*& head, int num) {     // Push into the end of the list

    try {

        List_t *new_node = (List_t *) (malloc(sizeof(List_t)));       // Creating new node, which will pe pushed back
        if (new_node == NULL) throw MALLOC_FAIL_ERROR;      // If malloc failed
        new_node->data = num;
        new_node->next = NULL;

        if (head == NULL) {      // If list is empty

            head = new_node;

        } else {

            List_t *temp = head;
            while (temp->next != NULL) temp = temp->next;     // Go to the end of the list
            temp->next = new_node;

        }

    }catch(int error) {

        throw PUSHBACK_FAIL_ERROR;

    }

}

void DeleteByValue(List_t*& head, int value) {    // Deleting node with her number

    if(head == NULL) throw EMPTY_LIST_ERROR;

    List_t* temp = head;

    if(temp->data == value) {      // Deleting the head of the list

        head = head->next;

    }else {

        while (temp != NULL && temp->next != NULL) {

            if (temp->next->data == value) {

                //free(temp->next);
                temp->next = temp->next->next;

            }else temp = temp->next;

        }

    }

}

int FindMax(List_t*& head) {     // Searching for max and min elements of the list

    if(head == NULL) throw EMPTY_LIST_ERROR;

    int max = -1e10;
    List_t* temp = head;

    while(temp->next != NULL) {

        if(temp->data > max) max = temp->data;
        temp = temp->next;

    }

    if(temp->data > max) max = temp->data;      // Checking the last element
    return max;

}

int FindMin(List_t*& head) {     // Searching for max and min elements of the list

    if(head == NULL) throw EMPTY_LIST_ERROR;

    int min = 1e10;
    List_t* temp = head;

    while(temp->next != NULL) {

        if(temp->data < min) min = temp->data;
        temp = temp->next;

    }

    if(temp->data < min) min = temp->data;      // Checking the last element
    return min;

}

void SwapMaxAndMin(List_t*& head) {

    if(head == NULL) throw EMPTY_LIST_ERROR;

    List_t* max = head;
    //max->data = -1e10;

    List_t* min = head;
    //min->data = 1e10;

    List_t* temp = head;

    while(temp->next != NULL) {     // Searching for max and min

        if(temp->data > max->data) max = temp;
        if(temp->data < min->data) min = temp;
        temp = temp->next;

    }

    if(temp->data > max->data) max = temp;      // Checking the last element
    if(temp->data < min->data) min = temp;

    //cout << "BEFORE_SWAP " << "Max elem is " << max->data << ". Min elem is " << min->data << endl;

    auto max_ptr = max->next;
    auto min_ptr = min->next;

    temp = head;
    // Swapping max and min
    if(temp == max) {       // Check, if the head is max

        head = min;
        head->next = max_ptr;

    } else if(temp == min) {        // Check, if the head is min

        head = max;
        head->next = min_ptr;

    }

    while(temp->next != NULL) {

        if(temp->next == max) {

            temp->next = min;
            min->next = max_ptr;

        } else if(temp->next == min) {

            temp->next = max;
            max->next = min_ptr;

        }

        temp = temp->next;

    }

    //cout << "AFTER_SWAP " << "Max elem is " << max->data << ". Min elem is " << min->data << endl;

}

void PrintListReverse(List_t* head) {

    if(head == NULL) throw EMPTY_LIST_ERROR;
    if(head->next != NULL) {

        PrintListReverse(head->next);

    }
    cout << head->data << " ";

}

void PrintList(List_t* head) {

    List_t* temp = head;
    while(temp != NULL) {

        cout << temp->data << " ";
        temp = temp->next;

    }

    cout << endl;

}