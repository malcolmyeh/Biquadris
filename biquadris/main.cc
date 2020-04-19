#include "controller/controller.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>
#include <cctype>

// Command-line Interface
bool parseCommandLineArgs(const int argc, char *argv[], bool &graphics, bool &ncurses, std::string &first, std::string &second, int &startLevel)
{
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        args.emplace_back(std::string(argv[i]));
    }
    for (int i = 1; i < argc; ++i)
    {
        std::string flag = args[i];
        try
        {
            if (flag == "-text")
                graphics = false;
            else if (flag == "-seed")
            {
                if (i + 1 < argc)
                    srand(std::stoi(args[i + 1]));
                else
                    throw "Invalid seed. ";
            }
            else if (flag == "-scriptfile1")
            {   
                if (i + 1 < argc) {
                    std::cout << "argv[i + 1] is: " << args[i + 1] << std::endl;
                    first = args[i + 1];
                    // std::cout << scriptFiles[0] << std::endl;
                }
                else
                    throw "Invalid scriptfile1. ";
            }
            else if (flag == "-scriptfile2")
            {
                if (i + 1 < argc)
                    second = args[i + 1];
                else
                    throw "Invalid scriptfile2. ";
            }
            else if (flag == "-startlevel")
            {
                if (i + 1 < argc)
                    startLevel = std::stoi(args[i + 1]);
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
    bool graphics = true, ncurses = false;
    std::vector<std::string> scriptFiles{"sequence1.txt", "sequence2.txt"};
    std::string first = "sequence1.txt";
    std::string second = "sequence2.txt";
    int startLevel = 0;
    for (auto file : scriptFiles)
        std::cout << file << std::endl;
    // bool valid = parseCommandLineArgs(argc, argv, graphics, ncurses, first, second, startLevel);

    // for (int i = 1; i < argc; ++i)
    // {
    //     std::istringstream ss{argv[i]};
    //     // std::string flag = argv[i];
    //     std::string flag;
    //     ss >> flag;
    //     try
    //     {
    //         if (flag == "-text")
    //             graphics = false;
    //         else if (flag == "-seed")
    //         {
    //             if (i + 1 < argc)
    //                 srand(std::stoi(argv[i + 1]));
    //             else
    //                 throw "Invalid seed. ";
    //         }
    //         else if (flag == "-scriptfile1")
    //         {   
    //             if (i + 1 < argc) {
    //                 std::cout << "argv[i + 1] is: " << argv[i + 1] << std::endl;
    //                 std::istringstream ss{argv[i + 1]};
    //                 ss >> scriptFiles[0];
    //                 // scriptFiles[0] = argv[i + 1];
    //                 // std::cout << scriptFiles[0] << std::endl;
    //                 std::cout << "IF YOU SEE THIS LINE YOU SUCCEEDED" << std::endl;
    //             }
    //             else
    //                 throw "Invalid scriptfile1. ";
    //         }
    //         else if (flag == "-scriptfile2")
    //         {
    //             if (i + 1 < argc) {
    //                 std::istringstream ss{argv[i + 1]};
    //                 ss >> scriptFiles[1];
    //             }
    //                 // scriptFiles[1] = argv[i + 1];
    //             else
    //                 throw "Invalid scriptfile2. ";
    //         }
    //         else if (flag == "-startlevel")
    //         {
    //             if (i + 1 < argc)
    //                 startLevel = std::stoi(argv[i + 1]);
    //             else
    //                 throw "Invalid startlevel. ";
    //         }
    //         else
    //             throw "Invalid flag. Verify input is correct.";
    //     }
    //     catch (std::string error)
    //     {
    //         std::cerr << error << std::endl;
    //         return 1;
    //     }
    // }

    bool fileExists(fileName) {
        return std::ifstream(fileName);
    }

    std::vector<std::string> args(argv + 1, argv + argc);
    for (int i = 0; i < args.size(); ++i) 
    {
        try {
            if (flag == "-text")
            {
                graphics = false;
            }
            else if (flag == "-seed")
            {
                if (i + 1 < args.size()) {
                    for (int j = 0; j < args[i].size(); ++j) {
                        if (!isDigit(args[i][j])) {
                            throw "Not a valid seed."
                        }
                    }
                    srand(std::stoi(args[i + 1]));
                } else {
                    throw "No seed given.";
                }
            } 
            else if (flag == "-scriptfile1")
            {
                if (i + 1 < args.size()) {
                    if (fileExists(args[i + 1])) {
                        
                    }
                }
            }
        } catch (const char * error) {

        }
    }

    // std::vector<std::string> args(argv + 1, argv + argc);
    // for (int i = 0; i < args.size(); ++i)
    // {
    //     std::string flag = args[i];
    //     if (flag == "-text")
    //     {
    //         graphics = false;
    //     }
    //     else if (flag == "-seed")
    //     {
    //         if (i + 1 < args.size()) {
    //             for (int j = 0; j < args[i].size(); ++j) {
    //                 if (!isDigit(args[i][j])) {
    //                     std::cerr << "Not a valid seed." << std::endl;
    //                     return 1;
    //                 }
    //             }
    //             srand(std::stoi(args[i + 1]));
    //         } else {
    //             std::cerr << "No seed given." << std::endl;
    //             return 1;
    //         }
    //     }
    // }

    for (int i = 1; i < argc; ++i)
    {
        std::string flag = argv[i];
        if (flag == "-text")
        {
            graphics = false;
            std::cout << "text only" << std::endl;
        }
        else if (flag == "-seed")
        {
            ++i;
            int seed;
            flag = argv[i];
            std::istringstream iss{argv[i]};
            iss >> seed;
            srand(seed);
            std::cout << "seeding with " << seed << std::endl;
        }
        else if (flag == "-scriptfile1")
        {
            ++i;
            std::ifstream infile{argv[i]};
            if (infile) {
                flag = argv[i];
                scriptFiles[0] = argv[i];
            } else {
                std::cerr << "Scriptfile1 invalid. Verify input is correct." << std::endl;
                return 1; 
            }
            
        }
        else if (flag == "-scriptfile2")
        {
            ++i;
            std::ifstream infile{argv[i]};
            if (infile) {
                flag = argv[i];
                scriptFiles[1] = argv[i];
            } else {
                std::cerr << "Scriptfile2 invalid. Verify input is correct." << std::endl;
                return 1;
            }
        }
        else if (flag == "-startlevel")
        {
            ++i;
            flag = argv[i];
            std::istringstream iss{argv[i]};
            iss >> startLevel;
        }
        else
        {
            std::cerr << "Invalid flag. Verify input is correct." << std::endl;
            return 1;
        }
    }

    for (auto file : scriptFiles)
        std::cout << file << std::endl;
    // if (valid)
    // {
        if (ncurses)
        {
            // ncurses controller
        }
        else
        {
            std::shared_ptr<Controller> c = std::make_shared<Controller>(graphics, ncurses, scriptFiles, startLevel);
            c->runGame();
        }
    // }
    return 0;
}