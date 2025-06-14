#pragma once

#include "Room.h"
#include "../core/my_vector.hpp"

class FileStorageHandler 
{
public:
    static void saveRooms(const my_vector<Room*>& rooms, const char* filename);
    static void loadRooms(my_vector<Room*>& rooms, const char* filename);
};
