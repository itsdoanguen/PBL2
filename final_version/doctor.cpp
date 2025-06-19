#include "doctor.h"
#include "patient.h"
#include <iostream> 
#include <iomanip>
#include <algorithm> 
#include <unistd.h> 

// Default constructor
Doctor::Doctor() : Users() {}
// Parameterized constructor
Doctor::Doctor(const string& userID, const string& userName, const string& userPassword, unsigned int userRole,
               const string& name, const string& DOB, const string& gender, 
               const string& phoneNumber, const string& email, const string& address,
               const string& specialization, const vector<string>& appointmentSchedule)
        : Users(userID, userName, userPassword, userRole),
          name(name), DOB(DOB), gender(gender), phoneNumber(phoneNumber),
          email(email), address(address), specialization(specialization),
          appointmentSchedule(appointmentSchedule) {}
// Destructor
Doctor::~Doctor() {}

// Get
string Doctor::getDoctorName() const { return name; }
string Doctor::getDOB() const { return DOB; }
string Doctor::getGender() const { return gender; }
string Doctor::getPhoneNumber() const { return phoneNumber; }
string Doctor::getEmail() const { return email; }
string Doctor::getAddress() const { return address; }
string Doctor::getSpecialization() const { return specialization; }
vector<string> Doctor::getAppointmentSchedule() const { return appointmentSchedule; }

// Set
void Doctor::setDoctorName(const string& name) { this->name = name; }
void Doctor::setDOB(const string& DOB) { this->DOB = DOB; }
void Doctor::setGender(const string& gender) { this->gender = gender; }
void Doctor::setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
void Doctor::setEmail(const string& email) { this->email = email; }
void Doctor::setAddress(const string& address) { this->address = address; }
void Doctor::setSpecialization(const string& specialization) { this->specialization = specialization; }
void Doctor::setAppointmentSchedule(const vector<string>& schedule) { appointmentSchedule = schedule; }

