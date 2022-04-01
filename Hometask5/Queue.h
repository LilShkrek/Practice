#ifndef QUEUE_H
#define QUEUE_H

#define INIT_QUEUE 3
#define INC_QUEUE 3

typedef int* arr_t;
struct queue;
typedef struct queue queue_t;



int Peak(queue_t);
void CleanMem(queue_t&);
bool IsEmpty(queue_t);
void Reallocation(queue_t&, int);
void Enqueue(queue_t&, int);
int Dequeue(queue_t&);
void CreateCopy(queue_t, queue_t&);
void PrintQueue(queue_t);

#endif 
