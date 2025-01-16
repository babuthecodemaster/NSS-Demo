#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void handleLogin(const string& username, const string& password) {
    // Example login check (replace with actual validation logic)
    if (username == "admin" && password == "1234") {
        cout << "Location: afterLR.html?action=login\r\n\r\n";
    } else {
        cout << "Location: afterLR.html?action=error\r\n\r\n";
    }
}

void handleRegistration(const string& username, const string& password, const string& confirm_password) {
    // Simple password matching check
    if (password == confirm_password) {
        // Here you would typically save the username and password to a database
        cout << "Location: afterLR.html?action=register\r\n\r\n";
    } else {
        cout << "Location: afterLR.html?action=error\r\n\r\n";
    }
}

int main() {
    // Set content-type header
    cout << "Content-type: text/html\r\n\r\n";

    // Get form data from environment variables (using POST method)
    string query = getenv("QUERY_STRING");
    string action;

    // Determine the action based on the query string
    if (query.find("action=login") != string::npos) {
        // Extract login data
        string username = getenv("USERNAME");
        string password = getenv("PASSWORD");
        handleLogin(username, password);
    } else if (query.find("action=register") != string::npos) {
        // Extract registration data
        string username, password, confirm_password;
        size_t pos_username = query.find("new-username=");
        size_t pos_password = query.find("&new-password=");
        size_t pos_confirm = query.find("&confirm-password=");

        if (pos_username != string::npos && pos_password != string::npos && pos_confirm != string::npos) {
            username = query.substr(pos_username + 13, pos_password - (pos_username + 13));
            password = query.substr(pos_password + 14, pos_confirm - (pos_password + 14));
            confirm_password = query.substr(pos_confirm + 17);
            handleRegistration(username, password, confirm_password);
        } else {
            cout << "Location: afterLR.html?action=error\r\n\r\n"; // Invalid data
        }
    } else {
        cout << "Location: afterLR.html?action=error\r\n\r\n"; // Unknown action
    }

    return 0;
}