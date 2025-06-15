#include "Receptionist.h"

Receptionist::Receptionist(const my_string& username, const my_string& password)
	: User(username, password, Role::Receptionist) {}

bool Receptionist::canCreateReservation() const
{
	return true;
}

bool Receptionist::canCancelReservation() const
{
	return true;
}

bool Receptionist::canViewReports() const
{
	return false;
}

bool Receptionist::canManageUsers() const
{
	return false;
}

bool Receptionist::canRegisterUser() const
{
	return false;
}


User* Receptionist::clone() const
{
	return new Receptionist(*this);
}