// Member Functions
void Doctor::showDoctorInfo() const {
    cout << "------------------Doctor Information----------------" << endl;
    cout << "|   Name: " << setw(41) << left << name << "|" << endl;
    cout << "|   Date of Birth: " << setw(32) << left << DOB << "|" << endl;
    cout << "|   Gender: " << setw(39) << left << gender << "|" << endl;
    cout << "|   Phone Number: " << setw(33) << left << phoneNumber << "|" << endl;
    cout << "|   Email: " << setw(40) << left << email << "|" << endl;
    cout << "|   Address: " << setw(38) << left << address << "|" << endl;
    cout << "|   Specialization: " << setw(31) << left << specialization << "|" << endl;
    cout << "|   Appointment Schedule:                          |" << endl;
    for (const auto& appointment : appointmentSchedule) {
        cout << "|             +" << setw(36) << left << appointment << "|" << endl;
    }
    cout << "----------------------------------------------------" << endl;
}
void Doctor::saveMedicalResult(Patient& patient, const string& appointment) {
    patient.addMedicalResult(appointment); 
}
void Doctor::updateDoctorInfo(const string& userID, const string& newName, const string& newDOB, const string& newGender, const string& newPhoneNumber, const string& newEmail, const string& newAddress, const string& newSpecialization, const vector<string>& newAppointmentSchedule) {
    if (this->getUserID() == userID) {
        this->name = newName;
        this->DOB = newDOB;
        this->gender = newGender;
        this->phoneNumber = newPhoneNumber;
        this->email = newEmail;
        this->address = newAddress;
        this->specialization = newSpecialization;
        this->appointmentSchedule = newAppointmentSchedule;
    }
}
void Doctor::updateDoctorInfoMenu(vector<Doctor>& doctors) {
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
        cout << "|                  7. Specialization                       |" << endl;
        cout << "|                  8. Save and exit                        |" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> updateChoice;
        cin.ignore(); 

        switch (updateChoice) {
            case 1: {
                string newName;
                cout << "Enter your name: ";
                getline(cin, newName);
                setDoctorName(newName);
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
            case 7: {
                string newSpecialization;
                cout << "Enter your Specialization: ";
                getline(cin, newSpecialization);
                setSpecialization(newSpecialization);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 8:
                cout << "Exiting update menu.\n"; sleep(1.5);
                break;
            default:
                cout << "Invalid choice. Please try again.\n"; sleep(2);
        }
    } while (updateChoice != 8);
}

string currentPatientID = "";
void Doctor::manageAppointmentSchedule(vector<Doctor>& doctors, vector<Patient>& patients) {
    int choice;
    do {
        system("cls");
        vector<string> sortedSchedule = appointmentSchedule;
        sort(sortedSchedule.begin(), sortedSchedule.end(), [](const string& a, const string& b) {
            tm timeA = {}, timeB = {};
            istringstream ssA(a), ssB(b);
            ssA >> get_time(&timeA, "%H:%M %d-%m-%Y");
            ssB >> get_time(&timeB, "%H:%M %d-%m-%Y");
            return mktime(&timeA) < mktime(&timeB);
        });

        cout << "-----------------Manage Appointment Schedule----------------" << endl;
        for (size_t i = 0; i < sortedSchedule.size(); ++i) {
            cout << "| " << setw(3) << right << i + 1 << ". " << setw(52) << left << sortedSchedule[i] << "|" << endl;
        }
        cout << "| " << setw(3) << right << "0" << ". Exit                                                |" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Choose an appointment to manage: ";
        cin >> choice;
        cin.ignore();
        string choosedAppointment;
        if (choice > 0 && choice <= sortedSchedule.size()) {
            for (const auto& patient : patients) {
                const auto& patientAppointments = patient.getStandingAppointments();
                if (find(patientAppointments.begin(), patientAppointments.end(), sortedSchedule[choice - 1]) != patientAppointments.end()) {
                    choosedAppointment = sortedSchedule[choice - 1];
                    currentPatientID = patient.getUserID();
                    break;
                }
            }

            int manageChoice;
            bool check = false; 
            do {
                system("cls");
                cout << "---------------------------------------------------" << endl;
                cout << "|   Appointment: " <<   setw(33) << left << choosedAppointment  << "|"<< endl;
                cout << "-----------------Manage Appointment----------------" << endl;
                cout << "| 1. Process Appointment                          |" << endl;
                cout << "| 2. Cancel Appointment                           |" << endl;
                cout << "| 3. Return                                       |" << endl;
                cout << "---------------------------------------------------" << endl;
                cout << "Choose an option: ";
                cin >> manageChoice;
                cin.ignore();

                switch (manageChoice) {
                    case 1:
                        check = processAppointment(choosedAppointment, patients);
                        if (check == true) {
                            return;
                        }
                        break;
                    case 2:
                        check = cancelAppointment(choosedAppointment, doctors, patients);
                        if (check == true) {
                            return;
                        }
                    case 3:
                        currentPatientID = "";
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl; sleep(1.5);
                        break;
                }
            } while (manageChoice != 3);
        } else if (choice != 0) {
            cout << "Invalid choice. Please try again." << endl; sleep(1.5);
        }
    } while (choice != 0);
}
bool Doctor::processAppointment(const string& appointment, vector<Patient>& patients) {
    int viewChoice;
    do {
        system("cls");
        cout << "-------------------------------------------------" << endl;
        cout << "|   Appointment: " <<   setw(31) << left << appointment  << "|"<< endl;
        cout << "-----------------View Appointment----------------" << endl;
        cout << "| 1. View Patient Info                          |" << endl;
        cout << "| 2. Start to Work                              |" << endl;
        cout << "| 3. Return                                     |" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "Choose an option: ";
        cin >> viewChoice;
        cin.ignore();

        Patient* currentPatient = nullptr;
        for (auto& patient : patients) {
            if (patient.getUserID() == currentPatientID) {
                currentPatient = &patient;
                break;
            }
        }
        if (!currentPatient) {
            cout << "No patient found with this appointment." << endl;
            return false;
        }

        switch (viewChoice) {
            case 1: 
            {
                currentPatient->showPatientInfo();
                cout << "Enter to continue."; getchar();
                break;
            }
            case 2:
            {
                currentPatient->showPatientInfo();
                cout << "Starting to work with patient..." << endl;
                string medicalRecord, prescription;
                cout << "Enter medical record: "; getline(cin, medicalRecord);
                cout << "Enter prescription: "; getline(cin, prescription);

                string patientID = currentPatient->getUserID();
                string date = appointment.substr(6, 2) + appointment.substr(9, 2) + appointment.substr(14, 2); 
                string time = appointment.substr(0, 2) + appointment.substr(3, 2); 
                string appointmentID = date + patientID + time;

                saveMedicalResult(*currentPatient, appointmentID);
                
                string filename = patientID + "_MedicalResults.txt";
                ofstream outFile(filename, ios::app);
                if (outFile.is_open()) {
                    outFile << appointmentID << "~" << appointment << "~" << medicalRecord << "~" << prescription << "~" << this->getUserID() << "~0" << "~D\n";
                    outFile.close();
                    cout << "Medical result saved successfully.\n";
                } else {
                    cout << "Error opening file to save medical result.\n";
                }

                auto& schedule = this->appointmentSchedule;
                schedule.erase(remove(schedule.begin(), schedule.end(), appointment), schedule.end());
                this->setAppointmentSchedule(schedule);

                vector<string> newStandingAppointments;
                for (const auto& appt : currentPatient->getStandingAppointments()) {
                    if (appt != appointment) {
                        newStandingAppointments.push_back(appt);
                    }
                }
                currentPatient->setStandingAppointments(newStandingAppointments);

                for (auto& patient : patients) {
                    if (patient.getUserID() == currentPatientID) {
                        patient = *currentPatient;
                        break;
                    }
                }
                cout << "Appointment completed and updated successfully." << endl; sleep(1.5);
                return true; 
            }
            case 3:
                return false;
            default:
                cout << "Invalid choice. Please try again." << endl; sleep(1.5);
                break;
        }
    } while (viewChoice != 3);
    return false; 
}
bool Doctor::cancelAppointment(const string& appointment, vector<Doctor>& doctors, vector<Patient>& patients) {
    int updateChoice;
    do {
        system("cls");
        cout << "-----------------Update Appointment----------------" << endl;
        cout << "| 1. Cancel Appointment (Busy)                    |" << endl;
        cout << "| 2. Cancel Appointment (No showing up)           |" << endl;
        cout << "| 3. Return                                       |" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Choose an option: ";
        cin >> updateChoice;
        cin.ignore();
        
        Patient* currentPatient = nullptr;
        for (auto& patient : patients) {
            if (patient.getUserID() == currentPatientID) {
                currentPatient = &patient;
                break;
            }
        }

        if (!currentPatient) {
            cout << "No patient found with this appointment." << endl;
            return false;
        }

        string patientID = currentPatient->getUserID();
        string date = appointment.substr(6, 2) + appointment.substr(9, 2) + appointment.substr(14, 2); 
        string time = appointment.substr(0, 2) + appointment.substr(3, 2); 
        string appointmentID = date + patientID + time;

        switch (updateChoice) {
            case 1: {
                cout << "Cancelling appointment due to busy schedule..." << endl; sleep(1);
                auto& schedule = this->appointmentSchedule;
                schedule.erase(remove(schedule.begin(), schedule.end(), appointment), schedule.end());
                this->setAppointmentSchedule(schedule);

                vector<string> newStandingAppointments;
                for (const auto& appt : currentPatient->getStandingAppointments()) {
                    if (appt != appointment) {
                        newStandingAppointments.push_back(appt);
                    }
                }
                currentPatient->setStandingAppointments(newStandingAppointments);
                cout << "Appointment canceled due to doctor's busy schedule. Refund $100.\n";
                currentPatient->setCash(currentPatient->getCash() + 100.0);

                string filename = patientID + "_MedicalResults.txt";
                ofstream outFile(filename, ios::app);
                if (outFile.is_open()) {
                    outFile << appointmentID << "~" << appointment << "~" << "N/A" << "~" << "N/A" << "~" << this->getUserID() << "~" << "Doctor canceled" << "~C1\n";
                    outFile.close();
                } else {
                    cout << "Error opening file to save medical result.\n";
                }

                for (auto& patient : patients) {
                    if (patient.getUserID() == currentPatientID) {
                        patient = *currentPatient;
                        break;
                    }
                }
                return true;
            }
            case 2: {
                cout << "Cancelling appointment due to no showup..." << endl;
                auto& schedule = this->appointmentSchedule;
                schedule.erase(remove(schedule.begin(), schedule.end(), appointment), schedule.end());
                this->setAppointmentSchedule(schedule);

                vector<string> newStandingAppointments;
                for (const auto& appt : currentPatient->getStandingAppointments()) {
                    if (appt != appointment) {
                        newStandingAppointments.push_back(appt);
                    }
                }
                currentPatient->setStandingAppointments(newStandingAppointments);
                cout << "Appointment canceled due to no showup. Refund $0.\n";

                string filename = patientID + "_MedicalResults.txt";
                ofstream outFile(filename, ios::app);
                if (outFile.is_open()) {
                    outFile << appointmentID << "~" << appointment << "~" << "N/A" << "~" << "N/A" << "~" << this->getUserID() << "~" << "Patient no showup" << "~C2\n";
                    outFile.close();
                } else {
                    cout << "Error opening file to save medical result.\n";
                }

                for (auto& patient : patients) {
                    if (patient.getUserID() == currentPatientID) {
                        patient = *currentPatient;
                        break;
                    }
                }
                return true;
            }
            case 3:
                currentPatientID = "";
                return false;
            default:
                cout << "Invalid choice. Please try again." << endl; sleep(1.5);
                break;
        }
    } while (updateChoice != 3);
    return false; 
}

void Doctor::manageAccount(vector<Users>& users) {
    Users::manageAccount(users);
}
