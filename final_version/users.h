#ifndef USERS_H
#define USERS_H
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

class Users {
public:
    Users();
    Users(const string& userID, const string& userName, const string& userPassword, unsigned int userRole);
    virtual ~Users();

    string getUserID() const;
    string getUserName() const;
    string getUserPassword() const;
    unsigned int getUserRole() const;

    void setUserID(const string& userID);
    void setUserName(const string& userName);
    void setUserPassword(const string& userPassword);
    void setUserRole(unsigned int userRole);

    void manageAccount(vector<Users>& users);
    
private:
    string userID;
    string userName;
    string userPassword;
    unsigned int userRole;
};

#endif // USERS_H
