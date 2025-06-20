#pragma once

#include "Room.h"
#include "../core/my_vector.hpp"

struct PricingEntry
{
    RoomType type;
    double basePrice;
    double multiplier;
};

class PricingTable
{
private:
    my_vector<PricingEntry> entries;
    bool isWeekend = false;
    double seasonMultiplier = 1.0;
    double demandMultiplier = 1.0;

public:
    bool loadFromFile(const char* filename);
    bool saveToFile(const char* filename) const;

    double calculatePrice(const Room& room) const;
    void updateBasePrice(RoomType type, double newPrice);

    void setWeekend(bool flag);
    void setSeasonMultiplier(double multiplier);
    void setDemandMultiplier(double multiplier);
    void updateDemandMultiplier(size_t totalRooms, size_t occupiedRooms);

    double getBasePrice(RoomType type) const;
};