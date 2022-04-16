#include <iostream>
#include "list.cpp"

using namespace std;

int main() {
    List_t *list = NULL;
    int x, menu;

    try {

        cout << "Enter list elements:";
        while (cin.peek() != '\n') {

            cin >> x;
            PushBack(list, x);

        }

        do {

            cout << "\nChoose an action\n" <<
                 "1 - Find all elements with inputted value and delete them from the list\n" <<
                 "2 - Find min and max elements of the list\n" <<
                 "3 - Swap max and min elements\n" <<
                 "4 - Print list and reversed list\n" <<
                 "5 - Print list\n" <<
                 "0 - Exit\n";

            cin >> menu;
            switch (menu) {

            case 1:
                cout << "Input the value: ";
                cin >> x;
                DeleteByValue(list, x);
                PrintList(list);
                break;

            case 2:
                x = FindMax(list);
                cout << "Max elem is " << x << endl;
                x = FindMin(list);
                cout << "Min elem is " << x << endl;
                break;

            case 3:
                SwapMaxAndMin(list);
                PrintList(list);
                break;

            case 4:
                cout << "Normal list: ";
                PrintList(list);
                cout << "Reversed list: ";
                PrintListReverse(list);
                cout << endl;
                break;

            case 5:
                PrintList(list);
                break;

            case 0:
                break;

            default:
                cout << "Wrong input. Try again" << endl;
                break;

            }

        } while (menu != 0);

    }catch (int error) {

        switch(error) {

        case PUSHBACK_FAIL_ERROR:
            cout << "ERROR. Pushback failed" << endl;
            break;

        case MALLOC_FAIL_ERROR:
            cout << "ERROR. Malloc failed" << endl;
            break;

        case EMPTY_LIST_ERROR:
            cout << "ERROR. List is empty" << endl;
            break;

        }

    }

}
