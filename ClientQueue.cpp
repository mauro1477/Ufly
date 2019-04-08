#include "ClientQueue.hpp"

ClientQueue::ClientQueue()
{
    head = tail = nullptr;
    
}

ClientQueue::~ClientQueue()
{
    CNode *curr = head, *prev = nullptr;
    
    while (curr != nullptr)
    {
        prev = head;
        curr = curr->next;
        delete prev;
    }
}

void ClientQueue::enqueue(CNode *client)
{
    client->next = nullptr;
    
    if (head == nullptr)
    {
        head = client;
        tail = client;
    }
    else
    {
        CNode *trav = tail;
        trav->next = client;
    }
}

void ClientQueue::dequeue()
{
    CNode *temp = head;
    head = head->next;
    delete temp;
}
