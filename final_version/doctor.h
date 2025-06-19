#ifndef DOCTOR_H
#define DOCTOR_H

#include "users.h"
#include "patient.h" // Include the full definition of the Patient class

class Patient;
class Doctor : public Users {
    private:
        string name;
        string DOB;
        string gender;
        string phoneNumber;
        string email;
        string address;
        string specialization;
        vector<string> appointmentSchedule;

    public:
        Doctor();
        Doctor(const string&, const string&, const string&, unsigned int, 
               const string&, const string&, const string&, const string&, 
               const string&, const string&, const string&, const vector<string>&);
        ~Doctor();

        // Get
        string getDoctorName() const;
        string getDOB() const;
        string getGender() const;
        string getPhoneNumber() const;
        string getEmail() const;
        string getAddress() const;
        string getSpecialization() const;
        vector<string> getAppointmentSchedule() const;

        // Set
        void setDoctorName(const string&);
        void setDOB(const string&);
        void setGender(const string&);
        void setPhoneNumber(const string&);
        void setEmail(const string&);
        void setAddress(const string&);
        void setSpecialization(const string&);
        void setAppointmentSchedule(const vector<string>&);

        // Member Functions
        void showDoctorInfo() const;
        void updateDoctorInfo(const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const vector<string>&);
        void updateDoctorInfoMenu(vector<Doctor>&);
        void manageAppointmentSchedule(vector<Doctor>&, vector<Patient>&);
        bool processAppointment(const string&, vector<Patient>&);
        bool cancelAppointment(const string& appointment, vector<Doctor>& doctors, vector<Patient>& patients);
        void saveMedicalResult(Patient&, const string&);
        void manageAccount(vector<Users>& users);
};

#endif
