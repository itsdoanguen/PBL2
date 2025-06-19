#include "users.h"
#include "patient.h"
#include "doctor.h"
#include "assistant.h"
#include "admin.h"

const string accFile = "account.txt";
const string patientInfoFile = "patientInfo.txt";
const string doctorInfoFile = "doctorInfo.txt";
const string assistantInfoFile = "assistantInfo.txt";
string currentUserID = "";

vector<Users> users;
vector<Patient> patients;
vector<Doctor> doctors;
vector<Assistant> assistants;

//Initialization
void initUsers() {
    ifstream file(accFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << accFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string userID, userName, userPassword, userRoleStr;

        if (getline(ss, userID, ';') &&
            getline(ss, userName, ';') &&
            getline(ss, userPassword, ';') &&
            getline(ss, userRoleStr)) {
            
            unsigned int userRole = stoi(userRoleStr);

            Users newUser(userID, userName, userPassword, userRole);
            users.push_back(newUser);
        } else {
            cerr << "Error: Invalid line format in " << accFile << endl;
        }
    }

    file.close();
}
void initPatient() {
    ifstream file(patientInfoFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << patientInfoFile << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string userID, patientName, DOB, gender, phoneNumber, email, 
                    address, medicalHistoryStr, standingAppointmentsStr, emergencyContact, medicalResultStr;
        double cash;

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
        ss >> cash;

        vector<string> medicalHistory;
        istringstream medHistoryStream(medicalHistoryStr);
        string medItem;
        while (getline(medHistoryStream, medItem, ',')) {
            medicalHistory.push_back(medItem);
        }
        vector<string> standingAppointments;
        istringstream standingApptStream(standingAppointmentsStr);
        string standingApptItem;
        while (getline(standingApptStream, standingApptItem, ',')) {
            standingAppointments.push_back(standingApptItem);
        }
        vector<string> medicalResult;
        istringstream medicalResultStream(medicalResultStr);
        string resultItem;
        while (getline(medicalResultStream, resultItem, ',')) {
            medicalResult.push_back(resultItem);
        }

        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getUserID() == userID && users[i].getUserRole() == 3) {
                Patient newPatient(users[i].getUserID(), users[i].getUserName(), users[i].getUserPassword(), users[i].getUserRole(),
                                   patientName, DOB, gender, phoneNumber, email, address, 
                                   medicalHistory, standingAppointments, emergencyContact, cash, medicalResult);
                patients.push_back(newPatient);
                break; 
            }
        }
    }
    file.close();
}
void initDoctor() {
    ifstream file(doctorInfoFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << doctorInfoFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string userID, name, DOB, gender, phoneNumber, email, address, specialization, appointmentScheduleStr;

        getline(ss, userID, ';');
        getline(ss, name, ';');
        getline(ss, DOB, ';');
        getline(ss, gender, ';');
        getline(ss, phoneNumber, ';');
        getline(ss, email, ';');
        getline(ss, address, ';');
        getline(ss, specialization, ';');
        getline(ss, appointmentScheduleStr, ';');

        vector<string> appointmentSchedule;
        istringstream scheduleStream(appointmentScheduleStr);
        string scheduleItem;
        while (getline(scheduleStream, scheduleItem, ',')) {
            appointmentSchedule.push_back(scheduleItem);
        }

        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getUserID() == userID && users[i].getUserRole() == 1) { 
                Doctor newDoctor(users[i].getUserID(), users[i].getUserName(), users[i].getUserPassword(), users[i].getUserRole(),
                                 name, DOB, gender, phoneNumber, email, address, 
                                 specialization, appointmentSchedule);
                doctors.push_back(newDoctor);
                break; 
            }
        }
    }

    file.close();
}
void initAssistant() {
    ifstream file(assistantInfoFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << assistantInfoFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string userID, name, DOB, gender, phoneNumber, email, address;

        getline(ss, userID, ';');
        getline(ss, name, ';');
        getline(ss, DOB, ';');
        getline(ss, gender, ';');
        getline(ss, phoneNumber, ';');
        getline(ss, email, ';');
        getline(ss, address, ';');

        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getUserID() == userID && users[i].getUserRole() == 2) {
                Assistant newAssistant(users[i].getUserID(), users[i].getUserName(), users[i].getUserPassword(), users[i].getUserRole(),
                                       name, DOB, gender, phoneNumber, email, address);
                assistants.push_back(newAssistant);
                break;
            }
        }
    }
    file.close();
}
void initialization() {
    initUsers();
    initPatient();
    initDoctor();
    initAssistant();
}

