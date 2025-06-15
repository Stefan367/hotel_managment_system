#include "User.h"
#include "../Constants.h"

User::User(const my_string& username, const my_string& password, Role role)
    : username(username), password(password), role(role)
{
    if (username.get_length() < UserConstants::MIN_USERNAME_LENGTH)
    {
        throw std::invalid_argument("Username should be at least 3 characters long.");
    }

    if (password.get_length() < UserConstants::MIN_PASSWORD_LENGTH)
    {
        throw std::invalid_argument("Password should be at least 5 characters long.");
    }
}

my_string User::getUsername() const
{
    return username;
}

my_string User::getPassword() const
{
    return password;
}

bool User::checkPassword(const my_string& input) const
{
    return password == input;
}

Role User::getRole() const
{
    return role;
}