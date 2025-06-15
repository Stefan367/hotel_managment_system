#include "Manager.h"

Manager::Manager(const my_string& username, const my_string& password)
    : User(username, password, Role::Manager) {}

bool Manager::canCreateReservation() const
{ 
    return true;
}

bool Manager::canCancelReservation() const
{
    return true;
}

bool Manager::canViewReports() const
{
    return true;
}

bool Manager::canManageUsers() const 
{
    return true;
}

bool Manager::canRegisterUser() const
{ 
    return true;
}


User* Manager::clone() const
{
    return new Manager(*this);
}