void updateDoctorInfoFiles(vector<Doctor>& doctors) {
    ofstream doctorFile("doctorInfo.txt", ios::trunc);
    if (doctorFile.is_open()) {
        for (const auto& doctor : doctors) {
            doctorFile << doctor.getUserID() << ";" << doctor.getDoctorName() << ";" << doctor.getDOB() << ";"
                       << doctor.getGender() << ";" << doctor.getPhoneNumber() << ";" << doctor.getEmail() << ";"
                       << doctor.getAddress() << ";" << doctor.getSpecialization() << ";";

            const auto& apptSchedule = doctor.getAppointmentSchedule();
            for (size_t i = 0; i < apptSchedule.size(); ++i) {
                doctorFile << apptSchedule[i];
                if (i < apptSchedule.size() - 1) doctorFile << ",";
            }
            doctorFile << "\n";
        }
        doctorFile.close();
    } else {
        cerr << "Error: Could not open doctorInfo.txt to save updated schedule.\n";
    }
}
void updatePatientInfoFiles(vector<Patient>& patients) {
    ofstream patientFile("patientInfo.txt", ios::trunc);
    if (patientFile.is_open()) {
        for (const auto& patient : patients) {
            patientFile << patient.getUserID() << ";" << patient.getPatientName() << ";" << patient.getDOB() << ";"
                        << patient.getGender() << ";" << patient.getPhoneNumber() << ";" << patient.getEmail() << ";"
                        << patient.getAddress() << ";";

            const auto& medHistory = patient.getMedicalHistory();
            for (size_t i = 0; i < medHistory.size(); ++i) {
                patientFile << medHistory[i];
                if (i < medHistory.size() - 1) patientFile << ",";
            }
            patientFile << ";";

            const auto& standingAppts = patient.getStandingAppointments();
            for (size_t i = 0; i < standingAppts.size(); ++i) {
                patientFile << standingAppts[i];
                if (i < standingAppts.size() - 1) patientFile << ",";
            }
            patientFile << ";" << patient.getEmergencyContact() << ";"; 

            const auto& medicalResult = patient.getMedicalResult();
            for (size_t i = 0; i < medicalResult.size(); ++i) {
                patientFile << medicalResult[i];
                if (i < medicalResult.size() - 1) patientFile << ",";
            }
            patientFile << ";" <<  patient.getCash();
            patientFile << "\n";
        }
        patientFile.close();
    } else {
        cerr << "Error: Could not open patientInfo.txt to save updated information.\n";
    }
}
void updateAssistantInfoFiles(vector<Assistant>& assistants) {
    ofstream assistantFile("assistantInfo.txt", ios::trunc);
    if (assistantFile.is_open()) {
        for (const auto& assistant : assistants) {
            assistantFile << assistant.getUserID() << ";" << assistant.getName() << ";" << assistant.getDOB() << ";"
                          << assistant.getGender() << ";" << assistant.getPhoneNumber() << ";" << assistant.getEmail() << ";"
                          << assistant.getAddress() << "\n";
        }
        assistantFile.close();
    } else {
        cerr << "Error: Could not open assistantInfo.txt to save updated information.\n";
    }
}

