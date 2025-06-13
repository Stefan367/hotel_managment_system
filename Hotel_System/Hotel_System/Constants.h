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

    const double WEEKEND_COEF = 1.5;
}

namespace GuestConstants
{
    const int GOLD_TIER_RESERVATIONS = 3;
    const int PLATINIUM_TIER_RESERVATIONS = 10;
}