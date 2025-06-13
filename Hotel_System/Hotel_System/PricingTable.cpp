#include "PricingTable.h"
#include <fstream>
#include <sstream>

bool PricingTable::loadFromFile(const char* filename)
{
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    char line[256];
    while (in.getline(line, sizeof(line)))
    {
        std::istringstream iss(line);

        my_string typeStr;
        double base, mult;

        iss >> typeStr >> base >> mult;
        RoomType type = from_string(typeStr);
        if (type == RoomType::Unknown) continue;

        PricingEntry entry = { type, base, mult };
        entries.push_back(entry);
    }

    in.close();
    return true;
}

void PricingTable::setWeekend(bool flag)
{
    isWeekend = flag;
}

void PricingTable::setSeasonMultiplier(double multiplier)
{
    seasonMultiplier = multiplier;
}

void PricingTable::setDemandMultiplier(double multiplier)
{
    demandMultiplier = multiplier;
}

double PricingTable::calculatePrice(const Room& room) const
{
    RoomType type = room.getType();

    for (size_t i = 0; i < entries.get_size(); ++i)
    {
        if (entries[i].type == type)
        {
            double base = entries[i].basePrice;
            double mult = entries[i].multiplier;

            double final = base * mult;

            if (isWeekend) final *= 1.10;
            final *= seasonMultiplier;
            final *= demandMultiplier;

            return final;
        }
    }

    return 0.0;
}