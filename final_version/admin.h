#ifndef ADMIN_H
#define ADMIN_H

#include "users.h"
#include "doctor.h"
#include "patient.h"
#include "assistant.h"

class Admin : public Users{
    private:
        string name;
        string DOB;
        string gender;
        string phoneNumber;
        string email;
        string address;
    public:
        Admin();
        ~Admin();
        Admin(const string&, const string&, const string&, unsigned int,
                  const string&, const string&, const string&,
                  const string&, const string&, const string&);

        static void showAccount(string);
        static void deleteAccount(string);
        static void createAccount(vector<Doctor>&, vector<Assistant>&);
        
};
#endif