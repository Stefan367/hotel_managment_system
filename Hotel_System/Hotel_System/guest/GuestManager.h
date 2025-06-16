#pragma once

#include "Guest.h"

class GuestManager
{
private:
    my_vector<Guest> guests;
    int nextClientNumber = 1;

public:
    bool addGuest(const Guest& guest);

    const Guest* findGuestByNumber(int clientNumber) const;
    Guest* getGuestByNumber(int clientNumber);
    void printAllGuests() const;
    void clearGuests();

    size_t getGuestCount() const;
    const my_vector<Guest>& getGuests() const;
    my_vector<Guest>& getGuests();
    int& getNextClientNumber();
};