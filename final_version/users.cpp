#include "users.h"

// Default constructor
Users::Users() : userRole(0) {}

// Parameterized constructor
Users::Users(const string& userID, const string& userName, const string& userPassword, unsigned int userRole)
    : userID(userID), userName(userName), userPassword(userPassword), userRole(userRole) {}

// Destructor
Users::~Users() {}

// Get methods
string Users::getUserID() const { return userID; }
string Users::getUserName() const { return userName; }
string Users::getUserPassword() const { return userPassword; }
unsigned int Users::getUserRole() const { return userRole; }

// Set methods
void Users::setUserID(const string& newUserID) { userID = newUserID; }
void Users::setUserName(const string& newUserName) { userName = newUserName; }
void Users::setUserPassword(const string& newUserPassword) { userPassword = newUserPassword; }
void Users::setUserRole(unsigned int newUserRole) { userRole = newUserRole; }

// Other methods

void Users::manageAccount(vector<Users>& users) {
    int choice;
    do {
        system("cls");
        cout << "-----------------Manage Account----------------" << endl;
        cout << "| 1. Change Username                          |" << endl;
        cout << "| 2. Change Password                          |" << endl;
        cout << "| 3. Return                                   |" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string newUsername;
                cout << "Enter new username: ";
                getline(cin, newUsername);
                this->setUserName(newUsername);
                for (auto& user : users) {
                    if (user.getUserID() == this->getUserID()) {
                        user.setUserName(newUsername);
                        break;
                    }
                }
                cout << "Username updated successfully.\n"; sleep(1.5);
                break;
            }
            case 2: {
                string oldPassword, newPassword;
                cout << "Enter your current password: "; getline(cin, oldPassword);
                if (oldPassword != getUserPassword()) {
                    cout << "Incorrect password. Please try again.\n"; sleep(1.5);
                    break;
                }
                cout << "Enter new password: ";
                getline(cin, newPassword);
                this->setUserPassword(newPassword);
                for (auto& user : users) {
                    if (user.getUserID() == this->getUserID()) {
                        user.setUserPassword(newPassword);
                        break;
                    }
                }
                cout << "Password updated successfully.\n"; sleep(1.5);
                break;
            }
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again.\n"; sleep(1.5);
                break;
        }

        ofstream accFileOut("account.txt", ios::trunc);
        if (accFileOut.is_open()) {
            for (const auto& user : users) {
                accFileOut << user.getUserID() << ";" << user.getUserName() << ";" << user.getUserPassword() << ";" << user.getUserRole() << "\n";
            }
            accFileOut.close();
        } else {
            cerr << "Error: Could not open account.txt to update account information.\n";
        }
    } while (choice != 3);
}
