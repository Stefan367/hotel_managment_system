#include "GuestStatus.h"
#include "../Constants.h"

my_string to_string(GuestStatus status)
{
    switch (status)
    {
    case GuestStatus::Regular: return "Regular";
    case GuestStatus::Gold: return "Gold";
    case GuestStatus::Platinum: return "Platinum";
    default: return "Unknown";
    }
}

GuestStatus string_to_status(const my_string& str)
{
    if (str == "0" || str == "Regular") return GuestStatus::Regular;
    if (str == "1" || str == "Gold") return GuestStatus::Gold;
    if (str == "2" || str == "Platinum") return GuestStatus::Platinum;

    throw std::runtime_error("Invalid GuestStatus value.");
}

GuestStatus classifyFromHistory(int reservationsCount)
{
    if (reservationsCount >= GuestConstants::PLATINIUM_TIER_RESERVATIONS) return GuestStatus::Platinum;
    if (reservationsCount >= GuestConstants::GOLD_TIER_RESERVATIONS) return GuestStatus::Gold;
    return GuestStatus::Regular;
}