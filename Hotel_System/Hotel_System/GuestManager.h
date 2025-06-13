#pragma once

#include "Guest.h"

class GuestManager
{
private:
    my_vector<Guest> guests;
    int nextClientNumber = 1;

public:
    bool addGuest(const my_string& name, const my_string& phone, const my_string& email);

    const Guest* findGuestByNumber(int clientNumber) const;
    void printAllGuests() const;

    size_t getGuestCount() const;
    const my_vector<Guest>& getGuests() const;
};