#pragma once

#include "Reservation.h"
#include "../guest/GuestManager.h"
#include "ReservationManager.h"
//#include "../core/my_vector.hpp"
//#include "../room/Room.h"

class ReservationFileHandler
{
public:
	static void saveToFile(const my_vector<Reservation>& reservations, const char* filename);
	static void loadFromFile(ReservationManager& manager, const char* filename, const GuestManager& guestManager, const my_vector<Room*>& rooms);
};