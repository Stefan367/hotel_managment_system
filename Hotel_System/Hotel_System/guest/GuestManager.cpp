#include "GuestManager.h"
#include "GuestValidator.h"

bool GuestManager::addGuest(const Guest& guest)
{
    if (!GuestValidator::isPhoneValid(guest.getPhone()))
    {
        throw std::invalid_argument("Invalid phone number! It should contain only digits and be exactly 10 characters long.");
    }

    if (!GuestValidator::isEmailValid(guest.getEmail()))
    {
        throw std::invalid_argument("Invalid email address! It must contain '@' and end with '.com'.");
    }

    if (!GuestValidator::isClientNumberValid(guest.getClientNumber()))
    {
        throw std::invalid_argument("Invalid client number! It should be a non-negative number.");
    }

    if (!GuestValidator::isClientNumberUnique(guest.getClientNumber(), guests))
    {
        throw std::invalid_argument("Client number already exists.");
    }

    guests.push_back(guest);
    std::cout << "Guest added successfully.\n";

    if (guest.getClientNumber() >= nextClientNumber)
    {
        nextClientNumber = guest.getClientNumber() + 1;
    }

    return true;
}

const Guest* GuestManager::findGuestByNumber(int clientNumber) const
{
	for (size_t i = 0; i < guests.get_size(); i++)
	{
		if (guests[i].getClientNumber() == clientNumber)
		{
			return &guests[i];
		}
	}
	return nullptr;
}

Guest* GuestManager::getGuestByNumber(int clientNumber)
{
    for (size_t i = 0; i < guests.get_size(); i++)
    {
        if (guests[i].getClientNumber() == clientNumber)
        {
            return &guests[i];
        }
    }
    return nullptr;
}

void GuestManager::clearGuests()
{
    guests.clear();
    nextClientNumber = 1;
}

void GuestManager::printAllGuests() const
{
	if (guests.get_size() == 0)
	{
		std::cout << "There are not any guests registered.\n";
		return;
	}

	for (size_t i = 0; i < guests.get_size(); i++)
	{
		guests[i].display();
	}
}

size_t GuestManager::getGuestCount() const
{
	return guests.get_size();
}

my_vector<Guest>& GuestManager::getGuests()
{
    return guests;
}

const my_vector<Guest>& GuestManager::getGuests() const
{
	return guests;
}

int& GuestManager::getNextClientNumber()
{
    return nextClientNumber;
}