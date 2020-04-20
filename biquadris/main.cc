#include "controller/controller.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>
#include <cctype>

// Command-line Interface
bool parseCommandLineArgs(const int argc, char *argv[], bool &graphics, bool &ncurses, std::vector<std::string> &scriptFiles, int &startLevel)
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

bool fileExists(std::string filename) {
    std::ifstream file(filename);
    return file.good();
}

int main(int argc, char *argv[])
{
    bool graphics = true, ncurses = false;
    std::vector<std::string> scriptFiles{"sequence1.txt", "sequence2.txt"};
    int startLevel = 0;
    // bool valid = parseCommandLineArgs(argc, argv, graphics, ncurses, scriptFiles, startLevel);
    bool valid = true;

    std::vector<std::string> args(argv + 1, argv + argc);
    for (unsigned i = 0; i < args.size(); ++i) {
        std:: string flag = args[i];
        try {
            if (flag == "-text") 
            {
                graphics = false;
            }
            else if (flag == "-seed")
            {
                if (i + 1 < args.size()) {
                    // verify it doesn't contain letters
                    for (unsigned int j = 0; j < args[i + 1].length(); ++j) {
                        if (!isdigit(args[i + 1][j]))
                            throw "Seed should be an unsigned integer.";
                    }
                    srand(std::stoi(args[i + 1]));
                    ++i;
                } else {
                    throw "No seed given";
                }
            }
            else if (flag == "-scriptfile1")
            {
                if (i + 1 < args.size()) {
                    if (!fileExists(args[i + 1]))
                        throw "File does not exist, or cannot be read for player 1.";
                    scriptFiles[0] = args[i + 1];
                    ++i;
                } else {
                    throw "No scriptfile for player 1 given.";
                }
            }
            else if (flag == "-scriptfile2")
            {
                if (i + 1 < args.size()) {
                    if (!fileExists(args[i + 1]))
                        throw "File does not exist, or cannot be read for player 2.";
                    scriptFiles[1] = args[i + 1];
                    ++i;
                } else {
                    throw "No scriptfile for player 2 given.";
                }
            }
            else if (flag == "-startlevel")
            {
                if (i + 1 < args.size()) {
                    // verify that it doesn't contain letters
                    for (unsigned int j = 0; j < args[i + 1].length(); ++j) {
                        if (!isdigit(args[i + 1][j]))
                            throw "Level must be a number between 0 and 4 inclusive.";
                    }
                    if (!(std::stoi(args[i + 1]) >= 0 && std::stoi(args[i + 1]) <= 4))
                        throw "Level must be between 0 and 4.";
                    startLevel = std::stoi(args[i + 1]);
                    ++i;
                } else {
                    throw "No startlevel given.";
                }
            }
        } catch (const char* errorMessage) {
            valid = false;
            std::cerr << errorMessage << std::endl;
        }
    }

    if (valid)
    {
        if (ncurses)
        {
            // ncurses controller
        }
        else
        {
            Controller c(graphics, ncurses, scriptFiles, startLevel);
            c.runGame();
        }
        std::cout << "Thanks for playing :D" << std::endl;
    }
    return 0;
}