#include <iostream>
#include <vector>
#include <string>

#include "queue.h"
#include "queue.cpp"

using std::vector;
using std::cout;
using std::endl;
using std::string;

int main()
{
    Queue<int> queue;
    queue.Enqueue(1);
    cout << queue.ToString() << endl;

    queue.Enqueue(2);
    cout << queue.ToString() << endl;

    queue.Enqueue(3);
    cout << queue.ToString() << endl;

    int dequeued = queue.Dequeue();
    cout << dequeued << endl;
    cout << queue.ToString() << endl;

    dequeued = queue.Dequeue();
    cout << dequeued << endl;
    cout << queue.ToString() << endl;

    dequeued = queue.Dequeue();
    cout << dequeued << endl;
    cout << queue.ToString() << endl;

    return 0;
}
