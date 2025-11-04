#include "train_system.h"
#include <cstring>
#include <cstdlib>

// Simple structures for data storage
struct User {
    char username[21];
    char password[31];
    char name[16]; // 5 Chinese characters * 3 bytes + 1
    char mail_addr[31];
    int privilege;
    bool logged_in;
};

struct Station {
    char name[31]; // 10 Chinese characters * 3 bytes + 1
};

struct Train {
    char train_id[21];
    int station_num;
    int seat_num;
    Station stations[100];
    int prices[99]; // stationNum - 1 prices
    char start_time[6]; // "hh:mm"
    int travel_times[99]; // stationNum - 1 travel times
    int stopover_times[98]; // stationNum - 2 stopover times
    char sale_date_from[6]; // "mm-dd"
    char sale_date_to[6]; // "mm-dd"
    char type;
    bool released;
};

struct Order {
    char username[21];
    char train_id[21];
    char from_station[31];
    char to_station[31];
    char leaving_time[17]; // "mm-dd hh:mm"
    char arriving_time[17]; // "mm-dd hh:mm"
    int price;
    int num;
    int status; // 0: success, 1: pending, 2: refunded
};

TrainSystem::TrainSystem() {
    // Initialize with reasonable capacities
    users = new User[10000];
    trains = new Train[1000];
    orders = new Order[100000];
    user_count = 0;
    train_count = 0;
    order_count = 0;
    logged_in_count = 0;
}

TrainSystem::~TrainSystem() {
    delete[] users;
    delete[] trains;
    delete[] orders;
}

int TrainSystem::find_user(const std::string& username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username.c_str()) == 0) {
            return i;
        }
    }
    return -1;
}

int TrainSystem::find_train(const std::string& train_id) {
    for (int i = 0; i < train_count; i++) {
        if (strcmp(trains[i].train_id, train_id.c_str()) == 0) {
            return i;
        }
    }
    return -1;
}

