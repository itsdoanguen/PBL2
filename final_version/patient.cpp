#include "patient.h"
#include "doctor.h"
#include "assistant.h"
// Default constructor
Patient::Patient() : Users() {}
// Parameterized constructor
Patient::Patient(const string& userID, const string& userName, const string& userPassword, unsigned int userRole,
                 const string& patientName, const string& DOB, const string& gender, 
                 const string& phoneNumber, const string& email, const string& address, 
                 const vector<string>& medicalHistory, const vector<string>& standingAppointments, const string& emergencyContact, double cash, const vector<string>& medicalResult)
    : Users(userID, userName, userPassword, userRole),  
      patientName(patientName), DOB(DOB), gender(gender),
      phoneNumber(phoneNumber), email(email), address(address),
      medicalHistory(medicalHistory), standingAppointments(standingAppointments), emergencyContact(emergencyContact), cash(cash), medicalResult(medicalResult) {}
// Destructor
Patient::~Patient() {}

// Get
string Patient::getPatientName() const { return patientName; }
string Patient::getDOB() const { return DOB; }
string Patient::getGender() const { return gender; }
string Patient::getPhoneNumber() const { return phoneNumber; }
string Patient::getEmail() const { return email; }
string Patient::getAddress() const { return address; }
vector<string> Patient::getMedicalHistory() const { return medicalHistory; }
vector<string> Patient::getStandingAppointments() const { return standingAppointments; }
string Patient::getEmergencyContact() const { return emergencyContact; }
double Patient::getCash() const { return cash; }
vector<string> Patient::getMedicalResult() const { return medicalResult; }

// Set
void Patient::setPatientName(const string& newPatientName) { patientName = newPatientName; }
void Patient::setDOB(const string& newDOB) { DOB = newDOB; }
void Patient::setGender(const string& newGender) { gender = newGender; }
void Patient::setPhoneNumber(const string& newPhoneNumber) { phoneNumber = newPhoneNumber; }
void Patient::setEmail(const string& newEmail) { email = newEmail; }
void Patient::setAddress(const string& newAddress) { address = newAddress; }
void Patient::setMedicalHistory(const vector<string>& newMedicalHistory) { medicalHistory = newMedicalHistory; }
void Patient::setStandingAppointments(const vector<string>& newStandingAppointments) { standingAppointments = newStandingAppointments; }
void Patient::setEmergencyContact(const string& newEmergencyContact) { emergencyContact = newEmergencyContact; }
void Patient::setCash(double newCash) { cash = newCash; }
void Patient::setMedicalResult(const vector<string>& newMedicalResult) { medicalResult = newMedicalResult; }

//Member Functions

