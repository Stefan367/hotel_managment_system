#pragma once

#include "Guest.h"

namespace GuestValidator
{
    bool is_valid_phone(const my_string& phone);
    bool is_valid_email(const my_string& email);
    bool is_valid_client_number(int number);
    bool is_unique_client_number(int number, const my_vector<Guest>& guests);
}