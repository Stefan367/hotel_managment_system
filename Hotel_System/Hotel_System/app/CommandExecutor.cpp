#include "CommandExecutor.h"
#include "../user/Manager.h"
#include "../user/Receptionist.h"
#include "../user/Accountant.h"
#include "../room/Apartment.h"
#include "../room/LuxuryRoom.h"
#include "../room/SingleRoom.h"
#include "../room/DoubleRoom.h"
#include "../room/ConferenceRoom.h"
#include "../core/my_string_utils.h"
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
	if (command == "add_room") return CommandType::ADD_ROOM;
	if (command == "register_guest") return CommandType::REGISTER_GUEST;
	if (command == "create_reservation") return CommandType::CREATE_RESERVATION;
	if (command == "cancel_reservation") return CommandType::CANCEL_RESERVATION;
	if (command == "view_rooms_reservations") return CommandType::VIEW_ROOMS_AND_RESERVATIONS;
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
	std::cout << "register_user <username> <passsword> <role>\n";
	std::cout << "view_guest_reservations <client_number>\n";
	std::cout << "update_pricing <room_type> <new_price>\n";
	std::cout << "add_room <room_number> <room_type> (room_type: 0 - Single, 1 - Double, 2 - Luxury, 3 - Conference, 4 - Apartment)\n\n";

	std::cout << "\n--- Receptionist Commands ---\n";
	std::cout << "view_rooms_reservations\n";
	std::cout << "register_guest <name> <phone> <email>\n";
	std::cout << "create_reservation <clientNumber> <roomNumber> <checkIn> <checkOut>\n";
	std::cout << "cancel_reservation <reservation_id>\n\n";

	std::cout << "\n--- Accountant Commands ---\n";
	std::cout << "view_rooms_reservations\n";
	std::cout << "view_income < 1 - total income\n2 - income by day - enter: day month year\n3 - income by month - enter: month year\n4 - income by year - enter: year >\n";
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
	if (type == RoomType::Unknown || typeInt < 0 || typeInt > 4)
	{
		throw std::invalid_argument("Invalid room type.");
	}

	system.getReservationManager().getPricingTable().updateBasePrice(type, newPrice);

	my_vector<Room*>& rooms = system.getAllRooms();
	for (size_t i = 0; i < rooms.get_size(); ++i)
	{
		if (rooms[i]->getType() == type)
		{
			rooms[i]->setBasePrice(newPrice);
		}
	}

	system.getReservationManager().getPricingTable().saveToFile(FilenameConstants::PRICING_FILE);

	std::cout << "Updated base price for type " << typeInt << " to " << newPrice << "\n";
	system.addActionReport("Updated pricing for room type.");
}


void CommandExecutor::handleAddRoom(System& system, std::stringstream& ss)
{
	int roomNumber, typeInt;
	ss >> roomNumber >> typeInt;

	if (typeInt < 0 || typeInt > static_cast<int>(RoomType::Apartment))
	{
		std::cout << "Invalid room type.\n";
		return;
	}

	RoomType type = static_cast<RoomType>(typeInt);

	if (system.findRoomByNumber(roomNumber))
	{
		std::cout << "Room number already exists.\n";
		return;
	}

	double basePrice;
	try
	{
		basePrice = system.getReservationManager().getPricingTable().getBasePrice(type);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Failed to get base price: " << ex.what() << "\n";
		return;
	}

	Room* newRoom = nullptr;
	switch (type) {
	case RoomType::Single: newRoom = new SingleRoom(roomNumber, basePrice); break;
	case RoomType::Double: newRoom = new DoubleRoom(roomNumber, basePrice); break;
	case RoomType::Luxury: newRoom = new LuxuryRoom(roomNumber, basePrice); break;
	case RoomType::Conference: newRoom = new ConferenceRoom(roomNumber, basePrice); break;
	case RoomType::Apartment: newRoom = new Apartment(roomNumber, basePrice); break;
	default:
		std::cout << "Unsupported room type.\n";
		return;
	}

	system.getAllRooms().push_back(newRoom);
	system.addActionReport("Added new room: " + int_to_string(roomNumber));

	std::cout << "Room " << roomNumber << " added successfully.\n";
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
	Date today = system.getCurrentDate();

	if (checkIn < today)
	{
		std::cout << "Cannot create reservation with a check-in date in the past.\n";
		return;
	}

	if (checkIn >= checkOut)
	{
		std::cout << "Check-out date must be after check-in date.\n";
		return;
	}

	if (!system.getReservationManager().isRoomAvailable(room, checkIn, checkOut))
	{
		std::cout << "Room is not available for the selected dates.\n";
		return;
	}

	system.getReservationManager().createReservation(guest, room, checkIn, checkOut);
	system.addActionReport("Created reservation.");
	std::cout << "Reservation successfully created.\n";
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
	const Date& today = system.getCurrentDate();
	const my_vector<Reservation>& reservations = system.getReservations();
	ReservationManager& reservationManager = system.getReservationManager();

	std::cout << "Rooms on " << today.to_string().c_str() << ":\n";

	for (size_t i = 0; i < rooms.get_size(); ++i)
	{
		Room* room = rooms[i];
		bool isAvailableToday = reservationManager.isRoomAvailable(room, today, today);

		std::cout << "Room " << room->getRoomNumber()
			<< " - " << (isAvailableToday ? "Available" : "Reserved");

		bool hasReservations = false;
		for (size_t j = 0; j < reservations.get_size(); ++j)
		{
			const Reservation& res = reservations[j];
			if (res.getRoom()->getRoomNumber() == room->getRoomNumber())
			{
				if (!(res.getCheckOutDate() < today))
				{
					if (!hasReservations)
					{
						std::cout << " | Booked: ";
						hasReservations = true;
					}
					std::cout << "[" << res.getCheckInDate().to_string().c_str()
						<< " - " << res.getCheckOutDate().to_string().c_str() << "] ";
				}
			}
		}
		std::cout << "\n";
	}

	std::cout << "\n--- All Reservations ---\n";
	reservationManager.printAllReservations();
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
	case CommandType::ADD_ROOM: handleAddRoom(system, ss); break;
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
	case CommandType::VIEW_ROOMS_AND_RESERVATIONS: handleViewRoomsAndReservations(system); break;
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