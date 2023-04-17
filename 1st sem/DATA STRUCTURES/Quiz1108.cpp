#include <iostream>

#define MAX_SIZE 5

using namespace std;

class Queue_1
{
private:
    int myqueue[MAX_SIZE], front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }
    bool is_full()
    {
    if(front == 0 && rear == MAX_SIZE - 1)
        return true;
    else return false;
    }
    bool is_empty()
    {
    if(front == -1)
        return true;
    else return false;
}

void enqueue(int value)
{
    if(is_full())
    cout << endl << "QUEUE IS FULL!";
    else
    {
    if(front == -1) front = 0;
    rear++;
    myqueue[rear] = value;
    cout << value << " ";
    }
}

int dequeue()
{
    int value;
    if(is_empty())
    {
        cout << "QUEUE IS EMPTY!" << endl;
            return(-1); }
    else
    {
        value = myqueue[front];
        if(front >= rear)
            {
                front = -1;
            rear = -1;
            }
    else
        front++;
    return(value);
    }
}

void display()
{
    int i;
    if(is_empty())
    cout << endl << "QUEUE IS EMPTY!" << endl;
    else
        {
        cout << endl << "Queue Elements : ";
        for(i = front; i <= rear; i++)
        cout << myqueue[i] << "\t";
        }
}
};

int main()
{
    Queue_1 que;
    int choice, flag = 1, value;

    while( flag == 1)
    {
        cout << "\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cin >> choice;

    switch (choice)
        {
        case 1:
            cout<<"Enter Value:\n";
            cin>>value;
            que.enqueue(value);
            break;

        case 2:
            que.dequeue();
            break;

        case 3:
            que.display();
            break;

        case 4:
            flag = 0;
            break;
        }
    }
return 0;
}
