#include "../reservation/Reservation.h"

Reservation::Reservation(int id, const Guest* guest, Room* room, const Date& checkIn, const Date& checkOut, double totalPrice)
    : id(id), guest(guest), room(room), checkIn(checkIn), checkOut(checkOut), totalPrice(totalPrice)
{
    if (!guest || !room)
        throw std::invalid_argument("Reservation must have a valid guest and room.");

    if (!(checkOut >= checkIn))
        throw std::invalid_argument("Check-out date must be after or equal to check-in date.");
}

int Reservation::getId() const
{
    return id;
}

const Guest* Reservation::getGuest() const
{
    return guest;
}

Room* Reservation::getRoom() const
{
    return room;
}

Date Reservation::getCheckInDate() const
{
    return checkIn;
}

Date Reservation::getCheckOutDate() const
{
    return checkOut;
}

double Reservation::getTotalPrice() const
{
    return totalPrice;
}

void Reservation::display() const
{
    std::cout << "Reservation ID: " << id << "\n";
    std::cout << "Guest:\n";
    guest->display();
    std::cout << "Room: " << room->getRoomNumber() << " (" << to_string(room->getType()) << ")\n";
    std::cout << "Check-in: " << checkIn.to_string() << "\n";
    std::cout << "Check-out: " << checkOut.to_string() << "\n";
    std::cout << "Total price: " << totalPrice << " BGN\n";
}