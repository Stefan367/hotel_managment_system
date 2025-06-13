#include "DoubleRoom.h"

DoubleRoom::DoubleRoom(int roomNumber, double basePrice)
    : Room(roomNumber, basePrice, RoomType::Double) {}

void DoubleRoom::displayInfo() const
{
    std::cout << "Room #" << getRoomNumber()
        << " | Type: " << to_string(getType()).c_str()
        << " | Status: " << getStatus().c_str()
        << "\n";
}

Room* DoubleRoom::clone() const
{
    return new DoubleRoom(*this);
}