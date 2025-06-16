#include "CommandExecutor.h"
#include "../user/Manager.h"
#include "../user/Receptionist.h"
#include "../user/Accountant.h"
#include <sstream>

CommandType CommandExecutor::getCommandType(const my_string& command) const
{
	if (command == "login") return CommandType::LOGIN;
	if (command == "logout") return CommandType::LOGOUT;
	if (command == "help") return CommandType::HELP;
	if (command == "exit") return CommandType::EXIT;
	if (command == "register_user") return CommandType::REGISTER_USER;
	if (command == "view_guest_reservations") return CommandType::VIEW_GUEST_RESERVATIONS;
	if (command == "update_pricing") return CommandType::UPDATE_PRICING;
	if (command == "register_guest") return CommandType::REGISTER_GUEST;
	if (command == "create_reservation") return CommandType::CREATE_RESERVATION;
	if (command == "cancel_reservation") return CommandType::CANCEL_RESERVATION;
	if (command == "view_rooms") return CommandType::VIEW_ROOMS_AND_RESERVATIONS;
	if (command == "view_income") return CommandType::VIEW_INCOME;
	if (command == "export_income") return CommandType::EXPORT_INCOME;
	return CommandType::UNKNOWN;
}

void CommandExecutor::executeCommand(System& system, const my_string& inputLine)
{
	std::stringstream ss(inputLine.c_str());
	my_string commandStr;
	ss >> commandStr;

	CommandType type = getCommandType(commandStr);

	switch (type)
	{
	case CommandType::LOGIN: handleLogin(system, ss); break;
	case CommandType::LOGOUT: handleLogout(system); break;
	case CommandType::HELP: handleHelp(); break;
	case CommandType::EXIT: handleExit(system); break;

	default:
		if (!system.isUserLoggedIn())
		{
			std::cout << "You must be logged in to use this command.\n";
			return;
		}

		Role role = system.getCurrentUser()->getRole();

		if (role == Role::Manager)
		{
			executeManagerCommand(system, ss, type);
		}
		else if (role == Role::Receptionist)
		{
			executeReceptionistCommand(system, ss, type);
		}
		else if (role == Role::Accountant)
		{
			executeGuestCommand(system, ss, type);
		}
		else
		{
			std::cout << "Unrecognized role.\n";
		}
	}
}

void CommandExecutor::handleLogin(System& system, std::stringstream& ss)
{
	my_string username, password;
	ss >> username >> password;
	system.login(username, password);
}

void CommandExecutor::handleLogout(System& system)
{
	system.logout();
}

void CommandExecutor::handleExit(System& system)
{
	system.saveToFiles();
	std::cout << "Exiting...\n";
	exit(0);
}

void CommandExecutor::handleHelp()
{
	std::cout << "\n=== Available Commands ===\n";
	std::cout << "login <username> <password>\n";
	std::cout << "logout\n";
	std::cout << "exit\n";

	std::cout << "\n--- Manager Commands ---\n";
	std::cout << "register_user\n";
	std::cout << "view_guest_reservations <client_number>\n";
	std::cout << "update_pricing <room_type> <new_price>\n";

	std::cout << "\n--- Receptionist Commands ---\n";
	std::cout << "register_guest\n";
	std::cout << "create_reservation\n";
	std::cout << "cancel_reservation <reservation_id>\n";

	std::cout << "\n--- Accountant Commands ---\n";
	std::cout << "view_rooms\n";
	std::cout << "view_income < 1 - total income | 2 - income by day - enter: day month year | 3 - income by month - enter: month year | 4 - income by year - enter: year >\n";
	std::cout << "export_income <filename>\n";

	std::cout << "\nType 'help' to show this menu again.\n";
}


// === MANAGER ===

void CommandExecutor::handleRegisterUser(System& system, std::stringstream& ss)
{
	my_string username, password, roleStr;
	ss >> username >> password >> roleStr;
	Role role = string_to_role(roleStr);

	User* user = nullptr;
	if (role == Role::Manager) user = new Manager(username, password);
	else if (role == Role::Receptionist) user = new Receptionist(username, password);
	else if (role == Role::Accountant) user = new Accountant(username, password);
	else
	{
		std::cout << "Invalid role!\n";
		return;
	}

	system.getUserManager().registerUser(user);
	system.addActionReport("Registered new user: " + username);
}

void CommandExecutor::handleViewGuestReservations(System& system, std::stringstream& ss)
{
	int clientNumber;
	ss >> clientNumber;

	const Guest* guest = system.getGuestManager().findGuestByNumber(clientNumber);
	if (!guest)
	{
		std::cout << "Guest not found.\n";
		return;
	}

	std::cout << "Reservations for " << guest->getName().c_str() << ":\n";
	const my_vector<Reservation>& reservations = system.getReservations();

	for (size_t i = 0; i < reservations.get_size(); ++i)
	{
		if (reservations[i].getGuest()->getClientNumber() == clientNumber)
		{
			reservations[i].display();
			std::cout << "---------------\n";
		}
	}
}

