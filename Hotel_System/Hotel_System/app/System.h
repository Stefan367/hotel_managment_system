#pragma once

#include "../reservation/ReservationManager.h"
#include "../reservation/ReservationFileHandler.h"
#include "../user/UserFileHandler.h"
#include "../income/IncomeAnalyzer.h"
#include "../user/ActionReportFileHandler.h"

class System
{
private:
    my_vector<Room*> rooms;
    ReservationManager reservationManager;
    UserManager userManager;
    GuestManager guestManager;
    IncomeAnalyzer incomeAnalyzer;
    my_vector<ActionReport> reports;
    Date currentDate;

public:
    System();

    void loadFromFiles();
    void saveToFiles() const;

    // Authentication
    bool login(const my_string& username, const my_string& password);
    void logout();
    bool isUserLoggedIn() const;
    User* getCurrentUser() const;

    // Action tracking
    void addActionReport(const my_string& action);
    const my_vector<ActionReport>& getReports() const;

    // Room access
    Room* findRoomByNumber(int roomNumber) const;
    const my_vector<Room*>& getAllRooms() const;

    // Reservations
    const my_vector<Reservation>& getReservations() const;
    ReservationManager& getReservationManager();

    // Users & Guests
    UserManager& getUserManager();
    GuestManager& getGuestManager();

    // Income
    IncomeAnalyzer& getIncomeAnalyzer();

    // Time
    const Date& getCurrentDate() const;
    void advanceToNextDay();
};