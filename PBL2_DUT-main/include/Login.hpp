#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <string>

class Login {
private:
    std::string Username;
    std::string Password;
public:
    void input();
    std::string getUsername() const;
    std::string getPassword() const;
    bool check();
    bool performLogin();
};

#endif