//Print
void printTitle(){
	cout <<"+------------------------------+-------------------------------------+\n";
	cout <<"|     TRUONG DAI HOC BACH KHOA |     PBL2: DU AN CO SO LAP TRINH     |\n";
	cout <<"+---------------+--------------+-------------------------------------+\n";
	cout <<"|  De tai 701   |    Xay dung ung dung quan ly dat lich kham benh    |\n";
	cout <<"+---------------+-------------------+--------------------------------+\n";
	cout <<"|          Sinh vien thuc hien      |      Giang vien huong dan:     |\n";
	cout <<"+--------------------+--------------+--------------------------------+\n";
	cout <<"| Nguyen Doan Nguyen |   102230033  |        Tran Ho Thuy Tien       |\n";
	cout <<"| Ton That Van       |   102230055  |          | version 1.1 |       |\n";
	cout <<"+--------------------+--------------+--------------------------------+\n";
}
void startUpScreen() {
    cout << "------------------------------------------------------------" << endl;
    cout << "|                 Welcome to the DUT Hospital              |" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "|                         1. Login                         |" << endl;
    cout << "|                         2. Signup                        |" << endl;
    cout << "|                         3. Exit                          |" << endl;
    cout << "------------------------------------------------------------" << endl;
}

//Processing
    //Patient
void asPatient() {
    auto patientIt = find_if(patients.begin(), patients.end(),
        [](const Patient& patient) { return patient.getUserID() == currentUserID; });
    if (patientIt == patients.end()) {
        cerr << "Error: Patient not found." << endl;
        return;
    }
    Patient& currentPatient = *patientIt;

    int choice;
    do {
        system("cls");
        cout << "------------------- Patient Menu -------------------" << endl;
        cout << "|       1. Show Patient Information                |" << endl;
        cout << "|       2. Update Patient Information              |" << endl;
        cout << "|       3. Book an Appointment                     |" << endl;
        cout << "|       4. View and Cancel Appointments            |" << endl;
        cout << "|       5. View Appointment History                |" << endl; 
        cout << "|       6. View medical result                     |" << endl;
        cout << "|       7. Manage Account                          |" << endl;
        cout << "|       0. Logout                                  |" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                currentPatient.showPatientInfo();
                cout << "Enter to continue."; cin.ignore(); cin.get();
                break;

            case 2: 
                currentPatient.updatePatientInfoMenu(patients);
                updatePatientInfoFiles(patients);
                break;

            case 3:
                currentPatient.bookAppointment(doctors, patients);
                updateDoctorInfoFiles(doctors);
                updatePatientInfoFiles(patients);
                sleep(1.5);
                break;

            case 4:
                currentPatient.viewAndCancelAppointments(doctors, patients);
                updateDoctorInfoFiles(doctors);
                updatePatientInfoFiles(patients);
                cout << "Enter to continue."; cin.ignore(); cin.get();
                break;

            case 5: 
                currentPatient.viewAppointmentHistory(doctors);
                sleep(1.5);
                break;

            case 6:
                currentPatient.viewMedicalResults(doctors);
                cout << "Enter to continue."; cin.ignore(); cin.get();
                break;

            case 7:
                currentPatient.manageAccount(users);
                break;

            case 0:
                cout << "Logging out from Patient Menu." << endl; sleep(1.5);
                currentUserID = "";
                break;

            default:
                cout << "Invalid choice. Please try again." << endl; sleep(1.5);
                break;
        }
    } while (choice != 0);
}
    //Doctor
