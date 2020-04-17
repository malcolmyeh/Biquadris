#include "controller/controller.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>


// Command-line Interface
bool parseCommandLineArgs(const int argc, char *argv[], bool &graphics, bool &bonus, std::vector<std::string> &scriptFiles, int &startLevel)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string flag = argv[i];
        try
        {
            if (flag == "-text")
                graphics = false;
            else if (flag == "-seed")
            {
                if (i + 1 < argc)
                    srand(std::stoi(argv[i + 1]));
                else
                    throw "Invalid seed. ";
            }
            else if (flag == "-scriptfile1")
            {
                if (i + 1 < argc)
                    scriptFiles[0] = argv[i + 1];
                else
                    throw "Invalid scriptfile1. ";
            }
            else if (flag == "-scriptfile2")
            {
                if (i + 1 < argc)
                    scriptFiles[1] = argv[i + 1];
                else
                    throw "Invalid scriptfile2. ";
            }
            else if (flag == "-startlevel")
            {
                if (i + 1 < argc)
                    startLevel = std::stoi(argv[i + 1]);
                else
                    throw "Invalid startlevel. ";
            }
            else
                throw "Invalid flag. Verify input is correct.";
        }
        catch (std::string error)
        {
            std::cerr << error << std::endl;
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    bool graphics = true, bonus = false;
    std::vector<std::string> scriptFiles{"sequence1.txt", "sequence2.txt"};
    int startLevel = 2;

    bool valid = parseCommandLineArgs(argc, argv, graphics, bonus, scriptFiles, startLevel);

    if (valid)
    {
        if (bonus)
        {
            // ncurses controller
        }
        else
        {
            std::shared_ptr<Controller> c = std::make_shared<Controller>(graphics, scriptFiles, startLevel);
            c->runGame();
        }
    }
    return 0;
}