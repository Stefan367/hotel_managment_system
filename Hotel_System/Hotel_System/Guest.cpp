#include "Guest.h"

Guest::Guest(const my_string& name, const my_string& phone, const my_string& email, int clientNumber)
    : name(name), phone(phone), email(email), clientNumber(clientNumber), status(GuestStatus::Regular) {}

void Guest::addReservation(const my_string& reservationId)
{
    reservationHistory.push_back(reservationId);
    updateStatus();
}

void Guest::updateStatus()
{
    status = classifyFromHistory(reservationHistory.get_size());
}

my_string Guest::getName() const
{
    return name;
}

int Guest::getClientNumber() const
{
    return clientNumber;
}

GuestStatus Guest::getStatus() const
{
    return status;
}

size_t Guest::getReservationCount() const
{
    return reservationHistory.get_size();
}

void Guest::display() const
{
    std::cout << "Guest: " << name.c_str()
        << " | Phone: " << phone.c_str()
        << " | Email: " << email.c_str()
        << " | Client #: " << clientNumber
        << " | Status: " << to_string(status)
        << " | Reservations: " << reservationHistory.get_size()
        << "\n";
}