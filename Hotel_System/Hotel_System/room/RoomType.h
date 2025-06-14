#ifndef ROOM_TYPE_H
#define ROOM_TYPE_H

#include "../core/my_string.h"

enum class RoomType
{
    Single,
    Double,
    Luxury,
    Conference,
    Apartment,
    Unknown
};

my_string to_string(RoomType type);

RoomType from_string(const my_string& str);

#endif