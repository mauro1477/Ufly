#pragma once
#include <string>
#include <vector>
using std::string;

struct CNode
{
    int ID;
    string name;
    int orig, destin, numPeople;
    int position; //stores the position in queue, nodes are added to the end and removed from the front
    CNode *next;
};

class ClientQueue
{
    public:
        ClientQueue();
        ~ClientQueue();
        void enqueue(CNode *client); //onto tail
        void dequeue(); //remove head
        CNode *getHead() { return head; }
        CNode *getTail() { return tail; }
        
    private:
        CNode *head, *tail;
        vector<CNode> clientList;
};
