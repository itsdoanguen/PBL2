#include "admin.h"
#include "doctor.h"
#include <random>
#include "users.h"
#include "assistant.h"

const string patientInfoFile = "patientInfo.txt";
const string doctorInfoFile = "doctorInfo.txt";
const string assistantInfoFile = "assistantInfo.txt";
const string accFile = "account.txt";

extern std::vector<Users> users;

Admin :: Admin(){}

Admin :: ~Admin(){}

Admin::Admin(const string& userID, const string& userName, const string& userPassword, unsigned int userRole,
                     const string& name, const string& DOB, const string& gender, 
                     const string& phoneNumber, const string& email, const string& address)
        : Users(userID, userName, userPassword, userRole),
          name(name), DOB(DOB), gender(gender), phoneNumber(phoneNumber),
          email(email), address(address) {}

void Admin :: showAccount(string accFile){
    users.clear();
    
    ifstream file(accFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << accFile << endl;
        return;
    }
    system("cls");
    cout << "-----------------Account Information----------------\n";
       cout << "|" << setw(9) << right << "userID" <<  "|" << setw(15) << right << "userName" << "|" << setw(15)  << "userPassword" << "|"  << setw(8) << "userRole" <<  "|" << endl;
    cout << "----------------------------------------------------\n";
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string userID, userName, userPassword, userRoleStr;

        if (getline(ss, userID, ';') &&
            getline(ss, userName, ';') &&
            getline(ss, userPassword, ';') &&
            getline(ss, userRoleStr)) {
            
            unsigned int userRole = stoi(userRoleStr); if (userRole == 0) continue;
            Users newUser(userID, userName, userPassword, userRole);
            users.push_back(newUser);
            cout << "|" << setw(9) << right << userID <<  "|" << setw(15) << right << userName << "|" << setw(15)  << userPassword << "|"  << setw(8) << userRole <<  "|" << endl;
        } else {
            cerr << "Error: Invalid line format in " << accFile << endl;
        }
    }
    cout << "----------------------------------------------------\n";
    file.close();
}

void deleteForm(const string accFile, string blackID){
    vector<string> reMake;
    ifstream file(accFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << accFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string UserID = line.substr(0, blackID.size()-1);
        if(UserID != blackID) reMake.push_back(line);
        else {
            cerr << "Error: Invalid line format in " << accFile << endl;
        }
    }
    file.close();
    ofstream accFileOut(accFile, ios::trunc);

    if (accFileOut.is_open()) {
        for (const auto& infor : reMake) {
            accFileOut << infor << '\n';
        }
    }
    else {
        cerr << "Error: Could not open account.txt to delete.\n";
    }
    accFileOut.close();    
}

void Admin::deleteAccount(string blackList) {
    int blackRole;
    string blackID;
    bool Inlist = false;

    if (blackList == "ADMIN") {
        cout << "Admin account cannot be deleted!\n";
        return;
    }

    users.clear();
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
            if (userID != blackList) {
                Users newUser(userID, userName, userPassword, userRole);
                users.push_back(newUser);
            } else {
                Inlist = true;
                blackID = userID;
                blackRole = userRole;
            }
        } else {
            cerr << "Error: Invalid line format in " << accFile << endl;
        }
    }
    file.close();

    if (!Inlist) {
        cout << "User cannot be found to delete!\n";
        return;
    }

    ofstream accFileOut(accFile, ios::trunc);
    if (accFileOut.is_open()) {
        for (const auto& user : users) {
            accFileOut << user.getUserID() << ";" << user.getUserName() << ";" 
                       << user.getUserPassword() << ";" << user.getUserRole() << ";\n";
        }
    } else {
        cerr << "Error: Could not open account.txt to delete.\n";
    }
    accFileOut.close();

    // Delete info based on role
    switch (blackRole) {
        case 1:
            deleteForm(doctorInfoFile, blackID);
            break;
        case 2:
            deleteForm(patientInfoFile, blackID);
            break;
        case 3:
            deleteForm(assistantInfoFile, blackID);
            break;
        default:
            break;
    }
}

