#pragma once

//#include "../core/my_string.h"
#include "System.h"

enum class CommandType
{
    LOGIN,
    LOGOUT,
    HELP,
    EXIT,

    // Manager
    REGISTER_USER,
    VIEW_GUEST_RESERVATIONS,
    UPDATE_PRICING,
    ADD_ROOM,

    // Receptionist
    REGISTER_GUEST,
    CREATE_RESERVATION,
    CANCEL_RESERVATION,
    VIEW_ROOMS_AND_RESERVATIONS,

    // Accountant
    VIEW_INCOME,
    EXPORT_INCOME,

    UNKNOWN
};

class CommandExecutor
{
public:
    void executeCommand(System& system, const my_string& inputLine);
    CommandType getCommandType(const my_string& command) const;

private:
    // Main dispatcher
    void executeGuestCommand(System& system, std::stringstream& ss, CommandType type);
    void executeReceptionistCommand(System& system, std::stringstream& ss, CommandType type);
    void executeManagerCommand(System& system, std::stringstream& ss, CommandType type);

    // Shared
    void handleLogin(System& system, std::stringstream& ss);
    void handleLogout(System& system);
    void handleHelp();
    void handleExit(System& system);

    // Manager
    void handleRegisterUser(System& system, std::stringstream& ss);
    void handleViewGuestReservations(System& system, std::stringstream& ss);
    void handleUpdatePricing(System& system, std::stringstream& ss);
    void handleAddRoom(System& system, std::stringstream& ss);

    // Receptionist
    void handleRegisterGuest(System& system, std::stringstream& ss);
    void handleCreateReservation(System& system, std::stringstream& ss);
    void handleCancelReservation(System& system, std::stringstream& ss);

    // Accountant
    void handleViewRoomsAndReservations(System& system);
    void handleViewIncome(System& system, std::stringstream& ss);
    void handleExportIncome(System& system, std::stringstream& ss);
};