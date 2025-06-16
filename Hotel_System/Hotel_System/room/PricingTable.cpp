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

bool PricingTable::saveToFile(const char* filename) const
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        std::cerr << "Could not open pricing file for writing: " << filename << "\n";
        return false;
    }

    for (size_t i = 0; i < entries.get_size(); ++i)
    {
        out << to_string(entries[i].type).c_str() << " "
            << entries[i].basePrice << " "
            << entries[i].multiplier << "\n";
    }

    out.close();
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

            if (isWeekend) final *= PricingConstants::WEEKEND_COEF;

            // TODO: To change these coeficients when making a price while the program runs
            final *= seasonMultiplier;
            final *= demandMultiplier;

            return final;
        }
    }

    return 0.0;
}

void PricingTable::updateBasePrice(RoomType type, double newPrice)
{
    for (size_t i = 0; i < entries.get_size(); ++i)
    {
        if (entries[i].type == type)
        {
            entries[i].basePrice = newPrice;
            return;
        }
    }

    // Create if does not exist
    PricingEntry entry = { type, newPrice, 1.0 };
    entries.push_back(entry);
}


void PricingTable::updateDemandMultiplier(size_t totalRooms, size_t occupiedRooms)
{
    if (totalRooms == 0)
    {
        demandMultiplier = 1.0;
        return;
    }

    double occupancy = (1.0 * occupiedRooms) / totalRooms;

    if (occupancy >= 0.8)
    {
        demandMultiplier = PricingConstants::DEMAND_HIGH;
    }
    else if (occupancy >= 0.5)
    {
        demandMultiplier = PricingConstants::DEMAND_MEDIUM;
    }
    else
    {
        demandMultiplier = PricingConstants::DEMAND_LOW;
    }
}