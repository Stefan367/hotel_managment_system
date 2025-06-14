#include "LuxuryRoom.h"

LuxuryRoom::LuxuryRoom(int roomNumber, double basePrice)
    : Room(roomNumber, basePrice, RoomType::Luxury) {}

void LuxuryRoom::displayInfo() const
{
    std::cout << "Room #" << getRoomNumber()
        << " | Type: " << to_string(getType()).c_str()
        << " | Status: " << getStatus().c_str()
        << "\n";
}

Room* LuxuryRoom::clone() const
{
    return new LuxuryRoom(*this);
}