string generationRandomString(size_t length){
    string Character = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, Character.size() - 1);
    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += Character[distribution(generator)];
    }
    return randomString;
}

void setupUsers(string &newUserName, string &newUserPassword, int lengthRandomString){
    newUserName =  generationRandomString(lengthRandomString);
    newUserPassword = generationRandomString(lengthRandomString);
}

string nextUserID(string lastUserID){
    int numberIdPositionBegin = 2, res = 0, temp = 1;
    int position = lastUserID.size() - 1;
    while(temp == 1){
        res = lastUserID[position] - '0';
        res += temp; temp--;
        if(res == 10){
            res = 0;
            temp = 1;
        }    
        lastUserID[position] = char(res + 48);
        position--;
    }
    return lastUserID;
}

void InputAccountForm(Users newUser){
    ofstream accFileOut(accFile, ios::app);
    if (accFileOut.is_open()) {
        accFileOut << newUser.getUserID() << ";" << newUser.getUserName() 
            << ";" << newUser.getUserPassword() << ";" << newUser.getUserRole() << '\n';
        accFileOut.close();
    } else {
        cerr << "Error: Could not open " << accFile << " to add new account.\n";
    }
    accFileOut.close();
}


void createAccountDoctor(vector<Doctor>& doctors) {
    int lengthRandomString = 6, newUserRole = 1;
    string newUserID, newUserName, newUserPassword;
    setupUsers(newUserName, newUserPassword, lengthRandomString);
    string lastDoctorID = doctors[doctors.size() - 1].getUserID();
    newUserID = nextUserID(lastDoctorID);

    Doctor newDoctor(newUserID, newUserName, newUserPassword, newUserRole, "Unknown", "Unknown", "Unknown",
                     "Unknown", "Unknown", "Unknown", "Unknown", {});

    doctors.push_back(newDoctor);
    users.push_back(newDoctor);

    InputAccountForm(newDoctor);

    ofstream doctorFile(doctorInfoFile, ios::app);
    doctorFile << newUserID << ";Unknow;Unknow;Unknow;Unknow;Unknow;Unknow;Unknow;" << '\n';
    doctorFile.close();
}

void createAccountAssistant(vector<Assistant>& assistants) {
    int lengthRandomString = 6, newUserRole = 2;
    string newUserID, newUserName, newUserPassword;
    setupUsers(newUserName, newUserPassword, lengthRandomString);
    string lastAssistantID = assistants[assistants.size() - 1].getUserID();
    newUserID = nextUserID(lastAssistantID);

    Assistant newAssistant(newUserID, newUserName, newUserPassword, newUserRole, "Unknown", "Unknown", "Unknown",
                           "Unknown", "Unknown", "Unknown");

    assistants.push_back(newAssistant);
    users.push_back(newAssistant); 

    InputAccountForm(newAssistant);

    ofstream assistantFile(assistantInfoFile, ios::app);
    assistantFile << newUserID << ";Unknow;Unknow;Unknow;Unknow;Unknow;Unknow;" << '\n';
    assistantFile.close();
}

void Admin::createAccount(vector<Doctor>& doctors, vector<Assistant>& assistants) {
    int choice;
    cout << "-----------------Create Account----------------\n";
    cout << "|       1. Doctor Account                    |\n";
    cout << "|       2. Assistant Account                 |\n";
    cout << "|       0. Exit                              |\n";
    cout << "----------------------------------------------\n";
    cout << "Choose an option: "; cin >> choice;
    switch (choice) {
        case 1:
            createAccountDoctor(doctors);
            break;
        case 2:
            createAccountAssistant(assistants);
            break;
        case 0:
            cout << "Exiting successful.\n"; sleep(1.5);
            break;
        default:
            cout << "Invalid choice. Please try again.\n"; sleep(2);
            break;
    }
    return;
}