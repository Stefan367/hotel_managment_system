#pragma once

#include "Room.h"

class Apartment : public Room
{
public:
    Apartment(int roomNumber, double basePrice);

    void displayInfo() const override;
    Room* clone() const override;
};