void CommandExecutor::handleUpdatePricing(System& system, std::stringstream& ss)
{
	int typeInt;
	double newPrice;
	ss >> typeInt >> newPrice;

	RoomType type = static_cast<RoomType>(typeInt);
	system.getReservationManager().loadPricing(FilenameConstants::PRICING_FILE);
	system.getReservationManager().getPricingTable().updateBasePrice(type, newPrice);
	std::cout << "Updated base price for type " << typeInt << " to " << newPrice << "\n";
	system.addActionReport("Updated pricing.");
}

// === RECEPTIONIST ===

void CommandExecutor::handleRegisterGuest(System& system, std::stringstream& ss)
{
	my_string name, phone, email;
	ss >> name >> phone >> email;

	Guest guest(name, phone, email, system.getGuestManager().getNextClientNumber());
	system.getGuestManager().addGuest(guest);
	system.addActionReport("Registered guest: " + name);
}

void CommandExecutor::handleCreateReservation(System& system, std::stringstream& ss)
{
	int clientNumber, roomNumber;
	my_string checkInStr, checkOutStr;
	ss >> clientNumber >> roomNumber >> checkInStr >> checkOutStr;

	const Guest* guest = system.getGuestManager().findGuestByNumber(clientNumber);
	Room* room = system.findRoomByNumber(roomNumber);

	if (!guest || !room)
	{
		std::cout << "Invalid guest or room.\n";
		return;
	}

	Date checkIn(checkInStr);
	Date checkOut(checkOutStr);

	system.getReservationManager().createReservation(guest, room, checkIn, checkOut);
	system.addActionReport("Created reservation.");
}

void CommandExecutor::handleCancelReservation(System& system, std::stringstream& ss)
{
	int reservationId;
	ss >> reservationId;

	system.getReservationManager().cancelReservation(reservationId);
	system.addActionReport("Cancelled reservation.");
}

// === ACCOUNTANT ===

void CommandExecutor::handleViewRoomsAndReservations(System& system)
{
	const my_vector<Room*>& rooms = system.getAllRooms();

	for (size_t i = 0; i < rooms.get_size(); ++i)
	{
		std::cout << "Room " << rooms[i]->getRoomNumber()
			<< " (" << rooms[i]->getStatus().c_str() << ")\n";
	}

	system.getReservationManager().printAllReservations();
}

void CommandExecutor::handleViewIncome(System& system, std::stringstream& ss)
{
	int type;
	ss >> type;

	const my_vector<Reservation>& res = system.getReservations();
	double income = 0;

	switch (type)
	{
	case 1: income = system.getIncomeAnalyzer().totalIncome(res); break;
	case 2:
	{
		int d, m, y;
		ss >> d >> m >> y;
		income = system.getIncomeAnalyzer().incomeByDay(res, Date(d, m, y));
		break;
	}
	case 3:
	{
		int m, y;
		ss >> m >> y;
		income = system.getIncomeAnalyzer().incomeByMonth(res, m, y);
		break;
	}
	case 4:
	{
		int y;
		ss >> y;
		income = system.getIncomeAnalyzer().incomeByYear(res, y);
		break;
	}
	}

	std::cout << "Income: " << income << " BGN\n";
}

void CommandExecutor::handleExportIncome(System& system, std::stringstream& ss)
{
	my_string filename;
	ss >> filename;

	system.getIncomeAnalyzer().exportReport(system.getReservations(), filename.c_str());
	std::cout << "Exported report to " << filename.c_str() << "\n";
}

// === ROLE DISPATCHERS ===

void CommandExecutor::executeManagerCommand(System& system, std::stringstream& ss, CommandType type)
{
	switch (type)
	{
	case CommandType::REGISTER_USER: handleRegisterUser(system, ss); break;
	case CommandType::VIEW_GUEST_RESERVATIONS: handleViewGuestReservations(system, ss); break;
	case CommandType::UPDATE_PRICING: handleUpdatePricing(system, ss); break;
	case CommandType::REGISTER_GUEST: handleRegisterGuest(system, ss); break;
	case CommandType::CREATE_RESERVATION: handleCreateReservation(system, ss); break;
	case CommandType::CANCEL_RESERVATION: handleCancelReservation(system, ss); break;
	case CommandType::VIEW_ROOMS_AND_RESERVATIONS: handleViewRoomsAndReservations(system); break;
	case CommandType::VIEW_INCOME: handleViewIncome(system, ss); break;
	case CommandType::EXPORT_INCOME: handleExportIncome(system, ss); break;
	default: std::cout << "Unknown command.\n"; break;
	}
}

void CommandExecutor::executeReceptionistCommand(System& system, std::stringstream& ss, CommandType type)
{
	switch (type)
	{
	case CommandType::REGISTER_GUEST: handleRegisterGuest(system, ss); break;
	case CommandType::CREATE_RESERVATION: handleCreateReservation(system, ss); break;
	case CommandType::CANCEL_RESERVATION: handleCancelReservation(system, ss); break;
	default: std::cout << "Unknown command.\n"; break;
	}
}

void CommandExecutor::executeGuestCommand(System& system, std::stringstream& ss, CommandType type)
{
	switch (type)
	{
	case CommandType::VIEW_ROOMS_AND_RESERVATIONS: handleViewRoomsAndReservations(system); break;
	case CommandType::VIEW_INCOME: handleViewIncome(system, ss); break;
	case CommandType::EXPORT_INCOME: handleExportIncome(system, ss); break;
	default: std::cout << "Unknown command.\n"; break;
	}
}