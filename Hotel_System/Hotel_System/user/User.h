#pragma once
#include "Role.h"

class User
{
protected:
    my_string username;
    my_string password;
    Role role;

public:
    User(const my_string& username, const my_string& password, Role role);
    virtual ~User() = default;

    my_string getUsername() const;
    my_string getPassword() const;
    bool checkPassword(const my_string& input) const;
    Role getRole() const;

    virtual bool canCreateReservation() const { return false; }
    virtual bool canCancelReservation() const { return false; }
    virtual bool canViewReports() const { return false; }
    virtual bool canManageUsers() const { return false; }
    virtual bool canRegisterUser() const { return false; }

    virtual User* clone() const = 0;
};