void Patient::bookAppointment(vector<Doctor>& doctors, vector<Patient>& patients) {
    if (patientName == "Unknown" || DOB == "Unknown" || gender == "Unknown" ||
        phoneNumber == "Unknown" || email == "Unknown" || address == "Unknown") {
        cout << "Please update your information before booking an appointment.\n";
        return;
    }

    cout << "----------------------------------------------------" << endl;
    int day, month;
    cout << "Enter the day for the appointment (1-31)" << setw(5) << right << ": ";
    cin >> day;
    cout << "Enter the month for the appointment (1-12)" << setw(3) << right << ": ";
    cin >> month;

    time_t t = time(nullptr);
    tm* currentTime = localtime(&t);
    bool validDate = true;
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        validDate = false;
    } else if (month == 2) {
        if (day > 29 || (day == 29 && (currentTime->tm_year + 1900) % 4 != 0)) {
            validDate = false;
        }
    } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        validDate = false;
    }
    if (!validDate || (month < (currentTime->tm_mon + 1)) || (month == (currentTime->tm_mon + 1) && day <= currentTime->tm_mday)) {
        cout << "Invalid date. Please enter a valid date after the current day.\n";
        return;
    }
    string date = (day < 10 ? "0" : "") + to_string(day) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-" + to_string(currentTime->tm_year + 1900);

    cout << "Enter the time for the appointment (HH:MM)" << setw(3) << right << ": ";
    string time;
    cin >> time;
    while (!regex_match(time, regex("\\d{2}:\\d{2}"))) {
        cout << "Invalid format. Enter the time in HH:MM format:";
        cin >> time;
    }
    int hour, minute;
    sscanf(time.c_str(), "%d:%d", &hour, &minute);
    while (hour < 0 || hour >= 24 || minute < 0 || minute >= 60) {
        cout << "Invalid time. Please enter a valid time in HH:MM format: ";
        cin >> time;
        sscanf(time.c_str(), "%d:%d", &hour, &minute);
    }

    string appointment = time + " " + date;

    cout << "----------------------------------------------------" << endl;
    cout << "|  Available doctors at " << appointment << ":          |"  << endl;
    vector<Doctor*> availableDoctors;
    for (size_t i = 0; i < doctors.size(); ++i) {
        vector<string> schedule = doctors[i].getAppointmentSchedule();
        bool isAvailable = true;
        for (const auto& appt : schedule) {
            tm apptTime = {};
            istringstream ss(appt);
            ss >> get_time(&apptTime, "%H:%M %d-%m-%Y");
            if (ss.fail()) {
                cerr << "Error parsing date/time.\n";
                continue;
            }
            if (apptTime.tm_year == currentTime->tm_year && apptTime.tm_mon == month - 1 && apptTime.tm_mday == day) {
                int apptHour, apptMinute;
                sscanf(appt.substr(0, 5).c_str(), "%d:%d", &apptHour, &apptMinute);
                if (abs((hour * 60 + minute) - (apptHour * 60 + apptMinute)) < 60) {
                    isAvailable = false;
                    break;
                }
            }
        }
        if (isAvailable) {
            availableDoctors.push_back(&doctors[i]);
            cout << "|     " << availableDoctors.size() << ". " <<
                setw(29) << left << doctors[i].getDoctorName() << "(" << setw(8) << doctors[i].getSpecialization() << ")   |" << endl;
        }
    }
    if (availableDoctors.empty()) {
        cout << "|     No doctors available at the selected date and time.\n";
        return;
    }
    cout << "|     0. Cancel                                    |" << endl;
    cout << "----------------------------------------------------" << endl;
    int doctorChoice;
    cout << "Select a doctor by number: ";
    cin >> doctorChoice;
    if (doctorChoice == 0) {
        cout << "Appointment booking canceled. Return to menu.\n";
        return;
    } 
    if (doctorChoice < 1 || doctorChoice > availableDoctors.size()) {
        cout << "Invalid choice.\n";
        return;
    }
    Doctor& selectedDoctor = *availableDoctors[doctorChoice - 1];

    cout << "----------------------------------------------------" << endl;
    cout << "|     Doctor Information:                          |" << endl;
    cout << "|     Name: " << setw(39) <<  selectedDoctor.getDoctorName() << "|" << endl;
    cout << "|     Specialization: " << setw(29) << selectedDoctor.getSpecialization() << "|" << endl;
    cout << "|     Phone Number: " << setw(31) << selectedDoctor.getPhoneNumber() << "|" << endl;
    cout << "|     Email: " << setw(38) << selectedDoctor.getEmail() << "|" << endl;
    cout << "|     Address: " << setw(36) << selectedDoctor.getAddress() << "|" << endl;
    cout << "----------------------------------------------------" << endl;
    double appointmentFee = 100.0; 
    cout << "You current have" << setw(30)<< right << ":" << this->cash << endl;;
    cout << "The fee for this appointment is              :" << appointmentFee <<  endl;
    cout << "Do you want to confirm the appointment?(Y/N) : ";
    string confirmation;
    cin >> confirmation;
    if (confirmation!= "Y" && confirmation != "y") {
        cout << "Appointment booking canceled.\n";
        return;
    }

    if (cash < appointmentFee) {
        cout << "Insufficient funds to book an appointment.\n";
        return;
    }
    cash -= appointmentFee;

    vector<string> schedule = selectedDoctor.getAppointmentSchedule();
    schedule.push_back(appointment);
    standingAppointments.push_back(appointment);
    selectedDoctor.setAppointmentSchedule(schedule);
    cout << "Appointment booked successfully.\n";
}
void Patient::updatePatientInfo(const string& userID, const string& newPatientName, const string& newDOB, 
                                const string& newGender, const string& newPhoneNumber, const string& newEmail, 
                                const string& newAddress, const string& newEmergencyContact, const vector<string>& newMedicalHistory, const vector<string>& newMedicalResult) {
    if (this->getUserID() == userID) { 
        this->patientName = newPatientName;
        this->DOB = newDOB;
        this->gender = newGender;
        this->phoneNumber = newPhoneNumber;
        this->email = newEmail;
        this->address = newAddress;
        this->emergencyContact = newEmergencyContact;
        this->medicalHistory = newMedicalHistory;
        this->medicalResult = newMedicalResult;
    }
}
void Patient::showPatientInfo() const 
{
    cout << "-----------------Patient Information----------------" << endl;
    cout << "|   Name: " << setw(41) << left << patientName << "|" << endl;
    cout << "|   Date of Birth: " << setw(32) << left << DOB << "|" << endl;
    cout << "|   Gender: " << setw(39) << left << gender << "|" << endl;
    cout << "|   Phone Number: " << setw(33) << left << phoneNumber << "|" << endl;
    cout << "|   Email: " << setw(40) << left << email << "|" << endl;
    cout << "|   Address: " << setw(38) << left << address << "|" << endl;
    cout << "|   Medical History:                               |" << endl;
    for (const auto& history : medicalHistory) {
        cout << "|             +" << setw(36) << left << history << "|" << endl;
    }
    cout << "|   Standing Appointments:                         |" << endl;
    for (const auto& appointment : standingAppointments) {
        cout << "|             +" << setw(36) << left << appointment << "|" << endl;
    }
    cout << "|   Emergency Contact: " << setw(28) << left << emergencyContact << "|" << endl;
    cout << "|   Cash: " << setw(41) << left << cash << "|" << endl;
    cout << "----------------------------------------------------" << endl;
}

