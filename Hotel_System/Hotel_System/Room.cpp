#include "Room.h"
#include <iostream>
#include <stdexcept>

Room::Room(int roomNumber, double basePrice) 
    : roomNumber(roomNumber), basePrice(basePrice), status(RoomConstants::STATUS_FREE)
{
    if (roomNumber <= 0)
    {
        throw std::invalid_argument("Invalid argument! Room number must be positive.");
    }

    if (basePrice < 0)
    {
        throw std::invalid_argument("Invalid argument! Base price cannot be negative.");
    }
}

int Room::getRoomNumber() const
{
    return roomNumber;
}

my_string Room::getStatus() const
{
    return status;
}

void Room::setStatus(const my_string& newStatus)
{
    if (!(newStatus == RoomConstants::STATUS_FREE 
        || newStatus == RoomConstants::STATUS_RESERVED
        || newStatus == RoomConstants::STATUS_MAINTENANCE))
    {
        throw std::invalid_argument("Invalid argument! Room status must be 'Free', 'Reserved', or 'Maintenance'.");
    }
    status = newStatus;
}

double Room::getBasePrice() const
{
    return basePrice;
}

void Room::setBasePrice(double price)
{
    if (price < 0)
    {
        throw std::invalid_argument("Invalid argument! Base price cannot be negative.");
    }
    basePrice = price;
}