#include "../reservation/ReservationManager.h"
#include <stdexcept>
#include <iostream>

ReservationManager::ReservationManager(PricingTable& table)
    : pricingTable(table), nextId(1) {}


bool ReservationManager::loadPricing(const char* filename)
{
    return pricingTable.loadFromFile(filename);
}

void ReservationManager::updateDemandMultiplier(size_t totalRooms, size_t occupiedRooms)
{
    pricingTable.updateDemandMultiplier(totalRooms, occupiedRooms);
}

bool ReservationManager::isRoomAvailable(Room* room, const Date& from, const Date& to) const
{
    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        const Reservation& res = reservations[i];
        if (res.getRoom()->getRoomNumber() == room->getRoomNumber())
        {
            if (!(to <= res.getCheckInDate() || from >= res.getCheckOutDate()))
            {
                return false;
            }
        }
    }
    return true;
}

bool ReservationManager::createReservation(const Guest* guest, Room* room, const Date& checkIn, const Date& checkOut)
{
    if (!guest || !room)
    {
        std::cout << "Invalid guest or room.\n";
        return false;
    }

    if (!(checkIn < checkOut))
    {
        std::cout << "Check-in date must be before check-out.\n";
        return false;
    }

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        const Reservation& r = reservations[i];
        if (r.getRoom()->getRoomNumber() == room->getRoomNumber())
        {
            if (!(checkOut <= r.getCheckInDate() || checkIn >= r.getCheckOutDate()))
            {
                std::cout << "Room is already booked for this period.\n";
                return false;
            }
        }
    }

    double totalPrice = 0;
    Date current = checkIn;
    while (current < checkOut)
    {
        pricingTable.setWeekend(current.isWeekend());
        totalPrice += pricingTable.calculatePrice(*room);
        current.addDays(1);
    }

    Reservation res(nextId++, guest, room->clone(), checkIn, checkOut, totalPrice);
    reservations.push_back(res);

    room->setStatus(RoomConstants::STATUS_RESERVED);

    std::cout << "Reservation created successfully. Total price: " << totalPrice << " BGN.\n";
    return true;
}

void ReservationManager::cancelReservation(int id)
{
    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        if (reservations[i].getId() == id)
        {
            reservations.remove_at(i);
            std::cout << "Reservation canceled.\n";
            return;
        }
    }
    std::cout << "Reservation not found.\n";
}

void ReservationManager::printAllReservations() const
{
    if (reservations.get_size() == 0)
    {
        std::cout << "No reservations found.\n";
        return;
    }

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        reservations[i].display();
        std::cout << "---------------------------\n";
    }
}

const my_vector<Reservation>& ReservationManager::getReservations() const
{
    return reservations;
}

my_vector<Reservation>& ReservationManager::getReservations()
{
    return reservations;
}