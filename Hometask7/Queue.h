//
// Created by danya on 06.05.2022.
//
#ifndef HOMETASK7_QUEUE_H
#define HOMETASK7_QUEUE_H

#define INIT_QUEUE 3
#define INC_QUEUE 3

typedef int* arr_t;
struct queue;
typedef struct queue queue_t;

struct tree_node;
typedef struct tree_node tree_node_t;

tree_node_t Peak(queue_t);
void CleanMem(queue_t&);
bool IsEmpty(queue_t);
void Reallocation(queue_t&, int);
void Enqueue(queue_t&, tree_node_t);
tree_node_t Dequeue(queue_t&);
void CreateCopy(queue_t, queue_t&);
void PrintQueue(queue_t);

#endif //HOMETASK7_QUEUE_H
