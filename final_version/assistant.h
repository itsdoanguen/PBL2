#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "users.h"
#include "doctor.h"
#include "patient.h"

class Assistant : public Users {
    private:
        string name;
        string DOB;
        string gender;
        string phoneNumber;
        string email;
        string address;

    public:
        Assistant();
        Assistant(const string&, const string&, const string&, unsigned int,
                  const string&, const string&, const string&,
                  const string&, const string&, const string&);
        ~Assistant();

        // Get
        string getName() const;
        string getDOB() const;
        string getGender() const;
        string getPhoneNumber() const;
        string getEmail() const;
        string getAddress() const;

        // Set
        void setName(const string&);
        void setDOB(const string&);
        void setGender(const string&);
        void setPhoneNumber(const string&);
        void setEmail(const string&);
        void setAddress(const string&);

        // Member Functions
        void showAssistantInfo() const;
        void updateAssistantInfo(const string&, const string&, const string&, const string&, const string&, const string&);
        void updateAssistantInfoMenu(vector<Assistant>&);
        void manageAccount(vector<Users>& users);
        void viewAppointmentSchedule(const vector<Doctor>&, const vector<Patient>&);
        void createBill(Patient*, string const&);
        void viewBill(Patient*, const string&);
};
#endif