void asDoctor() {
    auto doctorIt = find_if(doctors.begin(), doctors.end(),
        [](const Doctor& doctor) { return doctor.getUserID() == currentUserID; });
    if (doctorIt == doctors.end()) {
        cerr << "Error: Doctor not found." << endl;
        return;
    }
    Doctor& currentDoctor = *doctorIt;

    int choice;
    do {
        system("cls");
        cout << "------------------- Doctor Menu -------------------" << endl;
        cout << "|       1. Show Doctor Information                |" << endl;
        cout << "|       2. Update Doctor Information              |" << endl;
        cout << "|       3. View Appointment Schedule              |" << endl;
        cout << "|       4. Manage Account                         |" << endl;
        cout << "|       0. Exit                                   |" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                currentDoctor.showDoctorInfo();
                cout << "Enter to continue."; cin.ignore(); cin.get();
                break;

            case 2:
                currentDoctor.updateDoctorInfoMenu(doctors);
                updateDoctorInfoFiles(doctors);
                break;

            case 3:
                currentDoctor.manageAppointmentSchedule(doctors, patients);
                updateDoctorInfoFiles(doctors);
                updatePatientInfoFiles(patients);
                cout << "Returning to Doctor Menu." << endl; sleep(1.5);
                break;

            case 4:
                currentDoctor.manageAccount(users);
                break;

            case 0:
                cout << "Exiting Doctor Menu." << endl; sleep(1.5);
                currentUserID = "";
                break;

            default:
                cout << "Invalid choice. Please try again." << endl; sleep(1.5);
                break;
        }
    } while (choice != 0);
}
    //Admin
void asAdmin(){
    int choice;
    do {
        Users newUser;
        string blackList = "", newUserID = "", newUserName = "", newUserPassword = "", newUserRole = "";
        system("cls");
        cout << "------------------- Admin Menu ---------------------" << endl;
        cout << "|       1. Show Account Information                |" << endl;
        cout << "|       2. Delete Account                          |" << endl;
        cout << "|       3. Create Account                          |" << endl;
        cout << "|       4. Exit                                    |" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                Admin :: showAccount(accFile);
                cout << "Enter to continue."; cin.ignore(); cin.get();
                break;

            case 2: 
                char temp;
                Admin :: showAccount(accFile);
                cout  << "Enter the ID you want to delete (0 to exit)    : "; cin >> blackList; 
                if (blackList == "0") break;

                cout << "Are you sure you want to delete?(Y/N)          : "; cin >> temp;
                if (temp == 'Y' || temp == 'y') {
                    Admin :: deleteAccount(blackList);
                    cout << "Account deleted successfully!\n";
                } else {
                    cout << "Operation canceled.\n";
                }
                break;
            case 3:
                Admin :: createAccount(doctors, assistants);
                cout << "Create Account successful! Return to menu.\n"; sleep(1.5);
                break;

            case 4:
                cout << "Exiting Admin Menu." << endl; sleep(1.5);
                currentUserID = "";
                break;

            default:
                cout << "Invalid choice. Please try again." << endl; sleep(1.5);
                break;
        }

    } while (choice != 4);

}
    //Assistant
void asAssistant() {
    auto assistantIt = find_if(assistants.begin(), assistants.end(),
        [](const Assistant& assistant) { return assistant.getUserID() == currentUserID; });
    if (assistantIt == assistants.end()) {
        cerr << "Error: Assistant not found." << endl;
        return;
    }
    Assistant& currentAssistant = *assistantIt;

    int choice;
    do {
        system("cls");
        cout << "------------------- Assistant Menu -------------------" << endl;
        cout << "|       1. Show Assistant Information                |" << endl;
        cout << "|       2. Update Assistant Information              |" << endl;
        cout << "|       3. View Appointment Schedule                 |" << endl;
        cout << "|       4. Manage Account                            |" << endl;
        cout << "|       0. Logout                                    |" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                currentAssistant.showAssistantInfo();
                cout << "Enter to continue."; cin.ignore(); cin.get();
                break;

            case 2:
                currentAssistant.updateAssistantInfoMenu(assistants);
                updateAssistantInfoFiles(assistants);
                break;

            case 3:
                currentAssistant.viewAppointmentSchedule(doctors, patients);
                break;

            case 4:
                currentAssistant.manageAccount(users);
                break;

            case 0:
                cout << "Logging out from Assistant Menu." << endl; sleep(1.5);
                currentUserID = "";
                break;

            default:
                cout << "Invalid choice. Please try again." << endl; sleep(1.5);
                break;
        }
    } while (choice != 0);
}
    //Process
