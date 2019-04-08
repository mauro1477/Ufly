#include "login.hpp"
#include <iostream>
#include <string>
using namespace std;

bool Login::isCollision()
{
    
}

Users* Login::signUp(string u, string p)
{
    if (isCollision())
    {
        cout << "Username is already taken. Please enter a different username." << endl;
    }
    else
    {
        username = u;
        password = p;
    }
}
