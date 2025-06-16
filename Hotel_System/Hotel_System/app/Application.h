#pragma once
#include "System.h"
#include "CommandExecutor.h"

class Application
{
private:
    System system;
    CommandExecutor executor;

public:
    void run();
};