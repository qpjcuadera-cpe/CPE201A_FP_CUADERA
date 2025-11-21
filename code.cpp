#include <iostream>
#include <string>
#include <vector>
#include <fstream>   // for file handling
#include <conio.h>   // for getch()
using namespace std;

struct Request {
    string name;
    string room;
    string issue;
};

void studentMenu(vector<Request> &requests);
void staffMenu(vector<Request> &requests);
bool login(string role);
string getPassword();
void saveRequests(const vector<Request> &requests);
void loadRequests(vector<Request> &requests);

int main() {
    vector<Request> requests;
    int choice;

    // Load existing requests from file
    loadRequests(requests);

    cout << "=========================================\n";
    cout << "   SCHOOL MAINTENANCE REQUEST SYSTEM\n";
    cout << "=========================================\n";

    while (true) {
        cout << "\n[1] Login as Student";
        cout << "\n[2] Login as Staff";
        cout << "\n[3] Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (login("student")) {
                    studentMenu(requests);
                } else {
                    cout << "\nInvalid student credentials!\n";
                }
                break;
            case 2:
                if (login("staff")) {
                    staffMenu(requests);
                } else {
                    cout << "\nInvalid staff credentials!\n";
                }
                break;
            case 3:
                cout << "\nSaving data before exiting...\n";
                saveRequests(requests);
                cout << "Exiting program... Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Try again.\n";
        }
    }
    return 0;
}

string getPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != 13) { // 13 = Enter key
        if (ch == 8) { // 8 = Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // erase last '*'
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

bool login(string role) {
    string user, pass;
    cout << "\nEnter username: ";
    cin >> user;
    cout << "Enter password: ";
    pass = getPassword();

    if (role == "student" && user == "student" && pass == "1234")
        return true;
    if (role == "staff" && user == "staff" && pass == "admin")
        return true;

    return false;
}

void studentMenu(vector<Request> &requests) {
    int choice;
    Request req;

    do {
        cout << "\n===== STUDENT MENU =====\n";
        cout << "[1] Submit Maintenance Request\n";
        cout << "[2] View Submitted Requests\n";
        cout << "[3] Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "\nEnter your name: ";
                getline(cin, req.name);
                cout << "Enter your room number: ";
                getline(cin, req.room);
                cout << "Describe the issue: ";
                getline(cin, req.issue);

                requests.push_back(req);
                saveRequests(requests);  // Save to file after new request
                cout << "\nRequest submitted successfully!\n";
                break;

            case 2:
                if (requests.empty()) {
                    cout << "\nNo requests submitted yet.\n";
                } else {
                    cout << "\nYour Submitted Requests:\n";
                    for (size_t i = 0; i < requests.size(); i++) {
                        cout << "\nRequest #" << i + 1
                             << "\nName: " << requests[i].name
                             << "\nRoom: " << requests[i].room
                             << "\nIssue: " << requests[i].issue << endl;
                    }
                }
                break;

            case 3:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 3);
}

void staffMenu(vector<Request> &requests) {
    int choice;

    do {
        cout << "\n===== STAFF MENU =====\n";
        cout << "[1] View All Maintenance Requests\n";
        cout << "[2] Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (requests.empty()) {
                    cout << "\nNo maintenance requests available.\n";
                } else {
                    cout << "\nAll Maintenance Requests:\n";
                    for (size_t i = 0; i < requests.size(); i++) {
                        cout << "\nRequest #" << i + 1
                             << "\nName: " << requests[i].name
                             << "\nRoom: " << requests[i].room
                             << "\nIssue: " << requests[i].issue << endl;
                    }
                }
                break;

            case 2:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 2);
}

// Save requests to file
void saveRequests(const vector<Request> &requests) {
    ofstream file("requests.txt");
    for (const auto &req : requests) {
        file << req.name << '\n'
        
             << req.room << '\n'
             << req.issue << '\n'
             << "-----\n"; // separator
    }
    file.close();
}

// Load requests from file
void loadRequests(vector<Request> &requests) {
    ifstream file("requests.txt");
    if (!file.is_open()) return;

    Request req;
    string line;
    while (getline(file, req.name)) {
        if (req.name.empty()) break;
        getline(file, req.room);
        getline(file, req.issue);
        getline(file, line); // read separator line "-----"
        requests.push_back(req);
    }
    file.close();
}
