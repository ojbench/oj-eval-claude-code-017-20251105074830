#ifndef TRAIN_SYSTEM_H
#define TRAIN_SYSTEM_H

#include <string>

// Forward declarations
struct User;
struct Train;
struct Order;

class TrainSystem {
private:
    // Core data structures
    User* users;
    Train* trains;
    Order* orders;

    int user_count;
    int train_count;
    int order_count;

    int logged_in_users[100]; // Track logged in users by user index
    int logged_in_count;

    // Helper methods
    int find_user(const std::string& username);
    int find_train(const std::string& train_id);
    bool is_logged_in(const std::string& username);

public:
    TrainSystem();
    ~TrainSystem();

    // User management
    int add_user(const std::string& cur_username, const std::string& username,
                 const std::string& password, const std::string& name,
                 const std::string& mail_addr, int privilege);
    int login(const std::string& username, const std::string& password);
    int logout(const std::string& username);
    std::string query_profile(const std::string& cur_username, const std::string& username);
    std::string modify_profile(const std::string& cur_username, const std::string& username,
                              const std::string& password, const std::string& name,
                              const std::string& mail_addr, int privilege);

    // Train management
    int add_train(const std::string& train_id, int station_num, int seat_num,
                  const std::string& stations, const std::string& prices,
                  const std::string& start_time, const std::string& travel_times,
                  const std::string& stopover_times, const std::string& sale_date,
                  char type);
    int release_train(const std::string& train_id);
    std::string query_train(const std::string& train_id, const std::string& date);
    int delete_train(const std::string& train_id);

    // Ticket operations
    std::string query_ticket(const std::string& from, const std::string& to,
                            const std::string& date, const std::string& sort_type);
    std::string query_transfer(const std::string& from, const std::string& to,
                              const std::string& date, const std::string& sort_type);
    std::string buy_ticket(const std::string& username, const std::string& train_id,
                          const std::string& date, int num, const std::string& from,
                          const std::string& to, bool queue = false);
    std::string query_order(const std::string& username);
    int refund_ticket(const std::string& username, int n = 1);

    // System operations
    int clean();
    std::string exit();
};

#endif