#include "GuestStatus.h"
#include "Constants.h"

const char* to_string(GuestStatus status)
{
    switch (status)
    {
    case GuestStatus::Regular: return "Regular";
    case GuestStatus::Gold: return "Gold";
    case GuestStatus::Platinum: return "Platinum";
    default: return "Unknown";
    }
}

GuestStatus classifyFromHistory(int reservationsCount)
{
    if (reservationsCount >= GuestConstants::PLATINIUM_TIER_RESERVATIONS) return GuestStatus::Platinum;
    if (reservationsCount >= GuestConstants::GOLD_TIER_RESERVATIONS) return GuestStatus::Gold;
    return GuestStatus::Regular;
}