void processProgram(){
    int currentUserRole;
    for (const auto& user : users) {
        if (user.getUserID() == currentUserID) {
            currentUserRole = user.getUserRole();
            break;
        }
    }
    switch (currentUserRole)
    {   
        case 0:
            asAdmin();
        case 1:
            asDoctor();
            break;
        case 2:
            asAssistant();
            break;
        case 3:
            asPatient();
            break;
        default:
            break;
    }
}

//Startup
string userLogin() {
    string userName, userPassword;
    int attempts = 0;
    system("cls"); cout << "------------------------------Login------------------------------\n";
    while (attempts < 5) {
        cout << setw(50) << "Enter your user name" << ": "; cin >> userName;
        cout << setw(50) << "Enter your password" << ": ";  cin >> userPassword;
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getUserName() == userName && users[i].getUserPassword() == userPassword) {
                cout << "---------------------Logged in successfully!---------------------" << endl;
                return users[i].getUserID();
            }
        }
        attempts++;
        if (attempts >= 5) {
            cout << "---------------------------------------------------------------\n";
            cout << "Maximum login attempts reached. Access denied. Return to main menu." << endl;
            return "";
        }
        cout << "Incorrect username or password. Attempts remaining: " << (5 - attempts) << endl;

    }
    return "";
}
void userSignup() {
    string newUserName, newUserPassword;
    system("cls"); 
    cout << "------------------------------Signup------------------------------\n";
    cout << setw(50) << "Enter a username" << ": ";
    cin >> newUserName;
    for (const auto& user : users) {
        if (user.getUserName() == newUserName) {
            cout << setw(50) << "Username already exists. Please try another username.\n";
            return;
        }
    }
    cout << setw(50) << "Enter a password" << ": ";
    cin >> newUserPassword;

    string newUserID;
    if (!patients.empty()) {
        int lastPatientID = stoi(patients.back().getUserID().substr(2)); 
        lastPatientID++;
        newUserID = "PT" + string(4 - to_string(lastPatientID).length(), '0') + to_string(lastPatientID);
    } else {
        newUserID = "PT0001";
    }

    Patient newPatient(newUserID, newUserName, newUserPassword, 3, "Unknown", "Unknown", "Unknown",
                       "Unknown", "Unknown", "Unknown", {}, {}, "Unknown", 0.0, {});
    users.push_back(newPatient); 
    patients.push_back(newPatient);

    ofstream accFileOut(accFile, ios::app);
    if (accFileOut.is_open()) {
        accFileOut << newUserID << ";" << newUserName << ";" << newUserPassword << ";3\n";
        accFileOut.close();
    } else {
        cerr << "Error: Could not open " << accFile << " to add new account.\n";
    }

    ofstream patientInfoOut(patientInfoFile, ios::app);
    if (patientInfoOut.is_open()) {
        patientInfoOut << newUserID << ";Unknown;Unknown;Unknown;Unknown;Unknown;Unknown;;;Unknown;;0.0\n";
        patientInfoOut.close();
    } else {
        cerr << "Error: Could not open " << patientInfoFile << " to add new patient info.\n";
    }

    cout << setw(50) << "Signup successful! Returning to main menu.\n";
    sleep(2);
}
void process(){
   int userChoice;
    do {
         system("cls"); 
        startUpScreen();
        cout << setw(53)<< left << "Choose your action" << setw(4) << ":";
        cin >> userChoice;
        switch (userChoice) {
            case 1:
                currentUserID = userLogin();
                if (currentUserID != "") processProgram();
                break;
            case 2:
                userSignup();
                cout << "Returning to main menu." << endl; sleep(1.5);
                break;
            case 3:
                cout << "Exiting the program." << endl;
                sleep(1.5);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                sleep(1.5);
                break;
        }
    } while (userChoice != 3);
}
void startup() {
    system("cls");
    printTitle(); sleep(2);
    process();    
}

//Close
void closeProgram() {
    updateDoctorInfoFiles(doctors);
    updatePatientInfoFiles(patients);
    updateAssistantInfoFiles(assistants);
    system("cls");
    printTitle();
}
//Main
int main() {
    initialization(); 
    startup();
    closeProgram();
    return 0;
}
