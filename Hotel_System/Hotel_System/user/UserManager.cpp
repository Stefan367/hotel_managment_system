#include "UserManager.h"
#include <iostream>

UserManager::~UserManager()
{
    for (size_t i = 0; i < users.get_size(); ++i)
    {
        delete users[i];
    }
    users.clear();
}

bool UserManager::registerUser(User* user)
{
    if (usernameExists(user->getUsername()))
    {
        std::cout << "Username already taken.\n";
        delete user;
        return false;
    }

    users.push_back(user);
    std::cout << "User registered successfully.\n";
    return true;
}

bool UserManager::login(const my_string& username, const my_string& password)
{
    for (size_t i = 0; i < users.get_size(); ++i)
    {
        if (users[i]->getUsername() == username && users[i]->checkPassword(password))
        {
            loggedInUser = users[i];
            std::cout << "Login successful. Welcome, " << username << "!\n";
            return true;
        }
    }

    std::cout << "Login failed. Invalid username or password.\n";
    return false;
}

void UserManager::logout()
{
    if (loggedInUser)
    {
        std::cout << "User " << loggedInUser->getUsername() << " logged out.\n";
        loggedInUser = nullptr;
    }
}

bool UserManager::usernameExists(const my_string& username) const
{
    for (size_t i = 0; i < users.get_size(); ++i)
    {
        if (users[i]->getUsername() == username) return true;
    }
    return false;
}

User* UserManager::getLoggedInUser() const
{
    return loggedInUser;
}

my_vector<User*>& UserManager::getAllUsers()
{
    return users;
}

const my_vector<User*>& UserManager::getAllUsers() const
{
    return users;
}

void UserManager::clear()
{
    for (size_t i = 0; i < users.get_size(); ++i)
    {
        delete users[i];
    }
    users.clear();
    loggedInUser = nullptr;
}