#pragma once

#include "Room.h"

class DoubleRoom : public Room
{
public:
    DoubleRoom(int roomNumber, double basePrice);

    void displayInfo() const override;
    Room* clone() const override;
};