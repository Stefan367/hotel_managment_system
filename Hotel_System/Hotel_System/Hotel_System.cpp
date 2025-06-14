// Hotel_System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// core
#include "core/my_string.h"
#include "core/my_vector.hpp"

// guest
#include "guest/Guest.h"
#include "guest/GuestManager.h"
#include "guest/GuestValidator.h"
#include "guest/GuestFileHandler.h"

void testGuestSystem() {
    GuestManager manager;

    try {
        // Добавяне на валидни гости
        Guest g1("Ivan Ivanov", "0888123456", "ivan@gmail.com", 1);
        Guest g2("Maria Petrova", "0899123456", "maria@abv.com", 2);
        Guest g3("Georgi Georgiev", "0878123456", "georgi@yahoo.com", 3);

        manager.addGuest(g1);
        manager.addGuest(g2);
        manager.addGuest(g3);

        std::cout << "Guests added to manager.\n";

        // Опит за невалиден гост
        try {
            Guest invalid("Fake Name", "123", "invalid", 4);
            manager.addGuest(invalid);
        }
        catch (const std::exception& e) {
            std::cout << "[Expected invalid guest] " << e.what() << "\n";
        }

        // Запазване във файл
        GuestFileHandler::saveGuests(manager.getGuests(), "guests.txt");
        std::cout << "Guests saved to guests.txt\n";

        // Зареждане от файл
        my_vector<Guest> loaded;
        int nextClientNumber = 100; // някаква начална стойност
        GuestFileHandler::loadGuests(loaded, "guests.txt", nextClientNumber);

        std::cout << "Guests loaded from file:\n";
        for (size_t i = 0; i < loaded.get_size(); ++i) {
            loaded[i].display();
        }

        std::cout << "Next available client number: " << nextClientNumber << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
}

int main() {
    testGuestSystem();
    return 0;
}
