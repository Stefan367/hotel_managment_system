#include "GuestFileHandler.h"
#include "GuestStatus.h"
#include "my_string_utils.h"
#include <fstream>

const int inputPartsCount = 6;

void GuestFileHandler::saveGuests(const my_vector<Guest>& guests, const char* filename)
{
	std::ofstream out(filename);

	if (!out)
	{
		std::cerr << "File for writing guests cannot be opened.\n";
		return;
	}

	for (size_t i = 0; i < guests.get_size(); i++)
	{
		const Guest& guest = guests[i];
		out << guest.getName().c_str() << "|"
			<< guest.getPhone().c_str() << "|"
			<< guest.getEmail().c_str() << "|"
			<< int_to_string(guest.getClientNumber()).c_str() << "|"
			<< to_string(guest.getStatus()).c_str() << "|"
			<< int_to_string(guest.getReservationCount()).c_str() << "|";

		for (size_t j = 0; j < guest.getReservationCount(); j++)
		{
			out << guest.getReservationId(j).c_str();
			if (j != guest.getReservationCount() - 1)
			{
				out << ",";
			}
		}

		out << "\n";
	}
}

void GuestFileHandler::loadGuests(my_vector<Guest>& guests, const char* filename, int& nextClientNumber)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        std::cerr << "Could not open file for reading guests!\n";
        return;
    }

    guests.clear();
    nextClientNumber = 1;

    char buffer[1024];
    while (in.getline(buffer, 1024))
    {
        my_string line(buffer);
        my_vector<my_string> parts;

        my_string current;
        for (size_t i = 0; i < line.get_length(); ++i)
        {
            if (line[i] == '|')
            {
                parts.push_back(current);
                current = my_string();
            }
            else
            {
                current += line[i];
            }
        }
        parts.push_back(current);

        if (parts.get_size() < inputPartsCount) continue;

        my_string name = parts[0];
        my_string phone = parts[1];
        my_string email = parts[2];
        int clientNumber = string_to_int(parts[3]);
        GuestStatus status = string_to_status(parts[4]);
        int resCount = string_to_int(parts[5]);

        my_vector<my_string> reservations;
        if (parts.get_size() > inputPartsCount)
        {
            my_string resList = parts[inputPartsCount];
            my_string id;
            for (size_t i = 0; i < resList.get_length(); ++i)
            {
                if (resList[i] == ',')
                {
                    reservations.push_back(id);
                    id = my_string();
                }
                else
                {
                    id += resList[i];
                }
            }
            if (id.get_length() > 0)
            {
                reservations.push_back(id);
            }
        }

        Guest guest(name, phone, email, clientNumber);
        for (size_t i = 0; i < reservations.get_size(); ++i)
        {
            guest.addReservation(reservations[i]);
        }

        guests.push_back(guest);

        if (clientNumber >= nextClientNumber)
        {
            nextClientNumber = clientNumber + 1;
        }
    }

    in.close();
}