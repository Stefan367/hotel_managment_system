#include "ReservationFileHandler.h"
#include "../core/my_string_utils.h"
#include <fstream>


const size_t INPUT_LINE_PARTS_COUNT = 6;

void ReservationFileHandler::saveToFile(const my_vector<Reservation>& reservations, const char* filename)
{
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open file for writing reservations.");
	}

	for (size_t i = 0; i < reservations.get_size(); ++i)
	{
		const Reservation& r = reservations[i];

		out << int_to_string(r.getId()).c_str() << ";"
			<< int_to_string(r.getGuest()->getClientNumber()).c_str() << ";"
			<< int_to_string(r.getRoom()->getRoomNumber()).c_str() << ";"
			<< r.getCheckInDate().to_string().c_str() << ";"
			<< r.getCheckOutDate().to_string().c_str() << ";"
			<< r.getTotalPrice() << "\n";
	}

	if (!out.good())
	{
		throw std::runtime_error("Failed while writing reservation data to file.");
	}

	out.close();
}

void ReservationFileHandler::loadFromFile(my_vector<Reservation>& reservations, const char* filename, const GuestManager& guestManager, const my_vector<Room*>& rooms)
{
	std::ifstream in(filename);
	if (!in.is_open())
	{
		throw std::runtime_error("Could not open reservation file for reading.");
	}

	char line[256];
	while (in.getline(line, sizeof(line)))
	{
		my_string str(line);

		my_vector<my_string> parts = split_string(str, ';');
		if (parts.get_size() != 6) continue;

		int id = string_to_int(parts[0]);
		int clientNumber = string_to_int(parts[1]);
		int roomNumber = string_to_int(parts[2]);
		Date checkIn(parts[3]);
		Date checkOut(parts[4]);
		double totalPrice = string_to_double(parts[5]);

		const Guest* guest = guestManager.findGuestByNumber(clientNumber);
		if (!guest) continue;

		Room* matchedRoom = nullptr;
		for (size_t i = 0; i < rooms.get_size(); ++i)
		{
			if (rooms[i]->getRoomNumber() == roomNumber)
			{
				matchedRoom = rooms[i];
				break;
			}
		}

		if (!matchedRoom) continue;

		Reservation reservation(id, guest, matchedRoom->clone(), checkIn, checkOut, totalPrice);
		reservations.push_back(reservation);
	}

	in.close();
}