bool TrainSystem::is_logged_in(const std::string& username) {
    for (int i = 0; i < logged_in_count; i++) {
        int user_idx = logged_in_users[i];
        if (strcmp(users[user_idx].username, username.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

// User management implementations
int TrainSystem::add_user(const std::string& cur_username, const std::string& username,
                         const std::string& password, const std::string& name,
                         const std::string& mail_addr, int privilege) {
    // Check if username already exists
    if (find_user(username) != -1) {
        return -1;
    }

    // First user case
    if (user_count == 0) {
        User& new_user = users[user_count++];
        strcpy(new_user.username, username.c_str());
        strcpy(new_user.password, password.c_str());
        strcpy(new_user.name, name.c_str());
        strcpy(new_user.mail_addr, mail_addr.c_str());
        new_user.privilege = 10;
        new_user.logged_in = false;
        return 0;
    }

    // Check current user exists and is logged in
    int cur_user_idx = find_user(cur_username);
    if (cur_user_idx == -1 || !is_logged_in(cur_username)) {
        return -1;
    }

    // Check privilege requirements
    if (privilege >= users[cur_user_idx].privilege) {
        return -1;
    }

    // Add new user
    User& new_user = users[user_count++];
    strcpy(new_user.username, username.c_str());
    strcpy(new_user.password, password.c_str());
    strcpy(new_user.name, name.c_str());
    strcpy(new_user.mail_addr, mail_addr.c_str());
    new_user.privilege = privilege;
    new_user.logged_in = false;

    return 0;
}

int TrainSystem::login(const std::string& username, const std::string& password) {
    int user_idx = find_user(username);
    if (user_idx == -1) {
        return -1;
    }

    // Check if already logged in
    if (is_logged_in(username)) {
        return -1;
    }

    // Check password
    if (strcmp(users[user_idx].password, password.c_str()) != 0) {
        return -1;
    }

    // Add to logged in users
    logged_in_users[logged_in_count++] = user_idx;
    users[user_idx].logged_in = true;

    return 0;
}

int TrainSystem::logout(const std::string& username) {
    int user_idx = find_user(username);
    if (user_idx == -1) {
        return -1;
    }

    // Find and remove from logged in users
    for (int i = 0; i < logged_in_count; i++) {
        if (logged_in_users[i] == user_idx) {
            // Shift remaining elements
            for (int j = i; j < logged_in_count - 1; j++) {
                logged_in_users[j] = logged_in_users[j + 1];
            }
            logged_in_count--;
            users[user_idx].logged_in = false;
            return 0;
        }
    }

    return -1; // Not logged in
}

std::string TrainSystem::query_profile(const std::string& cur_username, const std::string& username) {
    int cur_user_idx = find_user(cur_username);
    int target_user_idx = find_user(username);

    if (cur_user_idx == -1 || target_user_idx == -1) {
        return "-1";
    }

    // Check if current user is logged in
    if (!is_logged_in(cur_username)) {
        return "-1";
    }

    // Check permission: same user or higher privilege
    if (strcmp(cur_username.c_str(), username.c_str()) != 0 &&
        users[cur_user_idx].privilege <= users[target_user_idx].privilege) {
        return "-1";
    }

    // Return user info
    std::string result = std::string(users[target_user_idx].username) + " " +
                        std::string(users[target_user_idx].name) + " " +
                        std::string(users[target_user_idx].mail_addr) + " " +
                        std::to_string(users[target_user_idx].privilege);
    return result;
}

std::string TrainSystem::modify_profile(const std::string& cur_username, const std::string& username,
                                       const std::string& password, const std::string& name,
                                       const std::string& mail_addr, int privilege) {
    int cur_user_idx = find_user(cur_username);
    int target_user_idx = find_user(username);

    if (cur_user_idx == -1 || target_user_idx == -1) {
        return "-1";
    }

    // Check if current user is logged in
    if (!is_logged_in(cur_username)) {
        return "-1";
    }

    // Check permission: same user or higher privilege
    if (strcmp(cur_username.c_str(), username.c_str()) != 0 &&
        users[cur_user_idx].privilege <= users[target_user_idx].privilege) {
        return "-1";
    }

    // Check privilege modification
    if (privilege != -1 && privilege >= users[cur_user_idx].privilege) {
        return "-1";
    }

    // Apply modifications
    if (!password.empty()) {
        strcpy(users[target_user_idx].password, password.c_str());
    }
    if (!name.empty()) {
        strcpy(users[target_user_idx].name, name.c_str());
    }
    if (!mail_addr.empty()) {
        strcpy(users[target_user_idx].mail_addr, mail_addr.c_str());
    }
    if (privilege != -1) {
        users[target_user_idx].privilege = privilege;
    }

    // Return updated profile
    return query_profile(cur_username, username);
}

// Train management implementations
int TrainSystem::add_train(const std::string& train_id, int station_num, int seat_num,
                          const std::string& stations, const std::string& prices,
                          const std::string& start_time, const std::string& travel_times,
                          const std::string& stopover_times, const std::string& sale_date,
                          char type) {
    // Check if train already exists
    if (find_train(train_id) != -1) {
        return -1;
    }

    // Add new train
    Train& new_train = trains[train_count++];
    strcpy(new_train.train_id, train_id.c_str());
    new_train.station_num = station_num;
    new_train.seat_num = seat_num;
    new_train.type = type;
    new_train.released = false;

    // Parse and copy start time
    strcpy(new_train.start_time, start_time.c_str());

    // Parse sale dates
    size_t pipe_pos = sale_date.find('|');
    if (pipe_pos != std::string::npos) {
        strcpy(new_train.sale_date_from, sale_date.substr(0, pipe_pos).c_str());
        strcpy(new_train.sale_date_to, sale_date.substr(pipe_pos + 1).c_str());
    }

    // TODO: Parse stations, prices, travel_times, stopover_times
    // This would require parsing the pipe-separated strings

    return 0;
}

int TrainSystem::release_train(const std::string& train_id) {
    int train_idx = find_train(train_id);
    if (train_idx == -1) {
        return -1;
    }

    trains[train_idx].released = true;
    return 0;
}

std::string TrainSystem::query_train(const std::string& train_id, const std::string& date) {
    int train_idx = find_train(train_id);
    if (train_idx == -1) {
        return "-1";
    }

    // TODO: Implement detailed train query
    // This would require calculating arrival/departure times and seat availability

    return "-1"; // Placeholder
}

int TrainSystem::delete_train(const std::string& train_id) {
    int train_idx = find_train(train_id);
    if (train_idx == -1) {
        return -1;
    }

    // Cannot delete released trains
    if (trains[train_idx].released) {
        return -1;
    }

    // Remove train by shifting
    for (int i = train_idx; i < train_count - 1; i++) {
        trains[i] = trains[i + 1];
    }
    train_count--;

    return 0;
}

// Ticket operations implementations
std::string TrainSystem::query_ticket(const std::string& from, const std::string& to,
                                     const std::string& date, const std::string& sort_type) {
    // TODO: Implement ticket query
    // This would require finding trains that pass through both stations
    // and calculating available seats

    return "0"; // Placeholder - no trains found
}

std::string TrainSystem::query_transfer(const std::string& from, const std::string& to,
                                       const std::string& date, const std::string& sort_type) {
    // TODO: Implement transfer query
    // This would require finding two-train transfers

    return "0"; // Placeholder - no transfers found
}

std::string TrainSystem::buy_ticket(const std::string& username, const std::string& train_id,
                                   const std::string& date, int num, const std::string& from,
                                   const std::string& to, bool queue) {
    // Check if user exists and is logged in
    int user_idx = find_user(username);
    if (user_idx == -1 || !is_logged_in(username)) {
        return "-1";
    }

    // Check if train exists and is released
    int train_idx = find_train(train_id);
    if (train_idx == -1 || !trains[train_idx].released) {
        return "-1";
    }

    // TODO: Implement ticket purchase logic
    // This would require checking seat availability, calculating price,
    // and handling queue if requested

    return "-1"; // Placeholder
}

std::string TrainSystem::query_order(const std::string& username) {
    int user_idx = find_user(username);
    if (user_idx == -1 || !is_logged_in(username)) {
        return "-1";
    }

    // TODO: Implement order query
    // This would require finding all orders for this user

    return "-1"; // Placeholder
}

int TrainSystem::refund_ticket(const std::string& username, int n) {
    int user_idx = find_user(username);
    if (user_idx == -1 || !is_logged_in(username)) {
        return -1;
    }

    // TODO: Implement ticket refund
    // This would require finding the nth order and processing refund

    return -1; // Placeholder
}

// System operations
int TrainSystem::clean() {
    user_count = 0;
    train_count = 0;
    order_count = 0;
    logged_in_count = 0;
    return 0;
}

std::string TrainSystem::exit() {
    logged_in_count = 0; // Log out all users
    return "bye";
}