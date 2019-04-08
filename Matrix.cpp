#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <limits>//for numeric_limits
#include <cstdlib>
#include <locale>//

using namespace std;

Matrix::Matrix(int n)
{
    numCities = n;
    adj = new double* [n];
    for (int i = 0; i < n; i++)
    {
        adj[i] = new double [n];
        for(int j = 0; j < n; j++)
        {
            adj[i][j] = 0;
        }
    }
}

//0(1) hash table
unsigned int Matrix::getHash(std::string word)
{
    unsigned int hashValue = 5381; int length = word.length();
    
    for (int i = 0; i < length; i++)
    {
        hashValue=((hashValue<<5)+hashValue) + word[i];
    }
    hashValue %= HASHTABLESIZE;
    
    return hashValue;
}

void Matrix::put(string city, int adjIndx)
{
    int hashIndx = getHash(city);
    
    location *newnode = new location;
    hashPlaceTable[ hashIndx ];
    
    newnode->next = nullptr;
    newnode->name = city;
    newnode->indx = adjIndx;
    
    if ( hashPlaceTable[ hashIndx ] == nullptr )
    {
        head = newnode;
    }
    else
    {
        location *curr = hashPlaceTable[ hashIndx ];
        
        while ( curr != nullptr )
        {
            if ( curr->next == nullptr )
            {
                curr->next = newnode;
            }
            curr = curr->next}
    }
}

int Matrix::findAdjIndx(string city)
{
    int hashIndx = getHash(city);
    
    location *trav = hashPlaceTable[ hashIndx ];
    
    if ( trav == nullptr )
    {
        return -1;
    }
    else if ( trav->name == city )
    {
        return trav->indx;
    }
    else
    {
        while ( trav != nullptr )
        {
            if ( trav->name == city )
            {
                return trav->indx;
            }
            trav = trav->next;
        }
    }
    return -1;
}

//Switching the edge from '0' to '1' between an origin 
//and destination
void Matrix::addEdge(int _origin, int _destination, double miles)
{
    if (_origin > numCities || _destination > numCities || 
        _origin < 0 || _destination < 0)
    {
        cout << "Incorrect Edge Input" << endl;
    }
    else
    {
        adj[_origin-1][_destination-1] = (miles / 483.00) * COST;
    }
}

//Helper to find distance between two cities by lon/lat
static double haversine(double lat1, double lon1, 
                                double lat2, double lon2) 
{ 
    // distance between latitudes 
    // and longitudes 
    double dLat = (lat2 - lat1) * 
                3.14159 / 180.0; 
    double dLon = (lon2 - lon1) *  
                3.14159 / 180.0; 

    // convert to radians 
    lat1 = (lat1) * 3.14159 / 180.0; 
    lat2 = (lat2) * 3.14159 / 180.0; 

    // apply formula
    double a = pow(sin(dLat / 2), 2) +  
            pow(sin(dLon / 2), 2) *  
            cos(lat1) * cos(lat2); 
    double rad = 6371; 
    double c = 2 * asin(sqrt(a)); 
    
    //if plane queue from pos1 to pos2
    //still has available planes, then return weight
    //else call function to switch to zero
    
    return (rad * c) / 1.609; 
}

//Helper to go to specific line in file
ifstream& GotoLine(ifstream& inFile, unsigned int num)
{
    inFile.seekg(std::ios::beg);
    
    for(int i=0; i < num - 1; ++i)
    {
        inFile.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return inFile;
}

void Matrix::inMatrix(string fileName)
{
    
    cout << endl << "LOADING COST MATRIX..." << endl << endl;
    
    ifstream inFile(fileName);
    
    if (inFile.is_open())
    {
        int pos1 = 0, pos2 = 0;
        double costCalc = 0.0;

        string lat1, lat2, lon1, 
                lon2, minlon1, minlat1, 
                minlon2, minlat2, origin, 
                state1, destination, state2;
        
        while (getline(inFile, origin, ','))
        {
            
            inFile>>state1>>lat1
            >>minlat1>>lon1>>minlon1;
            
            pos1++;
            // pos2 = pos1; //If the graph is symmetric
            pos2 = 0;
            GotoLine(inFile, pos2+1);//gotoline to iterate from 0 pos in file for complete graph (asymmetric)
            while (getline(inFile, destination, ','))
            {
                inFile>>state2>>lat2
                >>minlat2>>lon2>>minlon2;

                costCalc = haversine(stod(lat1)+(stod(minlat1)/60.0),
                                    stod(lon1)+(stod(minlon1)/60.0),
                                    stod(lat2)+(stod(minlat2)/60.0),
                                    stod(lon2)+(stod(minlon2)/60.0));

                // if (origin == "Denver")
                // {
                    // cout << origin << ", ";
                    // cout << lat1 << ", " << minlat1 << ", ";
                    // cout << lon1 << ", " << minlon1 << ", " << endl;
                    // cout << destination << ", ^^";
                    // cout << lat2 << ", " << minlat2 << ", ";
                    // cout << lon2 << ", " << minlon2 << endl;
                    // cout << "-- " << pos1 << ", " << pos2 << endl;
                    // cout << "miles: " << costCalc << endl;
                    // cout << "maths: " << (costCalc/483) * COST << endl << endl;
                // }

                pos2++;
                addEdge(pos1, pos2, costCalc);  
                GotoLine(inFile, pos2+1);//gotoline to iterate from 0
            }
            inFile.clear();
            GotoLine(inFile, pos1+1);
        }
        inFile.close();
    }
    else
    {
        cout << "error matrix file" << endl;
    }
}

void Matrix::displayAll()
{
    int i,j;
    for(i = 0;i < numCities;i++)
    {
        for(j = 0; j < numCities; j++)
        {
            // if (adj[i][j] != 0)
                cout<<" $"<<adj[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void Matrix::displaySpecific(int _origin, int _destination)
{
    ifstream inFile("testfile.txt");
    string orig, dest;

    if (inFile.is_open())
    {
        GotoLine(inFile, _origin);
        getline(inFile, orig, ',');
        GotoLine(inFile, _destination);
        getline(inFile, dest, ',');
    }
    else
    {
        cout << "error file" << endl;
    }

    if (_origin > _destination)
    {
        int temp = _origin;
        _origin = _destination;
        _destination = temp;
    }

    cout << "$" << fixed << setprecision(2);
    cout << adj[_origin-1][_destination-1] << " for ";
    cout << orig << " to " << dest << endl;

    inFile.close();
}

int Matrix::find(string city)
{
    string line; int count = 1;
    ifstream inFile("testfile.txt");
    
    if (inFile.is_open())
    {
        while(getline(inFile, line, ','))
        {
            int i = 0;
            while (line[i])
            {
                line[i] = tolower(line[i]);
                i++;
            }
            if (line == city)
            {
                inFile.close();
                return count;
            }
            else
            {
                count++;
                getline(inFile, line);
            }
        }
    }
    else
    {
        cout << "error file" << endl;
    }
    inFile.close();
    return -1;
}
