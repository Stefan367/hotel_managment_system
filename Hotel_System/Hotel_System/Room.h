#pragma once

#include "RoomType.h"
#include "Constants.h"

class Room
{
protected:
    int roomNumber;
    my_string status;
    double basePrice;
    RoomType type;

    Room(int roomNumber, double basePrice, RoomType type);

public:
    virtual ~Room() = default;

    virtual double calculatePrice() const = 0;
    virtual void displayInfo() const = 0;
    virtual Room* clone() const = 0;

    int getRoomNumber() const;
    my_string getStatus() const;
    void setStatus(const my_string& newStatus);
    double getBasePrice() const;
    void setBasePrice(double price);
    RoomType getType() const;
};