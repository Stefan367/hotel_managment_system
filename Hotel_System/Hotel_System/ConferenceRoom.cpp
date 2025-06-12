#include "ConferenceRoom.h"

ConferenceRoom::ConferenceRoom(int roomNumber, double basePrice)
    : Room(roomNumber, basePrice, RoomType::Conference) {}

double ConferenceRoom::calculatePrice() const
{
    return getBasePrice() + RoomConstants::CONFERENCE_FEES;
}

void ConferenceRoom::displayInfo() const
{
    std::cout << "Room #" << getRoomNumber()
        << " | Type: " << to_string(getType()).c_str()
        << " | Status: " << getStatus().c_str()
        << " | Price: $" << calculatePrice()
        << "\n";
}

Room* ConferenceRoom::clone() const
{
    return new ConferenceRoom(*this);
}
