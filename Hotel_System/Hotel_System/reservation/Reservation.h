#pragma once

#include "../guest/Guest.h"
#include "../room/Room.h"
#include "../core/Date.h"

class Reservation
{
private:
    int id = -1;
    const Guest* guest = nullptr;
    Room* room = nullptr;
    Date checkIn;
    Date checkOut;
    double totalPrice = 0.0;

public:
    Reservation() = default;
    Reservation(int id, const Guest* guest, Room* room, const Date& checkIn, const Date& checkOut, double totalPrice);

    int getId() const;
    const Guest* getGuest() const;
    Room* getRoom() const;
    Date getCheckInDate() const;
    Date getCheckOutDate() const;
    double getTotalPrice() const;

    void display() const;
};