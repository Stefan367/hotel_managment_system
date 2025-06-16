#include "System.h"
#include "../room/FileStorageHandler.h"
#include "../guest/GuestFileHandler.h"

System::System() : reservationManager(*new PricingTable())
{
    /*loadFromFiles();*/

    currentDate = ActionReportFileHandler::getNextDateFromLastReport(reports);
}

void System::loadFromFiles()
{
    FileStorageHandler::loadRooms(rooms, FilenameConstants::ROOMS_FILE);
    UserFileHandler::loadFromFile(userManager.getAllUsers(), FilenameConstants::USERS_FILE);
    GuestFileHandler::loadGuests(guestManager.getGuests(), FilenameConstants::GUESTS_FILE, guestManager.getNextClientNumber());

    reservationManager.loadPricing(FilenameConstants::PRICING_FILE);
    ReservationFileHandler::loadFromFile(reservationManager.getReservations(), FilenameConstants::RESERVATIONS_FILE, guestManager, rooms);
    ActionReportFileHandler::loadFromFile(reports, FilenameConstants::REPORTS_FILE);
}

void System::saveToFiles() const
{
    FileStorageHandler::saveRooms(rooms, FilenameConstants::ROOMS_FILE);
    UserFileHandler::saveToFile(userManager.getAllUsers(), FilenameConstants::USERS_FILE);
    GuestFileHandler::saveGuests(guestManager.getGuests(), FilenameConstants::GUESTS_FILE);
    ReservationFileHandler::saveToFile(reservationManager.getReservations(), FilenameConstants::RESERVATIONS_FILE);
    ActionReportFileHandler::saveToFile(reports, FilenameConstants::REPORTS_FILE);
}



bool System::login(const my_string& username, const my_string& password)
{
    return userManager.login(username, password);
}

void System::logout()
{
    userManager.logout();
}

bool System::isUserLoggedIn() const
{
    return userManager.getLoggedInUser() != nullptr;
}

User* System::getCurrentUser() const
{
    return userManager.getLoggedInUser();
}



void System::addActionReport(const my_string& action)
{
    if (!isUserLoggedIn()) return;

    my_string username = getCurrentUser()->getUsername();
    reports.push_back(ActionReport(currentDate, action, username));
}

const my_vector<ActionReport>& System::getReports() const
{
    return reports;
}



Room* System::findRoomByNumber(int roomNumber) const
{
    for (size_t i = 0; i < rooms.get_size(); ++i)
    {
        if (rooms[i]->getRoomNumber() == roomNumber)
            return rooms[i];
    }
    return nullptr;
}

const my_vector<Room*>& System::getAllRooms() const
{
    return rooms;
}

my_vector<Room*>& System::getAllRooms()
{
    return rooms;
}

const my_vector<Reservation>& System::getReservations() const
{
    return reservationManager.getReservations();
}



ReservationManager& System::getReservationManager()
{
    return reservationManager;
}

UserManager& System::getUserManager()
{
    return userManager;
}

GuestManager& System::getGuestManager()
{
    return guestManager;
}

IncomeAnalyzer& System::getIncomeAnalyzer()
{
    return incomeAnalyzer;
}



const Date& System::getCurrentDate() const
{
    return currentDate;
}

void System::advanceToNextDay()
{
    currentDate.addDays(1);
}