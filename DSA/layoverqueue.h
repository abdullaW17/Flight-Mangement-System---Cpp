#ifndef LAYOVERQUEUE_H
#define LAYOVERQUEUE_H

#include <string>
#include <iostream>
using namespace std;

class Layover
{
public:
    string airline;
    string departureTime;
    string arrivalTime;
    int cost;

    Layover() 
    {
        airline = "";
        departureTime = "";
        arrivalTime = "";
        cost = 0;
    }

    Layover(string a, string dep, string arr, int c) 
    {
        airline = a;
        departureTime = dep;
        arrivalTime = arr;
        cost = c;
    }
};

class QueueNode
{
public:
    Layover data;
    QueueNode* next;

    QueueNode(Layover d) 
    {
        data = d;
        next = nullptr;
    }
};

class LayoverQueue
{
private:
    QueueNode* front;
    QueueNode* rear;

public:
    LayoverQueue() 
    {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(Layover layover);
    Layover dequeue();
    bool isEmpty() const;
    ~LayoverQueue();
};





#endif