void Patient::viewAppointmentHistory(const vector<Doctor>& doctors) {
    vector<string> unpaidAppointments;
    vector<string> paidAppointments;
    vector<string> canceledAppointments;

    ifstream file(this->getUserID() + "_MedicalResults.txt");
    if (!file.is_open()) {
        cout << "There are no appointments to display.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string appointmentID, appointment, medicalRecord, prescription, doctorID, paymentStatus, resultStatus;
        getline(ss, appointmentID, '~');
        getline(ss, appointment, '~');
        getline(ss, medicalRecord, '~');
        getline(ss, prescription, '~');
        getline(ss, doctorID, '~');
        getline(ss, paymentStatus, '~');
        getline(ss, resultStatus, '~');

        if (resultStatus == "C1" || resultStatus == "C2" || resultStatus == "C3") {
            canceledAppointments.push_back(appointment + "~" + resultStatus);
        } else if (resultStatus == "D") {
            if (paymentStatus == "0") {
                unpaidAppointments.push_back(appointment);
            } else if (paymentStatus == "1") {
                paidAppointments.push_back(appointment);
            }
        }
    }
    file.close();

    int choice;
    do {
        cout << "-----------------Appointment History----------------" << endl;
        cout << "| 1. Unpaid Appointments                           |" << endl;
        cout << "| 2. Paid Appointments                             |" << endl;
        cout << "| 3. Canceled Appointments                         |" << endl;
        cout << "| 0. Exit                                          |" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int subChoice;
                do {
                    system("cls");
                    if (unpaidAppointments.empty()) {
                        cout << "-----------------Unpaid Appointments----------------" << endl;
                        cout << "|      No unpaid appointments available.           |" << endl;
                        cout << "----------------------------------------------------" << endl;
                        cout << "Enter to continue."; cin.ignore(); cin.get();
                        break;
                    }
                    cout << "-----------------Unpaid Appointments----------------" << endl;
                    for (size_t i = 0; i < unpaidAppointments.size(); ++i) {
                            cout << "| " << setw(3) << right << i + 1 << ". " << setw(36) << left << unpaidAppointments[i] << "        |" << endl;
                        }
                    cout << "| " << setw(3) << right << unpaidAppointments.size() + 1 << ". Deposit Money                               |" << endl;
                    cout << "|   0. Return                                      |" << endl;
                    cout << "----------------------------------------------------" << endl;
                    cout << "Select an appointment to pay by number: ";
                    cin >> subChoice;
                    if (subChoice > 0 && subChoice <= unpaidAppointments.size()) {
                        if (cash >= 100.0) {
                            char confirm;
                            cout << "Confirm payment for " << unpaidAppointments[subChoice - 1] << "?(Y/N): ";
                            cin >> confirm;
                            if (confirm != 'Y' && confirm != 'y') {
                                cout << "Payment canceled.\n";
                                break;
                            }
                            makeDeposit(-100.0);
                            string selectedAppointment = unpaidAppointments[subChoice - 1];
                            ifstream inFile(this->getUserID() + "_MedicalResults.txt");
                            ofstream outFile("temp.txt");
                            string line;
                            while (getline(inFile, line)) {
                                if (line.find(selectedAppointment) != string::npos) {
                                    line.replace(line.find("~0~D"), 4, "~1~D");
                                }
                                outFile << line << endl;
                            }
                            inFile.close();
                            outFile.close();
                            remove((this->getUserID() + "_MedicalResults.txt").c_str());
                            rename("temp.txt", (this->getUserID() + "_MedicalResults.txt").c_str());
                            Assistant assistant;
                            assistant.createBill(this, selectedAppointment);

                            cout << "Appointment paid successfully.\n";
                            cout << "Enter to continue."; cin.ignore(); cin.get();
                            paidAppointments.push_back(selectedAppointment);
                            unpaidAppointments.erase(unpaidAppointments.begin() + subChoice - 1);
                        } else {
                            cout << "Insufficient funds to pay for the appointment.\n";
                        }
                    } else if (subChoice == unpaidAppointments.size() + 1) {
                        double amount;
                        cout << "Enter the amount to deposit: ";
                        cin >> amount;
                        if (amount <= 0) {
                            cout << "Invalid amount. Please enter a positive value.\n";
                            return;
                        }
                        makeDeposit(amount);
                    }
                } while (subChoice != 0);
                system("cls");
                break;
            }
            case 2: {
                int subChoice;
                do {
                    system("cls"); 
                    if (paidAppointments.empty()) {
                        cout << "------------------Paid Appointments-----------------" << endl;
                        cout << "|      No paid appointments available.             |" << endl;
                        cout << "----------------------------------------------------" << endl;
                        cout << "Enter to continue."; cin.ignore(); cin.get();
                        break;
                    } else 
                    cout << "------------------Paid Appointments-----------------" << endl;
                    for (size_t i = 0; i < paidAppointments.size(); ++i) {
                        cout << "| " << setw(3) << right << i + 1 << ". " << setw(36) << left << paidAppointments[i] << "        |" << endl;
                    }
                    cout << "|   0. Return                                      |" << endl;
                    cout << "----------------------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> subChoice;

                    if (subChoice > 0 && subChoice <= paidAppointments.size()) {
                        string selectedAppointment = paidAppointments[subChoice - 1];
                        Assistant assistant;
                        assistant.viewBill(this, selectedAppointment);
                    }
                } while (subChoice != 0);
                system("cls");
                break;
            }
            case 3: {
                system("cls");
                cout << "----------------Canceled Appointments---------------" << endl;
                if (canceledAppointments.empty()) {
                    cout << "|      No canceled appointments available.          |" << endl;
                } else {
                    for (const auto& appointment : canceledAppointments) {
                        size_t pos = appointment.find("~");
                        string appt = appointment.substr(0, pos);
                        string reason = appointment.substr(pos + 1);
                        if (reason == "C1") reason = "Doctor canceled.";
                        else if (reason == "C2") reason = "Patient not show up.";
                        else if (reason == "C3") reason = "Patient canceled.";
                        cout << "|    +   " << setw(36) << left << appt << "      |" << endl;
                        cout << "|        Reason: "<< setw(27) << reason << "      |" << endl;
                    }
                }
                cout << "----------------------------------------------------" << endl;
                cout << "Enter to continue."; cin.ignore(); cin.get();
                system("cls");
                break;
            }
            case 0:
                cout << "Exiting appointment history.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);
}

