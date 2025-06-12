#pragma once

#include "Room.h"

class ConferenceRoom : public Room
{
public:
    ConferenceRoom(int roomNumber, double basePrice);

    double calculatePrice() const override;
    void displayInfo() const override;
    Room* clone() const override;
};