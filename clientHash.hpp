#ifndef CLIENT_HASH
#define CLIENT_HASH
#include <string>
using namespace std;
// struct to store word + count combinations
struct client//Client
{
    int count;
    int IDNumber;
    string name;
    string passWord;
    int passengerNum;
    string orgin;
    client* next;
};

class HashTable {
  public:
    HashTable(int hashTableSize);
    ~HashTable();
    void addClient(int IDNumber, string name, string password, int passengerNum, string orgin);
    bool isInTable(string word);
    void incrementCount(string word);
    int getNumCollisions();
    int getNumItems();
    int getTotalNumWords();



  private:
    /* member functions */
    unsigned int getHash(string word);
    client* searchTable(string word);

    /* instance variables */
    client** hashTable;
    int hashTableSize;
    int numCollisions;
    int numItems;
};


/* size to make your stopwords hash table */
const int CLIENT_TABLE_SIZE = 50;
void getClient(HashTable &clientTable);



#endif
