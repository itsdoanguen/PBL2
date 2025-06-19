#include "assistant.h"
#include "doctor.h"
#include "patient.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>

// Default constructor
Assistant::Assistant() : Users() {}

// Parameterized constructor
Assistant::Assistant(const string& userID, const string& userName, const string& userPassword, unsigned int userRole,
                     const string& name, const string& DOB, const string& gender, 
                     const string& phoneNumber, const string& email, const string& address)
        : Users(userID, userName, userPassword, userRole),
          name(name), DOB(DOB), gender(gender), phoneNumber(phoneNumber),
          email(email), address(address) {}

// Destructor
Assistant::~Assistant() {}

// Get
string Assistant::getName() const { return name; }
string Assistant::getDOB() const { return DOB; }
string Assistant::getGender() const { return gender; }
string Assistant::getPhoneNumber() const { return phoneNumber; }
string Assistant::getEmail() const { return email; }
string Assistant::getAddress() const { return address; }

// Set
void Assistant::setName(const string& name) { this->name = name; }
void Assistant::setDOB(const string& DOB) { this->DOB = DOB; }
void Assistant::setGender(const string& gender) { this->gender = gender; }
void Assistant::setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
void Assistant::setEmail(const string& email) { this->email = email; }
void Assistant::setAddress(const string& address) { this->address = address; }

// Member Functions
void Assistant::showAssistantInfo() const {
    cout << "----------------Assistant Information---------------" << endl;
    cout << "|   Name: " << setw(41) << left << name << "|" << endl;
    cout << "|   Date of Birth: " << setw(32) << left << DOB << "|" << endl;
    cout << "|   Gender: " << setw(39) << left << gender << "|" << endl;
    cout << "|   Phone Number: " << setw(33) << left << phoneNumber << "|" << endl;
    cout << "|   Email: " << setw(40) << left << email << "|" << endl;
    cout << "|   Address: " << setw(38) << left << address << "|" << endl;
    cout << "----------------------------------------------------" << endl;
}

void Assistant::updateAssistantInfo(const string& newName, const string& newDOB, const string& newGender, const string& newPhoneNumber, const string& newEmail, const string& newAddress) {
    this->name = newName;
    this->DOB = newDOB;
    this->gender = newGender;
    this->phoneNumber = newPhoneNumber;
    this->email = newEmail;
    this->address = newAddress;
}

