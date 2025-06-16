#include "Application.h"

void Application::run()
{
    my_string inputLine;

    std::cout << "<---|--->   Welcome to Hotel Poseidon   <---|--->\n";
    std::cout << "Available command: login\n";

    try
    {
        system.loadFromFiles();
        //system.advanceToNextDay();
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }

    while (true)
    {
        std::cout << "> ";
        getline(std::cin, inputLine);

        if (inputLine.get_length() == 0)
            continue;

        try
        {
            executor.executeCommand(system, inputLine);
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << "\n";
        }
    }
}