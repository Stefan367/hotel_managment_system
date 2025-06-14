#pragma once

#include "Room.h"

class ConferenceRoom : public Room
{
public:
    ConferenceRoom(int roomNumber, double basePrice);

    void displayInfo() const override;
    Room* clone() const override;
};