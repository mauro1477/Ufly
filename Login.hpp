#include <iostream>
using namespace std;

struct Users
{
    Users* username;
    Users* password;
    Users* firstName;
    Users* lastName;
};

class Login
{
    private:
        int numUsers;
    public:
       bool isCollision ();
       Users* signUp(string u, string p);
};
