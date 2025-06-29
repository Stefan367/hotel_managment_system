#include "Apartment.h"

Apartment::Apartment(int roomNumber, double basePrice)
    : Room(roomNumber, basePrice, RoomType::Apartment) {}

void Apartment::displayInfo() const
{
    std::cout << "Room #" << getRoomNumber()
        << " | Type: " << to_string(getType()).c_str()
        << " | Status: " << getStatus().c_str()
        << "\n";
}

Room* Apartment::clone() const
{
    return new Apartment(*this);
}
