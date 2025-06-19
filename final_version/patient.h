#ifndef PATIENT_H
#define PATIENT_H

#include "users.h"

class Doctor;
class Assistant;

class Patient : public Users {
    private:
        string patientName;
        string DOB;
        string gender;
        string phoneNumber;
        string email;
        string address;
        vector<string> medicalHistory;
        vector<string> standingAppointments;
        string emergencyContact;
        double cash;
        vector<string> medicalResult;

    public:
        Patient();
        Patient(const string&, const string&, const string&, unsigned int, const string&,
                const string&, const string&, const string&, const string&, const string&, 
                const vector<string>&, const vector<string>&, const string&, double, const vector<string>&);
        ~Patient();
        // Get
        string getPatientName() const;
        string getDOB() const;
        string getGender() const;
        string getPhoneNumber() const;
        string getEmail() const;
        string getAddress() const;
        vector<string> getMedicalHistory() const;
        vector<string> getStandingAppointments() const;
        string getEmergencyContact() const;
        double getCash() const;
        vector<string> getMedicalResult() const; 

        // Set
        void setPatientName(const string&);
        void setDOB(const string&);
        void setGender(const string&);
        void setPhoneNumber(const string&);
        void setEmail(const string&);
        void setAddress(const string&);
        void setMedicalHistory(const vector<string>&);
        void setStandingAppointments(const vector<string>&);
        void setEmergencyContact(const string&);
        void setCash(double);
        void setMedicalResult(const vector<string>&); 

        //Member Functions
        void showPatientInfo() const;
        void updatePatientInfo(const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const vector<string>&, const vector<string>&);
        void updatePatientInfoMenu(vector<Patient>&);
        void bookAppointment(vector<Doctor>&, vector<Patient>&);
        void viewAndCancelAppointments(vector<Doctor>&, vector<Patient>&);
        void viewAppointmentHistory(const vector<Doctor>&);
        void addMedicalResult(const string&); 
        void viewMedicalResults(vector<Doctor>&) const;
        void manageAccount(vector<Users>& users);
        void makeDeposit(double amount); 
};

#endif
