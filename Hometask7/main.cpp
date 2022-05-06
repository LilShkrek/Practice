#include <iostream>
#include "tree.cpp"

using namespace std;

int main() {

    int x, menu;
    tree_node_t* tree = NULL;
//    Insert(tree, 5);
//    Insert(tree, 2);
//    Insert(tree, 7);
//    Insert(tree, 6);
//
//    cout << FindMin(tree)->value << endl;
//    DeleteByValue(tree, 7);

    auto a = &tree;
    cout << "AAA " << a << endl;


    cout << "Enter tree elements: ";
    while(cin.peek() != '\n') {

        cin >> x;
        Insert(tree, x);

    }

    cout << "\nChoose an action\n" <<
        "1 - Insert element\n" <<
        "2 - Delete element of the tree with inputted value\n" <<
        "3 - Print tree elements\n" <<
        "0 - Exit\n";
    cin >> menu;

    switch(menu) {

    case 1:     // Insert
        cout << "Input value, you want to insert: ";
        cin >> x;
        Insert(tree, x);
        break;

    case 2:     // Delete
        cout << "Input value: ";
        cin >> x;
        DeleteByValue(tree, x);
        break;

    case 3:
        cout << "Coming soon" << endl;
        break;

    case 0:
        break;

    default:
        cout << "Wrong input. Try again" << endl;
        break;

    }

}
