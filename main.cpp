#include <iostream>
#include <string>
#include "train_system.h"

using namespace std;

int main() {
    TrainSystem system;
    string command;

    while (getline(cin, command)) {
        if (command.empty()) continue;

        // Parse command
        if (command == "exit") {
            cout << system.exit() << endl;
            break;
        }

        // Parse command and parameters
        string cmd;
        string params;
        size_t space_pos = command.find(' ');
        if (space_pos != string::npos) {
            cmd = command.substr(0, space_pos);
            params = command.substr(space_pos + 1);
        } else {
            cmd = command;
        }

        // Process commands
        if (cmd == "add_user") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "login") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "logout") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "query_profile") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "modify_profile") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "add_train") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "release_train") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "query_train") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "delete_train") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "query_ticket") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "query_transfer") {
            cout << "0" << endl; // Placeholder
        } else if (cmd == "buy_ticket") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "query_order") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "refund_ticket") {
            cout << "-1" << endl; // Placeholder
        } else if (cmd == "clean") {
            cout << system.clean() << endl;
        } else {
            cout << "-1" << endl; // Unknown command
        }
    }

    return 0;
}