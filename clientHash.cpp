#include "ClientHash.hpp"
#include <stdlib.h>
#include<list>//libary for linked list
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

HashTable::HashTable(int hashTableSize)//
{
  this->hashTableSize = hashTableSize;
  hashTable = new client*[hashTableSize];
  for(int i = 0; i<hashTableSize; i++)
  {
      hashTable[i] = NULL;
  }
  numCollisions = 0;
  numItems = 0;
}

HashTable::~HashTable()
{
  for(int i = 0; i < hashTableSize; i++)
  {
    client* newNode = hashTable[i];
    while (newNode != NULL)
    {
      newNode = newNode->next;
      delete newNode;
    }
  }
}

void HashTable::incrementCount(string word)
{
  searchTable(word)->count++;
}

void HashTable::addClient(string _IDNumber, string _name, string _password, string _passengerNum, string _orgin)
{
  cout<<"ID Number"<<_IDNumber<<endl;
  int _IDNumber1 = stoi(_IDNumber);
  int _passengerNum1 = stoi(_passengerNum);

  cout<<"Hello"<<_passengerNum1<<endl;

  int hashName = getHash(_name);
  client* pointTemp = hashTable[hashName];
  if(pointTemp == NULL)
  {
      cout<<"Hello addClient"<<endl;
      hashTable[hashName] = new client;
      hashTable[hashName]->IDNumber = _IDNumber1;
      hashTable[hashName]->name = _name;
      hashTable[hashName]->passWord = _password;
      hashTable[hashName]->passengerNum = _passengerNum1;
      hashTable[hashName]->orgin = _orgin;
      hashTable[hashName]->next = NULL;
  }
  else
  {
    cout<<"Hello else"<<endl;
      client* temp = new client;
      temp->IDNumber = _IDNumber1;
      temp->name = _name;
      temp->passWord = _password;
      temp->passengerNum = _passengerNum1;
      temp->orgin = _orgin;
      temp->next = hashTable[hashName];
      hashTable[hashName] = temp;
      numCollisions++;
  }
  numItems++;
}

//Using your search Table fuction for the wordItem containgin word. Return true
//if it is found, otherwise return false.
bool HashTable::isInTable(string word)
{
  client* result = searchTable(word);

  if(result == NULL)
  {
    return false;
  }
  else
  {
    return true;
  }
}



int HashTable::getTotalNumWords()
{
  int sum = 0;
  for (int i = 0; i < hashTableSize; i++)
  {
    client* newNode = hashTable[i];//head of the table
    if(newNode != NULL)
    {
      while(newNode != NULL)
      {
          sum = sum + newNode->count;
          newNode = newNode->next;
      }
    }
  }
  return sum;
}

unsigned int HashTable::getHash(string word)
{
  unsigned int hashValue = 5381;
  int length = word.length();
  for(int i = 0; i < length; i++)
  {
    hashValue = ((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}

client* HashTable::searchTable(string word)
{
  client* temp = hashTable[getHash(word)];
  while(temp != NULL && temp->name != word)
  {
    temp = temp->next;
  }
  return temp;
}

int HashTable::getNumCollisions()
{
  return numCollisions;
}

int HashTable::getNumItems()
{
  return numItems;
}


void getClient(HashTable &clientTable)
{
  cout<<"Hello getClient"<<endl;
  ifstream myfile("ClientList.csv");

  string line, IDNumber, name, password, passengerNum, orgin;
  if(myfile.is_open())
  {
      cout<<"Hello getClient"<<endl;
    while(getline(myfile, line))
    {
      stringstream ss(line);
      getline(ss, IDNumber, ',');
      getline(ss, name, ',');
      getline(ss, password, ',');
      getline(ss, passengerNum, ',');
      getline(ss, orgin, ',');
      cout<<IDNumber<<endl;
      cout<<name<<endl;
      cout<<password<<endl;
      cout<<passengerNum<<endl;
      cout<<orgin<<endl;
      clientTable.addClient(IDNumber, name, password, passengerNum, orgin);
    }
  }
  else
  {
    cout<<"File not open"<<endl;
  }
  myfile.close();
}

int main(int argc, char* argv[])
{
  HashTable Client(CLIENT_TABLE_SIZE);
  getClient(Client);
  return 0;
}
