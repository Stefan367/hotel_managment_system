#include "DoubleRoom.h"

DoubleRoom::DoubleRoom(int roomNumber, double basePrice)
    : Room(roomNumber, basePrice, RoomType::Double) {}

double DoubleRoom::calculatePrice() const
{
    return getBasePrice() * RoomConstants::DOUBLE_ROOM_COEF;
}

void DoubleRoom::displayInfo() const
{
    std::cout << "Room #" << getRoomNumber()
        << " | Type: " << to_string(getType()).c_str()
        << " | Status: " << getStatus().c_str()
        << " | Price: $" << calculatePrice()
        << "\n";
}

Room* DoubleRoom::clone() const
{
    return new DoubleRoom(*this);
}