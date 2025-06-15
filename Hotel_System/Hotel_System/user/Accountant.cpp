#include "Accountant.h"

Accountant::Accountant(const my_string& username, const my_string& password)
	: User(username, password, Role::Accountant) {}

bool Accountant::canCreateReservation() const
{
	return false;
}

bool Accountant::canCancelReservation() const
{
	return false;
}

bool Accountant::canViewReports() const
{
	return true;
}

bool Accountant::canManageUsers() const
{
	return false;
}

bool Accountant::canRegisterUser() const
{
	return false;
}

User* Accountant::clone() const
{
	return new Accountant(*this);
}