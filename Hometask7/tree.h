//
// Created by danya on 29.04.2022.
//

#ifndef HOMETASK7_TREE_H
#define HOMETASK7_TREE_H

#include "Queue.h"

struct tree_node;
typedef struct tree_node tree_node_t;

void Insert(tree_node_t*&, int);
tree_node_t* FindMin(tree_node_t*);
void DeleteByValue(tree_node_t*&, int);

#endif //HOMETASK7_TREE_H
