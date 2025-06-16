#pragma once

#include "Reservation.h"
//#include "../core/my_vector.hpp"
#include "../room/PricingTable.h"

class ReservationManager
{
private:
    my_vector<Reservation> reservations;
    size_t nextId = 1;
    PricingTable pricingTable;

public:
    ReservationManager(PricingTable& table);

    bool loadPricing(const char* filename);
    void updateDemandMultiplier(size_t totalRooms, size_t occupiedRooms);

    size_t getNextReservationId();
    void updateNextReservationId(const my_vector<Reservation>& reservations);

    bool isRoomAvailable(Room* room, const Date& from, const Date& to) const;

    bool createReservation(
        const Guest* guest,
        Room* room,
        const Date& checkIn,
        const Date& checkOut);


    void cancelReservation(int id);
    void printAllReservations() const;
    const my_vector<Reservation>& getReservations() const;
    my_vector<Reservation>& getReservations();

    void updateBasePrice(RoomType type, double newPrice);

    PricingTable& getPricingTable();
};