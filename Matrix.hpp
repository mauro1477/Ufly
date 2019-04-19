#pragma once
#include <iostream>
using std::string;

class MatNode
{
    public:
        string orig_Name;
        string dest_Name;
        double distance;
        double price;
};

class Matrix
{
    public:
        //Parameterized constructor to set all vals to zero in adjacency matrix
        Matrix(int n);
        //Switching the edge from '0' to '1' between an origin and destination
        // void addEdge(int _origin, int _destination);
        // void addEdge(int, int, double, string, string);  
        //-----------------------------------------------------------------------------------
        //I WILL GO BACK THROUGH AND COMMENT EACH FUNCTION SO THEY ARE UNDERSTANDABLE - WAYNE
        void inMatrix(string fileName);
        void addEdge(double miles, string _origin, string _destination);
        MatNode *findNode(string origin, string destination);
        void displayAll();
        void displaySpecific(string _origin, string _destination);
        unsigned int getHash(std::string word);
        
    private:
        // int numPlanes;
        int numCities;
        int matrixValues;
        // int size;
        MatNode ***adj;
        
        const double COST = 7000.00; //$7000 is the avg cost of a private jet that can go across the united states
                                    //we can change this to whatever seems appropriate or randomize in the future
};

