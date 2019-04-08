#include <iostream>
#include <locale>
#include <string>
#include "Matrix.hpp"
#include "ClientQueue.hpp"
#include "login.hpp"
using namespace std;
bool loginDisplay();
void display();

int main(int argc, char const* argv[])
{
    ClientQueue cq;
    
    //maybe argv[1] can be "n"? not settled for now.
    // Matrix(argv[1]);
    
    
    //***THIS IS WHAT I USED TO TEST - NOT THE FINAL DRIVER***
    bool resultLogin = false;
    string from, to;
    int home = 0, travel = 0;
    //constructed with 117, take number of lines in file and add one
    Matrix mat(5);
    mat.inMatrix("testfile.txt");
    //mat.display displays the entire matrix..
    //matrix is half due to symmetry but will be changed due to
    //plane availability
    mat.displayAll();
    // resultLogin = loginDisplay();//have user login
    // if(resultLogin = true)//if its true the user has locked him self out 
    // {
    //     return 0;//end the program
    // }
    cout << "Where are you coming from?" << endl;
    getline(cin, from);
    cout << "Where would you like to travel?" << endl;
    getline(cin, to);
    
    //while loops make it so it is not cap-sensitive
    int i = 0;
    while(from[i])
    {
        from[i] = tolower(from[i]);
        i++;
    }
    i = 0;
    while(to[i])
    {
        to[i] = tolower(to[i]);
        i++;
    }
    home = mat.find(from);
    travel = mat.find(to);
    
    if (home == -1 || travel == -1)
    {
        cout << "One or both cities are not in the directory" << endl;
    }
    else
    {
        cout << endl;
        mat.displaySpecific(home, travel);
    }
    
    //******************************************************
    
    return 0;
}

void display()
{
    cout << "Main Menu" << endl; //not the final implementation!! just an idea of what we might need
    cout << "1. Choose Location" << endl;
    cout << "2. Choose Destination" << endl;
    cout << "3. Quit" << endl;
}

bool loginDisplay()
{
    string userName;
    string userPassword;
    int loginAttempt = 0;//Keep track of attempts loggin in
    
    while(loginAttempt != 5)
    {
        if (userName ==  && userPassword == )
        {
            cout << "Welcome Name!\n";
            return false;//if its true continue the program
        }
        else
        {
            cout << "Invalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
        if (loginAttempt == 5)
        {
            cout << "Too many login attempts! The program will now terminate.";
            return true;//if its false terminate the program in main
        }
    }
}
