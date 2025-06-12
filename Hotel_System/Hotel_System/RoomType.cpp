#include "RoomType.h"

my_string to_string(RoomType type)
{
    switch (type) {
    case RoomType::Single: return "Single";
    case RoomType::Double: return "Double";
    case RoomType::Luxury: return "Luxury";
    case RoomType::Conference: return "Conference";
    case RoomType::Apartment: return "Apartment";
    default: return "Unknown";
    }
}

RoomType from_string(const my_string& str)
{
    if (str == "Single") return RoomType::Single;
    if (str == "Double") return RoomType::Double;
    if (str == "Luxury") return RoomType::Luxury;
    if (str == "Conference") return RoomType::Conference;
    if (str == "Apartment") return RoomType::Apartment;
    return RoomType::Unknown;
}