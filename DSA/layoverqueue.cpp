#include "layoverqueue.h"

LayoverQueue::~LayoverQueue() 
{
    while (front != nullptr) 
    {
        QueueNode* temp = front;
        front = front->next;
        delete temp;
    }
}

void LayoverQueue::enqueue(Layover layover) 
{
    QueueNode* newNode = new QueueNode(layover);
    if (rear == nullptr) 
    {
        front = rear = newNode;
    } 
    else 
    {
        rear->next = newNode;
        rear = newNode;
    }
}

Layover LayoverQueue::dequeue() 
{
    if (front == nullptr) 
    {
        cout << "Error: Queue is empty, cannot dequeue." << endl;
        return Layover();  // Return an empty Layover object if the queue is empty
    }

    QueueNode* temp = front;
    Layover data = front->data;
    front = front->next;
    if (front == nullptr) 
    {
        rear = nullptr;
    }
    delete temp;
    return data;
}

bool LayoverQueue::isEmpty() const 
{
    return front == nullptr;
}
