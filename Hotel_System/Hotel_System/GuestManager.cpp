#include "GuestManager.h"
#include "GuestValidator.h"

bool GuestManager::addGuest(const my_string& name, const my_string& phone, const my_string& email)
{
	if (!GuestValidator::is_valid_phone(phone))
	{
		throw std::invalid_argument("Invalid phone number! It should be digits only and exactly 10 symbols long.");
	}

	if (!GuestValidator::is_valid_email(email))
	{
		throw std::invalid_argument("Invalid email address! It should be at least 10 characters long and contains @ and ends with .com");
	}

	if (!GuestValidator::is_valid_client_number(nextClientNumber))
	{
		throw std::invalid_argument("Invalid client number! It should be a positive number.");
	}

	if (!GuestValidator::is_unique_client_number(nextClientNumber, guests))
	{
		throw std::invalid_argument("Client number already exists.");
	}

	Guest guest(name, phone, email, nextClientNumber++);
	guests.push_back(guest);
	std::cout << "Guest added successfully.\n";
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

const my_vector<Guest>& GuestManager::getGuests() const
{
	return guests;
}