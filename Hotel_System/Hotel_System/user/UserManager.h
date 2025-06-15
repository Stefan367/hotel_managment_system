#pragma once

#include "User.h"
#include "../core/my_vector.hpp"

class UserManager
{
private:
    my_vector<User*> users;
    User* loggedInUser = nullptr;

public:
    ~UserManager();

    bool registerUser(User* user);
    bool login(const my_string& username, const my_string& password);
    void logout();

    bool usernameExists(const my_string& username) const;

    User* getLoggedInUser() const;

    my_vector<User*>& getAllUsers();

    void clear();
};