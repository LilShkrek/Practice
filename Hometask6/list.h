//
// Created by danya on 14.04.2022.
//

#ifndef HOMETASK6_LIST_H
#define HOMETASK6_LIST_H

struct list;
typedef struct list List_t;

void PushBack(List_t*&, int);
void DeleteByValue(List_t*&, int);
int FindMax(List_t*&);
int FindMin(List_t*&);
void SwapMaxAndMin(List_t*&);
void PrintListReverse(List_t*);
void PrintList(List_t*);

#endif //HOMETASK6_LIST_H
