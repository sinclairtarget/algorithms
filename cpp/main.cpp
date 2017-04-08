#include <iostream>
#include <vector>
#include <string>

#include "linked_list.h"
#include "linked_list.cpp"

using std::vector;
using std::cout;
using std::endl;
using std::string;

int main()
{
    ListNode<int>* listHead = new ListNode<int>(23);
    listHead = listHead->Prepend(21);
    cout << listHead->ListToString() << endl;

    listHead->InsertAfter(22);
    cout << listHead->ListToString() << endl;

    listHead = listHead->Reverse();
    cout << listHead->ListToString() << endl;

    return 0;
}
