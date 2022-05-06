//
// Created by danya on 29.04.2022.
//

#include "tree.h"
#include <iostream>

//using namespace std;

typedef struct tree_node {

    int value = 0;
    tree_node_t* left = NULL;
    tree_node_t* right = NULL;

}tree_node_t;

void Insert(tree_node_t*& current_tree_node, int value) {

    if(current_tree_node == NULL) {

        current_tree_node = (tree_node_t*)malloc(sizeof(tree_node_t));
        current_tree_node->left = NULL;
        current_tree_node->right = NULL;
        current_tree_node->value = value;

    }else {

        if(value < current_tree_node->value) Insert(current_tree_node->left, value);
        else if(value > current_tree_node->value) Insert(current_tree_node->right, value);

    }

}

tree_node_t* FindMin(tree_node_t* current_tree_node) {

    if(current_tree_node->left != NULL) return FindMin(current_tree_node->left);
    return current_tree_node;

}

void DeleteByValue(tree_node_t*& current_tree_node, int value) {

    if(current_tree_node->value == value) {         // Deleting root

        if(current_tree_node->right != NULL) {

            current_tree_node->value = FindMin(current_tree_node->right)->value;
            DeleteByValue(current_tree_node->right, current_tree_node->value);

        }else if(current_tree_node->left != NULL && current_tree_node->right == NULL) {

            current_tree_node->value = FindMin(current_tree_node->left)->value;
            DeleteByValue(current_tree_node->left, current_tree_node->value);

        }else if(current_tree_node->left == NULL && current_tree_node->right == NULL) {

            current_tree_node = NULL;

        }

    } else if (value < current_tree_node->value) {

        if (current_tree_node->left->value == value) {           // If the next element is desired (current_left is desired)

            //if((current_tree_node->left != NULL && current_tree_node->right != NULL) || (current_tree_node->right != NULL && current_tree_node->left == NULL)) {
            if(current_tree_node->left->right != NULL) {

                current_tree_node->left->value = FindMin(current_tree_node->left->right)->value;        // Replacing desired value with minimal from its right subbranch
                DeleteByValue(current_tree_node->left->right,current_tree_node->left->value);               // Deleting element with replaced value

            }else if(current_tree_node->left->left != NULL && current_tree_node->left->right == NULL) {

                current_tree_node->left->value = FindMin(current_tree_node->left->left)->value;         // Replacing desired value with minimal from its left subbranch
                DeleteByValue(current_tree_node->left->left, current_tree_node->left->value);               // Deleting element with replaced value

            }else if(current_tree_node->left->left == NULL && current_tree_node->left->right == NULL) {               // When element with desired value has no kids

                current_tree_node->left = NULL;                                                                      // Just delete it

            }

        } else {

            DeleteByValue(current_tree_node->left, value);      // Moving to the next element

        }

    } else if (value > current_tree_node->value) {

        if (current_tree_node->right->value == value) {

            if(current_tree_node->right->right != NULL) {

                current_tree_node->right->value = FindMin(current_tree_node->right->right)->value;      // Replacing desire value with minimal from its right subbranch
                DeleteByValue(current_tree_node->right->right,current_tree_node->right->value);             // Deleting element with replaced value

            }else if(current_tree_node->right->left != NULL && current_tree_node->right->right == NULL) {

                current_tree_node->right->value = FindMin(current_tree_node->right->left)->value;       // Replacing desired value with minimal from its left subbranch
                DeleteByValue(current_tree_node->right->left, current_tree_node->right->value);             // Deleting element with replaced value

            }else if(current_tree_node->right->left == NULL && current_tree_node->right->right == NULL) {           // When element with desired value has no kids

                current_tree_node->right = NULL;                                                                    // Just delete it

            }

        } else {

            DeleteByValue(current_tree_node->right, value);     // Moving to the next element

        }

    }

}

void PrintInWidth(tree_node_t*& current_tree_node) {

    queue_t q;
    Enqueue(q, current_tree_node);

    while(!IsEmpty(q)) {

        Enqueue(q, current_tree_node->left);
        std::cout << Dequeue(q)->value << " ";

    }

}