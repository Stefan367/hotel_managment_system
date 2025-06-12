#pragma once

#include "Room.h"

class Apartment : public Room
{
public:
    Apartment(int roomNumber, double basePrice);

    double calculatePrice() const override;
    void displayInfo() const override;
    Room* clone() const override;
};