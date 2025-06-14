#include "FileStorageHandler.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "LuxuryRoom.h"
#include "ConferenceRoom.h"
#include "Apartment.h"

#include <fstream>

void FileStorageHandler::saveRooms(const my_vector<Room*>& rooms, const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Could not open file for writing: " << filename << "\n";
        return;
    }

    for (size_t i = 0; i < rooms.get_size(); ++i) {
        Room* r = rooms[i];
        out << static_cast<int>(r->getType()) << " "
            << r->getRoomNumber() << " "
            << r->getBasePrice() << " "
            << r->getStatus().c_str() << "\n";
    }

    out.close();
}

void FileStorageHandler::loadRooms(my_vector<Room*>& rooms, const char* filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        std::cerr << "Could not open file for reading: " << filename << "\n";
        return;
    }

    int typeInt;
    int number;
    double basePrice;
    char statusBuffer[64];

    while (in >> typeInt >> number >> basePrice >> statusBuffer)
    {
        RoomType type = static_cast<RoomType>(typeInt);
        Room* room = nullptr;

        switch (type)
        {
        case RoomType::Single: room = new SingleRoom(number, basePrice); break;
        case RoomType::Double: room = new DoubleRoom(number, basePrice); break;
        case RoomType::Luxury: room = new LuxuryRoom(number, basePrice); break;
        case RoomType::Conference: room = new ConferenceRoom(number, basePrice); break;
        case RoomType::Apartment: room = new Apartment(number, basePrice); break;
        default: continue;
        }

        room->setStatus(statusBuffer);
        rooms.push_back(room);
    }

    in.close();
}
