#pragma once
#include "User.h"

class Accountant : public User
{
public:
    Accountant(const my_string& username, const my_string& password);

    bool canCreateReservation() const override;
    bool canCancelReservation() const override;
    bool canViewReports() const override;
    bool canManageUsers() const override;
    bool canRegisterUser() const override;


    User* clone() const override;
};