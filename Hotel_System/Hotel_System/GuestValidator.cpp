#include "GuestValidator.h"

const int minEmailLength = 10;

bool GuestValidator::isPhoneValid(const my_string& phone)
{
    if (phone.get_length() != 10)
    {
        return false;
    }

    for (size_t i = 0; i < phone.get_length(); ++i)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return false;
        }
    }
    return true;
}

bool GuestValidator::isEmailValid(const my_string& email)
{
    bool hasAt = false;
    bool endsWithDotCom = false;

    size_t len = email.get_length();

    for (size_t i = 0; i < len; ++i)
    {
        if (email[i] == '@')
        {
            hasAt = true;
            break;
        }
    }

    if (len >= minEmailLength &&
        email[len - 4] == '.' &&
        email[len - 3] == 'c' &&
        email[len - 2] == 'o' &&
        email[len - 1] == 'm') {
        endsWithDotCom = true;
    }

    return hasAt && endsWithDotCom;
}

bool GuestValidator::isClientNumberValid(int number)
{
    return number >= 0;
}

bool GuestValidator::isClientNumberUnique(int number, const my_vector<Guest>& guests)
{
    for (size_t i = 0; i < guests.get_size(); ++i)
    {
        if (guests[i].getClientNumber() == number)
        {
            return false;
        }
    }
    return true;
}