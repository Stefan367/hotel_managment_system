#include "IncomeAnalyzer.h"

double IncomeAnalyzer::totalIncome(const my_vector<Reservation>& reservations)
{
    double sum = 0.0;
    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        sum += reservations[i].getTotalPrice();
    }
    return sum;
}

double IncomeAnalyzer::incomeByDay(const my_vector<Reservation>& reservations, const Date& date)
{
    double sum = 0.0;

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        const Reservation& r = reservations[i];
        Date checkIn = r.getCheckInDate();
        Date checkOut = r.getCheckOutDate();

        if (date >= checkIn && date < checkOut)
        {
            int nights = r.getCheckOutDate().daysUntil(r.getCheckInDate()) * -1; // days are taken backwards
            if (nights == 0) continue;

            double pricePerNight = r.getTotalPrice() / nights;
            sum += pricePerNight;
        }
    }

    return sum;
}

double IncomeAnalyzer::incomeByMonth(const my_vector<Reservation>& reservations, int month, int year)
{
    double total = 0.0;

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        const Reservation& r = reservations[i];
        int nights = r.getCheckOutDate().daysUntil(r.getCheckInDate()) * -1;
        if (nights <= 0) continue;

        double pricePerNight = r.getTotalPrice() / nights;

        Date current = r.getCheckInDate();
        while (current < r.getCheckOutDate())
        {
            if (current.getMonth() == month && current.getYear() == year)
            {
                total += pricePerNight;
            }
            current.addDays(1);
        }
    }

    return total;
}

double IncomeAnalyzer::incomeByYear(const my_vector<Reservation>& reservations, int year)
{
    double total = 0.0;

    for (int month = 1; month <= 12; ++month)
    {
        total += incomeByMonth(reservations, month, year);
    }

    return total;
}

double IncomeAnalyzer::incomeByRoomType(const my_vector<Reservation>& reservations, RoomType type)
{
    double total = 0.0;

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        const Reservation& r = reservations[i];
        if (r.getRoom()->getType() == type)
        {
            total += r.getTotalPrice();
        }
    }

    return total;
}

size_t IncomeAnalyzer::reservationCountForRoomType(const my_vector<Reservation>& reservations, RoomType type)
{
    size_t count = 0;

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        if (reservations[i].getRoom()->getType() == type)
        {
            ++count;
        }
    }

    return count;
}

double IncomeAnalyzer::occupancyRate(const my_vector<Reservation>& reservations, size_t totalRooms, const Date& from, const Date& to)
{
    if (totalRooms == 0 || !(from < to))
    {
        return 0.0;
    }

    int totalAvailableRoomDays = totalRooms * from.daysUntil(to);
    int totalOccupiedRoomDays = 0;

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        const Reservation& r = reservations[i];
        Date resFrom = r.getCheckInDate();
        Date resTo = r.getCheckOutDate();

        if (resTo <= from || resFrom >= to) continue;

        Date overlapStart = (resFrom < from) ? from : resFrom;
        Date overlapEnd = (resTo > to) ? to : resTo;

        int overlapDays = overlapStart.daysUntil(overlapEnd);
        if (overlapDays > 0)
        {
            totalOccupiedRoomDays += overlapDays;
        }
    }

    return totalAvailableRoomDays == 0 ? 0.0 : (100.0 * totalOccupiedRoomDays) / totalAvailableRoomDays;
}

Reservation IncomeAnalyzer::mostProfitableReservation(const my_vector<Reservation>& reservations)
{
    if (reservations.get_size() == 0)
    {
        throw std::runtime_error("No reservations available.");
    }

    const Reservation* mostProfitable = &reservations[0];

    for (size_t i = 1; i < reservations.get_size(); ++i)
    {
        if (reservations[i].getTotalPrice() > mostProfitable->getTotalPrice())
        {
            mostProfitable = &reservations[i];
        }
    }

    return *mostProfitable;
}

RoomType IncomeAnalyzer::mostProfitableRoomType(const my_vector<Reservation>& reservations)
{
    double typeProfits[6] = {};
    RoomType types[] = { RoomType::Single, RoomType::Double, RoomType::Luxury, RoomType::Conference, RoomType::Apartment };

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        RoomType type = reservations[i].getRoom()->getType();
        typeProfits[static_cast<int>(type)] += reservations[i].getTotalPrice();
    }

    double maxProfit = -1;
    RoomType most = RoomType::Unknown;

    for (int i = 0; i < 5; ++i)
    {
        if (typeProfits[i] > maxProfit)
        {
            maxProfit = typeProfits[i];
            most = types[i];
        }
    }

    return most;
}

void IncomeAnalyzer::exportReport(const my_vector<Reservation>& reservations, const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        throw std::runtime_error("Could not open file for writing income report.");
    }

    out << "ID;Guest;Room;Check-in;Check-out;Price\n";

    for (size_t i = 0; i < reservations.get_size(); ++i)
    {
        const Reservation& r = reservations[i];
        out << r.getId() << ";"
            << r.getGuest()->getName().c_str() << ";"
            << r.getRoom()->getRoomNumber() << ";"
            << r.getCheckInDate().to_string().c_str() << ";"
            << r.getCheckOutDate().to_string().c_str() << ";"
            << r.getTotalPrice() << "\n";
    }

    out.close();
}