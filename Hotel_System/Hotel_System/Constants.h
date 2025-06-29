#pragma once

const int YEAR_OF_OPENING = 1900;
const int MAX_YEAR_FOR_RESERVATIONS = 2100;
const int CURRENT_YEAR = 2025;

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
}

namespace GuestConstants
{
    const int GOLD_TIER_RESERVATIONS = 3;
    const int PLATINIUM_TIER_RESERVATIONS = 10;
}

namespace PricingConstants
{
    const double SEASON_SUMMER_MULTIPLIER = 1.3;
    const double SEASON_DEFAULT_MULTIPLIER = 1.0;

    const double DEMAND_LOW = 1.0;
    const double DEMAND_MEDIUM = 1.1;
    const double DEMAND_HIGH = 1.3;

    const double WEEKEND_COEF = 1.4;
}

namespace UserConstants
{
    const size_t MIN_USERNAME_LENGTH = 3;
    const size_t MIN_PASSWORD_LENGTH = 5;
}

namespace FilenameConstants
{
    extern const char* const ROOMS_FILE;
    extern const char* const GUESTS_FILE;
    extern const char* const USERS_FILE;
    extern const char* const RESERVATIONS_FILE;
    extern const char* const PRICING_FILE;
    extern const char* const REPORTS_FILE;
}