void Patient::viewAndCancelAppointments(vector<Doctor>& doctors, vector<Patient>& patients) {
    if (standingAppointments.empty()) {
        cout << "You have no appointments booked.\n";
        return;
    }

    cout << "----------------------------------------------------" << endl;
    cout << "| Your Appointments:                               |" << endl;
    for (size_t i = 0; i < standingAppointments.size(); ++i) {
        cout << "| " << setw(3) << right << i + 1 << ". " << setw(43) << left << standingAppointments[i] << " |" << endl;
    }
    cout << "|   0. Cancel                                      |" << endl;
    cout << "----------------------------------------------------" << endl;
    int appointmentChoice;
    cout << "Select an appointment to view or cancel by number: ";
    cin >> appointmentChoice;
    if (appointmentChoice == 0) {
        cout << "Operation canceled.\n";
        return;
    }
    if (appointmentChoice < 1 || appointmentChoice > standingAppointments.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    string selectedAppointment = standingAppointments[appointmentChoice - 1];
    cout << "Selected Appointment: " << selectedAppointment << endl;

    cout << "----------------------------------------------------" << endl;
    cout << "| 1. View Doctor Info                              |" << endl;
    cout << "| 2. Cancel Appointment                            |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Enter your choice: ";
    int actionChoice;
    cin >> actionChoice;

    if (actionChoice == 1) {
        for (const auto& doctor : doctors) {
            const auto& schedule = doctor.getAppointmentSchedule();
            if (find(schedule.begin(), schedule.end(), selectedAppointment) != schedule.end()) {
                cout << "----------------------------------------------------" << endl;
                cout << "|     Doctor Information:                          |" << endl;
                cout << "|     Name: " << setw(39) <<  doctor.getDoctorName() << "|" << endl;
                cout << "|     Specialization: " << setw(29) << doctor.getSpecialization() << "|" << endl;
                cout << "|     Phone Number: " << setw(31) << doctor.getPhoneNumber() << "|" << endl;
                cout << "|     Email: " << setw(38) << doctor.getEmail() << "|" << endl;
                cout << "|     Address: " << setw(36) << doctor.getAddress() << "|" << endl;
                cout << "----------------------------------------------------" << endl;
                break;
            }
        }
    } else if (actionChoice == 2) {
        for (auto& doctor : doctors) {
            auto schedule = doctor.getAppointmentSchedule();
            auto it = find(schedule.begin(), schedule.end(), selectedAppointment);
            if (it != schedule.end()) {
                schedule.erase(it);
                doctor.setAppointmentSchedule(schedule);
                break;
            }
        }
        standingAppointments.erase(standingAppointments.begin() + appointmentChoice - 1);
        time_t t = time(nullptr);
        tm* currentTime = localtime(&t);
        tm appointmentTime = {};
        istringstream ss(selectedAppointment);
        ss >> get_time(&appointmentTime, "%H:%M %d-%m-%Y");
        if (ss.fail()) {
            cerr << "Error parsing date/time.\n";
            return;
        }
        double refund = 0.0;
        double appointmentFee = 100.0; 
        double secondsInDay = 86400.0;
        double daysDifference = difftime(mktime(&appointmentTime), mktime(currentTime)) / secondsInDay;

        if (daysDifference >= 2) {
            refund = appointmentFee;
        } else if (daysDifference >= 1) {
            refund = appointmentFee * 0.5;
        }

        cout << "----------------------------------------------------" << endl;
        cout << "| Cancellation Fee:                                |" << endl;
        cout << "| Full refund if canceled >= 2 days before         |" << endl;
        cout << "| 50% refund if canceled < 2 days before           |" << endl;
        cout << "| No refund if canceled on the same day            |" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "| You will be refunded                        :" << setw(4) << refund << "|"<< endl;
        cout << "----------------------------------------------------" << endl;

        cout << "Do you want to confirm the cancellation? (Y/N): ";
        string confirmation;
        cin >> confirmation;
        if (confirmation != "Y" && confirmation != "y") {
            cout << "Cancellation process aborted.\n";
            return;
        }

        cash += refund;
        cout << "Appointment canceled successfully.\n";

        string patientID = this->getUserID();
        string date = selectedAppointment.substr(6, 2) + selectedAppointment.substr(9, 2) + selectedAppointment.substr(14, 2); 
        string time = selectedAppointment.substr(0, 2) + selectedAppointment.substr(3, 2); 
        string appointmentID = date + patientID + time;
        string filename = patientID + "_MedicalResults.txt";
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            outFile << appointmentID << "~" << selectedAppointment << "~" << "N/A" << "~" << "N/A" << "~" << "N/A" << "~" << "Patient canceled" << "~C3\n";
            outFile.close();
        } else {
            cout << "Error opening file to save medical result.\n";
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

void Patient::updatePatientInfoMenu(vector<Patient>& patients) {
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
        cout << "|                  7. Emergency Contact                    |" << endl;
        cout << "|                  8. Medical History                      |" << endl;
        cout << "|                  9. Save and exit                        |" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> updateChoice;
        cin.ignore(); 

        switch (updateChoice) {
            case 1: {
                string newPatientName;
                cout << "Enter your name: ";
                getline(cin, newPatientName);
                setPatientName(newPatientName);
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
                string newEmergencyContact;
                cout << "Enter your Emergency Contact: ";
                getline(cin, newEmergencyContact);
                setEmergencyContact(newEmergencyContact);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 8: {
                vector<string> newMedicalHistory;
                string medHistoryStream;
                cout << "Enter your medical history (separated by commas): ";
                getline(cin, medHistoryStream);
                istringstream ss(medHistoryStream);
                string medItem;
                while (getline(ss, medItem, ',')) {
                    newMedicalHistory.push_back(medItem);
                }
                setMedicalHistory(newMedicalHistory);
                cout << "Updating successfully." << endl; sleep(1.5);
                break;
            }
            case 9:
                cout << "Exiting update menu.\n"; sleep(1.5);
                break;
            default:
                cout << "Invalid choice. Please try again.\n"; sleep(2);
        }
    } while (updateChoice != 9);
}
void Patient::addMedicalResult(const string& newMedicalResult) { medicalResult.push_back(newMedicalResult); }
void Patient::viewMedicalResults(vector<Doctor>& doctors) const {
    if (medicalResult.empty()) {
        cout << "No medical results available.\n";
        return;
    }
    cout << "----------------------------------------------------" << endl;
    cout << "|    Medical Results:                              |" << endl;
    for (size_t i = 0; i < medicalResult.size(); ++i) {
        cout << "| " << setw(3) <<  i + 1 << ". " << setw(36) <<medicalResult[i] << "        |" << endl;
    }
    cout << "| " << setw(3) <<  0 << ". " << setw(36) <<"Cancel" << "        |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Select the appointment you want to view(0 to cancel): ";
    int choice;
    cin >> choice;
    if (choice == 0) {
        cout << "Operation canceled.\n";
        return;
    }
    if (choice < 1 || choice > medicalResult.size()) {
        cout << "Invalid choice.\n";
        return;
    }
    cout << "----------------------------------------------------" << endl;
    cout << "|     Detailed Medical Result:                     |\n";
    string selectedResult = medicalResult[choice - 1];
    string appointmentID = selectedResult;
    ifstream file(this->getUserID() + "_MedicalResults.txt");
    if (!file.is_open()) {
        cout << "Error opening medical results file.\n";
        return;
    }
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(appointmentID) != string::npos) {
            found = true;
            break;
        }
    }
    if (found){
        istringstream ss(line);
        string appointmentID, appointment, medicalRecord, prescription, doctorID;
        getline(ss, appointmentID, '~');
        getline(ss, appointment, '~');
        getline(ss, medicalRecord, '~');
        getline(ss, prescription, '~');
        getline(ss, doctorID, '~');

        cout << "----------------------------------------------------" << endl;
        cout << "|   Appointment Details:                           |" << endl;
        cout << "|   Appointment ID: " << setw(31) << appointmentID << "|"<< endl;
        cout << "|   Appointment day: " << setw(30) << appointment << "|" <<endl;
        cout << "|   Medical Record: " << setw(31) << medicalRecord << "|" << endl;
        cout << "|   Prescription: " << setw(33) << prescription << "|" << endl;
        for (const auto& doctor : doctors) {
            if (doctor.getUserID() == doctorID) {
            cout << "|   Doctor Name: " << setw(34) << doctor.getDoctorName() << "|" << endl;
            cout << "|   Specialization: " << setw(31) << doctor.getSpecialization() << "|" << endl;
            cout << "|   Phone Number: " << setw(33) << doctor.getPhoneNumber() << "|" << endl;
            cout << "|   Email: " << setw(40) << doctor.getEmail() << "|" << endl;
            break;
            }
        }
        cout << "----------------------------------------------------" << endl;
    }
    else {
        cout << "No detailed medical result found for the selected appointment.\n";
    }

    file.close();
}

void Patient::makeDeposit(double amount) {
    cash += amount;
    cout << "Your new balance is: " << cash << "\n";

    ifstream inFile("patientInfo.txt");
    ofstream outFile("temp.txt");
    string line;
    while (getline(inFile, line)) {
        if (line.find(this->getUserID()) != string::npos) {
            istringstream ss(line);
            string userID, patientName, DOB, gender, phoneNumber, email, 
                        address, medicalHistoryStr, standingAppointmentsStr, emergencyContact, medicalResultStr;
            double oldCash;

            getline(ss, userID, ';');
            getline(ss, patientName, ';');
            getline(ss, DOB, ';');
            getline(ss, gender, ';');
            getline(ss, phoneNumber, ';');
            getline(ss, email, ';');
            getline(ss, address, ';');
            getline(ss, medicalHistoryStr, ';');
            getline(ss, standingAppointmentsStr, ';');
            getline(ss, emergencyContact, ';');
            getline(ss, medicalResultStr, ';');
            ss >> oldCash;

            outFile << userID << ";" << patientName << ";" << DOB << ";" << gender << ";" << phoneNumber << ";" << email << ";"
                    << address << ";" << medicalHistoryStr << ";" << standingAppointmentsStr << ";"
                    << emergencyContact << ";" << medicalResultStr << ";" << cash << "\n";
        } else {
            outFile << line << "\n";
        }
    }
    inFile.close();
    outFile.close();
    remove("patientInfo.txt");
    rename("temp.txt", "patientInfo.txt");
}

void Patient::manageAccount(vector<Users>& users) {
    int choice;
    do {
        system("cls");
        cout << "------------------- Manage Account -------------------" << endl;
        cout << "| 1. Manage Account                                  |" << endl;
        cout << "| 2. Deposit Money                                   |" << endl;
        cout << "| 0. Exit                                            |" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                Users::manageAccount(users);
                break;
            case 2: {
                double amount;
                cout << "Enter the amount to deposit: ";
                cin >> amount;
                if (amount <= 0) {
                    cout << "Invalid amount. Please enter a positive value.\n";
                    break;
                }
                makeDeposit(amount);
                cout << "Enter to continue."; cin.ignore(); cin.get();
                break;
            }
            case 0:
                cout << "Exiting Manage Account.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);
}