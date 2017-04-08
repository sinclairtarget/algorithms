#include <iostream>
#include <vector>
#include <string>

#include "stack.h"
#include "stack.cpp"

using std::vector;
using std::cout;
using std::endl;
using std::string;

int main()
{
    Stack<int> stack;

    stack.Push(1);
    cout << stack.ToString() << endl;

    stack.Push(2);
    cout << stack.ToString() << endl;

    stack.Push(3);
    cout << stack.ToString() << endl;

    int popped = stack.Pop();
    cout << popped << endl;
    cout << stack.ToString() << endl;

    popped = stack.Pop();
    cout << popped << endl;
    cout << stack.ToString() << endl;

    popped = stack.Pop();
    cout << popped << endl;
    cout << stack.ToString() << endl;

    return 0;
}
