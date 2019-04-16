#pragma once
#include <iostream>
using std::string;

const int HASHTABLESIZE = 30;

struct location
{
    string place_name;
    int indx;
    location *next;
};

class Matrix
{
    public:
        //Parameterized constructor to set all vals to zero in adjacency matrix
        Matrix(int _n);
        //Switching the edge from '0' to '1' between an origin and destination
        void addEdge(int _origin, int _destination);
        //-----------------------------------------------------------------------------------
        //I WILL GO BACK THROUGH AND COMMENT EACH FUNCTION SO THEY ARE UNDERSTANDABLE - WAYNE
        void inMatrix(string fileName);
        void addEdge(int _origin, int _destination, double miles);
        void displayAll();
        void displaySpecific(int _origin, int _destination);
        int findAdjIndx(string city);
        void put(string city, int adjIndx);
        unsigned int getHash(std::string word);
        int find(string city);
        
    private:
        int numPlanes;
        int numCities;
        int matrixValues;
        //adj matrix below
        int size;
        double **adj;
        //hash table below
        location *hashPlaceTable[20];
        location *head;
        
        const double COST = 7000.00; //$7000 is the avg cost of a private jet that can go across the united states
                                    //we can change this to whatever seems appropriate or randomize in the future
};

