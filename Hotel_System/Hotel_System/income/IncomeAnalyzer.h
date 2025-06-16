#pragma once

#include "../reservation/Reservation.h"
//#include "../room/RoomType.h"
#include <fstream>

class IncomeAnalyzer
{
public:
    double totalIncome(const my_vector<Reservation>& reservations);

    double incomeByDay(const my_vector<Reservation>& reservations, const Date& date);
    double incomeByMonth(const my_vector<Reservation>& reservations, int month, int year);
    double incomeByYear(const my_vector<Reservation>& reservations, int year);

    double incomeByRoomType(const my_vector<Reservation>& reservations, RoomType type);

    size_t reservationCountForRoomType(const my_vector<Reservation>& reservations, RoomType type);

    double occupancyRate(const my_vector<Reservation>& reservations, size_t totalRooms, const Date& from, const Date& to);

    Reservation mostProfitableReservation(const my_vector<Reservation>& reservations);
    RoomType mostProfitableRoomType(const my_vector<Reservation>& reservations);

    void exportReport(const my_vector<Reservation>& reservations, const char* filename);
};