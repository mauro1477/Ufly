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
    adj = new MatNode** [n];
    for (int i = 0; i < n; i++)
    {
        adj[i] = new MatNode* [n];
        for(int j = 0; j < n; j++)
        {
            MatNode *newnode = new MatNode;
            *newnode = { "", "", 0.0, 0.0 };
            adj[i][j] = newnode;
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
    hashValue %= numCities;

    return hashValue;
}

//Switching the edge from '0' to '1' between an origin 
//and destination
void Matrix::addEdge(double miles, string _origin, string _destination)
{   
    string lower = _origin;
    int i = 0;
    while (lower[i])
    {
        lower[i] = tolower(lower[i]);
        i++;
    }
    _origin = lower;
    lower = _destination;
    i = 0;
    while (lower[i])
    {
        lower[i] = tolower(lower[i]);
        i++;
    }
    _destination = lower;

    int oIndx = getHash(_origin);
    int dIndx = getHash(_destination);
    int track = 0;
    // cout << "inindx " << oIndx << ", ";
    while (adj[oIndx][dIndx]->orig_Name != "" && track < numCities)
    {
        if (dIndx == numCities-1)
        {
            dIndx = 0; track++;
        }
        else
        {
            dIndx++; track++;
        }  
        if (adj[oIndx][dIndx]->orig_Name != "" && track == numCities-1)
        {
            track = 0;

            if (oIndx == numCities-1)
            {
                oIndx=0;
            }
            else
            {
                oIndx++;
            }
        }
    }

    track = 0;

    while (adj[oIndx][dIndx]->dest_Name != "" && track < numCities)
    {
        if (oIndx == numCities-1)
        {
            oIndx = 0;
            track++;
        }
        else
        {
            oIndx++; track++;
        }
    } 
    if (adj[oIndx][dIndx]->dest_Name == "")
    {
        double price = (miles / 483.00) * COST;
        MatNode *newnode = new MatNode;
        *newnode = { _origin, _destination, miles, price };
        adj[oIndx][dIndx] = newnode;
    }
}

MatNode *Matrix::findNode(string _origin, string _destination)
{
    int oIndx = getHash(_origin);
    int dIndx = getHash(_destination);
    int track = 0; string low;

    if (adj[oIndx][dIndx]->orig_Name == "")
    {
        return nullptr;
    }
    else
    {
        do
        {
            low = adj[oIndx][dIndx]->dest_Name;
            int i = 0;
            while(low[i])
            {
                low[i] = tolower(low[i]);
                i++;
            }
            if (low != _destination)
            {
                if (dIndx == numCities-1)
                {
                    dIndx = 0; track++;
                }
                else
                {
                    dIndx++; track++;
                }

                if (adj[oIndx][dIndx]->orig_Name != "" && track == numCities-1)
                {
                    track = 0;

                    if (oIndx == numCities-1)
                    {
                        oIndx=0;
                    }
                    else
                    {
                        oIndx++;
                    }
                }
            }
            else
            {
                track = 0;
                break;
            }
            

        } while (track < numCities);

        do
        {
            low = adj[oIndx][dIndx]->orig_Name;
            int i = 0;
            while(low[i])
            {
                low[i] = tolower(low[i]);
                i++;
            }
            if (low == _origin)
            {
                return adj[oIndx][dIndx];
            }
            else if (oIndx == numCities-1)
            {
                oIndx = 0; track++;
            }
            else
            {
                oIndx++; track++;
            }
        } while (track < numCities);
    }
    return nullptr;
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
        int count = 0;
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

                pos2++;
                count++;
                addEdge(costCalc, origin, destination);  

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
        cout << "i " << i << " ";
        for(j = i; j < numCities; j++)
        {
            cout << adj[i][j]->orig_Name << "->" << adj[i][j]->dest_Name;
        }
        cout<<endl << endl;
    }
}

void Matrix::displaySpecific(string _origin, string _destination)
{
    MatNode *curr = findNode(_origin, _destination);

    if (curr == nullptr)
    {
        cout << "City not found in database" << endl;
    }
    else
    {
        cout << "$" << fixed << setprecision(2);
        cout << curr->price << " for ";
        cout << _origin << " to " << _destination << endl;
    }
}
