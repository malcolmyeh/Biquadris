#include "controller/controller.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>

int main(int argc, char *argv[])
{
    bool graphics = true;
    std::vector<std::string> scriptFiles = {"sequences/sequence1.txt", "sequence/sequencefile2"};
    int startLevel = 2;
    std::cout << "BEFORE FLAG" << std::endl;
    // handling flags
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
            if (infile)
            {
                flag = argv[i];
                scriptFiles[0] = argv[i];
            }
            else
            {
                std::cerr << "Scriptfile1 invalid. Verify input is correct." << std::endl;
                return 1;
            }
        }
        else if (flag == "-scriptfile2")
        {
            ++i;
            std::ifstream infile{argv[i]};
            if (infile)
            {
                flag = argv[i];
                scriptFiles[1] = argv[i];
            }
            else
            {
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
    std::cout << "BEFORE CONTROLLER" << std::endl;

    std::shared_ptr<Controller> c = std::make_shared<Controller>(graphics, scriptFiles, startLevel);

    c->runGame();

    return 0;
}