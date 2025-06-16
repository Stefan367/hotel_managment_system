#pragma once

//#include "../core/my_string.h"
#include "GuestStatus.h"
#include "../core/my_vector.hpp"

class Guest
{
private:
    my_string name;
    my_string phone;
    my_string email;
    int clientNumber;
    GuestStatus status;
    my_vector<my_string> reservationHistory;

public:
    Guest();
    Guest(const my_string& name, const my_string& phone, const my_string& email, int clientNumber);

    void addReservation(const my_string& reservationId);
    void updateStatus();

    my_string getName() const;
    int getClientNumber() const;
    GuestStatus getStatus() const;
    size_t getReservationCount() const;

    my_string getPhone() const;
    my_string getEmail() const;
    my_string getReservationId(size_t index) const;

    void display() const;
};