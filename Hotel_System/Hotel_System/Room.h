#pragma once

#include "RoomType.h"
#include "Constants.h"

class Room
{
protected:
	unsigned int roomNumber;
	my_string status;
	double basePrice;

public:
    Room(int roomNumber, double basePrice);
    virtual ~Room() = default;

    virtual my_string getType() const = 0;
    virtual double calculatePrice() const = 0;
    virtual void displayInfo() const = 0;

    int getRoomNumber() const;
    my_string getStatus() const;
    void setStatus(const my_string& newStatus);
    double getBasePrice() const;
    void setBasePrice(double price);
};