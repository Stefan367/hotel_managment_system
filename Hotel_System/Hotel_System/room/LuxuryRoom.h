#pragma once

#include "Room.h"

class LuxuryRoom : public Room 
{
public:
    LuxuryRoom(int roomNumber, double basePrice);

    void displayInfo() const override;
    Room* clone() const override;
};