#pragma once

#include "Room.h"

class SingleRoom : public Room
{
public:
    SingleRoom(int roomNumber, double basePrice);

    void displayInfo() const override;
    Room* clone() const override;
};