#include <iostream>
#include <string>
#include "train_system.h"
#include "command_parser.h"

using namespace std;

int main() {
    TrainSystem system;
    CommandParser parser;
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

        // Parse parameters
        parser.parse(params);

        // Process commands
        if (cmd == "add_user") {
            string cur_user = parser.get_param("c");
            string username = parser.get_param("u");
            string password = parser.get_param("p");
            string name = parser.get_param("n");
            string mail_addr = parser.get_param("m");
            int privilege = 0;
            if (parser.has_param("g")) {
                privilege = stoi(parser.get_param("g"));
            }
            cout << system.add_user(cur_user, username, password, name, mail_addr, privilege) << endl;

        } else if (cmd == "login") {
            string username = parser.get_param("u");
            string password = parser.get_param("p");
            cout << system.login(username, password) << endl;

        } else if (cmd == "logout") {
            string username = parser.get_param("u");
            cout << system.logout(username) << endl;

        } else if (cmd == "query_profile") {
            string cur_user = parser.get_param("c");
            string username = parser.get_param("u");
            cout << system.query_profile(cur_user, username) << endl;

        } else if (cmd == "modify_profile") {
            string cur_user = parser.get_param("c");
            string username = parser.get_param("u");
            string password = parser.get_param("p");
            string name = parser.get_param("n");
            string mail_addr = parser.get_param("m");
            int privilege = -1;
            if (parser.has_param("g")) {
                privilege = stoi(parser.get_param("g"));
            }
            cout << system.modify_profile(cur_user, username, password, name, mail_addr, privilege) << endl;

        } else if (cmd == "add_train") {
            string train_id = parser.get_param("i");
            int station_num = stoi(parser.get_param("n"));
            int seat_num = stoi(parser.get_param("m"));
            string stations = parser.get_param("s");
            string prices = parser.get_param("p");
            string start_time = parser.get_param("x");
            string travel_times = parser.get_param("t");
            string stopover_times = parser.get_param("o");
            string sale_date = parser.get_param("d");
            char type = parser.get_param("y")[0];
            cout << system.add_train(train_id, station_num, seat_num, stations, prices,
                                   start_time, travel_times, stopover_times, sale_date, type) << endl;

        } else if (cmd == "release_train") {
            string train_id = parser.get_param("i");
            cout << system.release_train(train_id) << endl;

        } else if (cmd == "query_train") {
            string train_id = parser.get_param("i");
            string date = parser.get_param("d");
            cout << system.query_train(train_id, date) << endl;

        } else if (cmd == "delete_train") {
            string train_id = parser.get_param("i");
            cout << system.delete_train(train_id) << endl;

        } else if (cmd == "query_ticket") {
            string from = parser.get_param("s");
            string to = parser.get_param("t");
            string date = parser.get_param("d");
            string sort_type = "time";
            if (parser.has_param("p")) {
                sort_type = parser.get_param("p");
            }
            cout << system.query_ticket(from, to, date, sort_type) << endl;

        } else if (cmd == "query_transfer") {
            string from = parser.get_param("s");
            string to = parser.get_param("t");
            string date = parser.get_param("d");
            string sort_type = "time";
            if (parser.has_param("p")) {
                sort_type = parser.get_param("p");
            }
            cout << system.query_transfer(from, to, date, sort_type) << endl;

        } else if (cmd == "buy_ticket") {
            string username = parser.get_param("u");
            string train_id = parser.get_param("i");
            string date = parser.get_param("d");
            int num = stoi(parser.get_param("n"));
            string from = parser.get_param("f");
            string to = parser.get_param("t");
            bool queue = false;
            if (parser.has_param("q") && parser.get_param("q") == "true") {
                queue = true;
            }
            cout << system.buy_ticket(username, train_id, date, num, from, to, queue) << endl;

        } else if (cmd == "query_order") {
            string username = parser.get_param("u");
            cout << system.query_order(username) << endl;

        } else if (cmd == "refund_ticket") {
            string username = parser.get_param("u");
            int n = 1;
            if (parser.has_param("n")) {
                n = stoi(parser.get_param("n"));
            }
            cout << system.refund_ticket(username, n) << endl;

        } else if (cmd == "clean") {
            cout << system.clean() << endl;

        } else {
            cout << "-1" << endl; // Unknown command
        }
    }

    return 0;
}