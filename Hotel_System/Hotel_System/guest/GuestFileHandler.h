#pragma once

#include "Guest.h"

class GuestFileHandler
{
public:
    static void saveGuests(const my_vector<Guest>& guests, const char* filename);
    static void loadGuests(my_vector<Guest>& guests, const char* filename, int& nextClientNumber);
};