void Assistant::updateAssistantInfoMenu(vector<Assistant>& assistants) {
    int updateChoice;
    do {
        system("cls");
        cout << "------------------------------------------------------------" << endl;
        cout << "|               What would you like to update?             |" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "|                  1. Name                                 |" << endl;
        cout << "|                  2. Date of Birth                        |" << endl;
        cout << "|                  3. Gender                               |" << endl;
        cout << "|                  4. Phone Number                         |" << endl;
        cout << "|                  5. Email                                |" << endl;
        cout << "|                  6. Address                              |" << endl;
        cout << "|                  0. Save and exit                        |" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> updateChoice;
        cin.ignore(); 

        switch (updateChoice) {
            case 1: {
                string newName;
                cout << "Enter your name: ";
                getline(cin, newName);
                setName(newName);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 2: {
                string newDOB;
                cout << "Enter your Date of Birth (DD-MM-YYYY): ";
                getline(cin, newDOB);
                setDOB(newDOB);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 3: {
                string newGender;
                cout << "Enter your gender: ";
                getline(cin, newGender);
                setGender(newGender);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 4: {
                string newPhoneNumber;
                cout << "Enter your Phone Number: ";
                getline(cin, newPhoneNumber);
                setPhoneNumber(newPhoneNumber);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 5: {
                string newEmail;
                cout << "Enter your Email: ";
                getline(cin, newEmail);
                setEmail(newEmail);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 6: {
                string newAddress;
                cout << "Enter your Address: ";
                getline(cin, newAddress);
                setAddress(newAddress);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 0:
                cout << "Exiting update menu.\n"; sleep(1.5);
                break;
            default:
                cout << "Invalid choice. Please try again.\n"; sleep(2);
        }
    } while (updateChoice != 0);
}

void Assistant::manageAccount(vector<Users>& users) {
    Users::manageAccount(users);
}

void showDoctorAppointmentSchedule(const Doctor& doctor, const vector<Patient>& patients) {
    vector<string> sortedSchedule = doctor.getAppointmentSchedule();
    if (sortedSchedule.empty()) {
        cout << "No appointments found for this doctor." << endl;
        cout << "Press Enter to continue.";
        cin.ignore(); cin.get();
        return;
    }
    system("cls");
    sort(sortedSchedule.begin(), sortedSchedule.end(), [](const string& a, const string& b) {
        tm timeA = {}, timeB = {};
        istringstream ssA(a), ssB(b);
        ssA >> get_time(&timeA, "%H:%M %d-%m-%Y");
        ssB >> get_time(&timeB, "%H:%M %d-%m-%Y");
        return mktime(&timeA) < mktime(&timeB);
    });

    cout << "-----------------Doctor Appointment Schedule----------------" << endl;
    for (size_t i = 0; i < sortedSchedule.size(); ++i) {
        cout << "| " << setw(3) << right << i + 1 << ". " << setw(52) << left << sortedSchedule[i] << "|" << endl;
    }
    cout << "| " << setw(3) << right << "0" << ". Exit                                                |" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Choose an appointment to view patient info (0 to exit): ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= sortedSchedule.size()) {
        string appointment = sortedSchedule[choice - 1];
        for (const auto& patient : patients) {
            if (find(patient.getStandingAppointments().begin(), patient.getStandingAppointments().end(), appointment) != patient.getStandingAppointments().end()) {
                patient.showPatientInfo();
                break;
            }
        }
    }
    cout << "Press Enter to continue.";
    cin.ignore(); cin.get();
}

void showPatientAppointmentSchedule(const Patient& patient, const vector<Doctor>& doctors) {
    vector<string> sortedSchedule = patient.getStandingAppointments();
    if (sortedSchedule.empty()) {
        cout << "No appointments found for this patient." << endl;
        cout << "Press Enter to continue.";
        cin.ignore(); cin.get();
        return;
    }
    system("cls");
    sort(sortedSchedule.begin(), sortedSchedule.end(), [](const string& a, const string& b) {
        tm timeA = {}, timeB = {};
        istringstream ssA(a), ssB(b);
        ssA >> get_time(&timeA, "%H:%M %d-%m-%Y");
        ssB >> get_time(&timeB, "%H:%M %d-%m-%Y");
        return mktime(&timeA) < mktime(&timeB);
    });

    cout << "-----------------Patient Appointment Schedule----------------" << endl;
    for (size_t i = 0; i < sortedSchedule.size(); ++i) {
        cout << "| " << setw(3) << right << i + 1 << ". " << setw(52) << left << sortedSchedule[i] << "|" << endl;
    }
    cout << "| " << setw(3) << right << "0" << ". Exit                                                |" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Choose an appointment to view doctor info (0 to exit): ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= sortedSchedule.size()) {
        string appointment = sortedSchedule[choice - 1];
        for (const auto& doctor : doctors) {
            if (find(doctor.getAppointmentSchedule().begin(), doctor.getAppointmentSchedule().end(), appointment) != doctor.getAppointmentSchedule().end()) {
                doctor.showDoctorInfo();
                break;
            }
        }
    }
    cout << "Press Enter to continue.";
    cin.ignore();
    getchar();
}

void Assistant::viewAppointmentSchedule(const vector<Doctor>& doctors, const vector<Patient>& patients) {
    int choice;
    do {
        system("cls");
        cout << "-----------------View Appointment Schedule----------------" << endl;
        cout << "| 1. View by Doctor ID                                   |" << endl;
        cout << "| 2. View by Patient ID                                  |" << endl;
        cout << "| 3. Return                                              |" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "-----------------Doctors----------------" << endl;
                for (const auto& doctor : doctors) {
                    cout << "| " << doctor.getUserID() << " - " << setw(27) <<  left << doctor.getDoctorName() << " |" << endl;
                }
                cout << "----------------------------------------" << endl;
                string doctorID;
                cout << "Enter Doctor ID(Enter 0 to return): ";
                getline(cin, doctorID);
                for (const auto& doctor : doctors) {
                    if (doctor.getUserID() == doctorID) {
                        showDoctorAppointmentSchedule(doctor, patients);
                        break;
                    }
                }
                break;
            }
            case 2: {
                cout << "-----------------Patients----------------" << endl;
                for (const auto& patient : patients) {
                    cout << "| " << patient.getUserID() << " - " << setw(27) << left << patient.getPatientName() << " |" << endl;
                }
                cout << "----------------------------------------" << endl;
                string patientID;
                cout << "Enter Patient ID(Enter 0 to return): ";
                getline(cin, patientID);
                for (const auto& patient : patients) {
                    if (patient.getUserID() == patientID) {
                        showPatientAppointmentSchedule(patient, doctors);
                        break;
                    }
                }
                break;
            }
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl; sleep(1.5);
        }
    } while (choice != 3);
}

void Assistant::createBill(Patient* patient, const string& appointment) {
    string patientID = patient->getUserID();
    string date = appointment.substr(6, 2) + appointment.substr(9, 2) + appointment.substr(14, 2); 
    string time = appointment.substr(0, 2) + appointment.substr(3, 2); 
    string appointmentID = date + patientID + time;
    string filename = appointmentID + "_Bill.txt";
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error creating bill." << endl;
        return;
    }

    outFile << "------------------Bill------------------" << endl;
    outFile << "Patient ID: " << patientID << endl;
    outFile << "Appointment: " << appointment << endl;
    outFile << "----------------------------------------" << endl;

    string medicalResultsFile = patientID + "_MedicalResults.txt";
    ifstream inFile(medicalResultsFile);
    if (!inFile.is_open()) {
        cout << "No medical results found for this patient." << endl;
        outFile.close();
        return;
    }

    string line;
    double totalCost = 0.0;
    while (getline(inFile, line)) {
        if (line.find(appointment) != string::npos) {
            istringstream iss(line);
            string appointmentID, appointment, medicalRecord, prescription, doctorID, status;
            getline(iss, appointmentID, '~');
            getline(iss, appointment, '~');
            getline(iss, medicalRecord, '~');
            getline(iss, prescription, '~');
            getline(iss, doctorID, '~');
            getline(iss, status, '~');

            outFile << "Medical Record: " << medicalRecord << endl;
            outFile << "Prescription: " << prescription << endl;
            outFile << "Doctor ID: " << doctorID << endl;
            outFile << "----------------------------------------" << endl;

            totalCost += 100.0;
        }
    }
    inFile.close();

    outFile << "Total Cost: $" << totalCost << endl;
    outFile << "----------------------------------------" << endl;
    outFile.close();
}

void Assistant::viewBill(Patient* patient, const string& appointment) {
    string patientID = patient->getUserID();
    string date = appointment.substr(6, 2) + appointment.substr(9, 2) + appointment.substr(14, 2); 
    string time = appointment.substr(0, 2) + appointment.substr(3, 2); 
    string appointmentID = date + patientID + time;
    string filename = appointmentID + "_Bill.txt";
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error opening bill." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
    cout << "Enter to continue."; cin.ignore(); cin.get();
}