#pragma once

#include "Guest.h"

class GuestValidator
{
public:
    static bool isPhoneValid(const my_string& phone);
    static bool isEmailValid(const my_string& email);
    static bool isClientNumberValid(int number);
    static bool isClientNumberUnique(int number, const my_vector<Guest>& guests);
};
