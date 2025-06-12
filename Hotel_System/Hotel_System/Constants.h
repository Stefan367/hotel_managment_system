#pragma once

namespace RoomConstants
{
    const char* const TYPE_SINGLE = "Single";
    const char* const TYPE_DOUBLE = "Double";
    const char* const TYPE_LUXURY = "Luxury";
    const char* const TYPE_CONFERENCE = "Conference";
    const char* const TYPE_APARTMENT = "Apartment";

    const char* const STATUS_FREE = "Free";
    const char* const STATUS_RESERVED = "Reserved";
    const char* const STATUS_MAINTENANCE = "Maintenance";

    const double DOUBLE_ROOM_COEF = 1.20;
    const double LUXURY_ROOM_COEF = 1.60;
    const double APARTMENT_COEF = 1.70;
    const double CONFERENCE_FEES = 50.0;
}