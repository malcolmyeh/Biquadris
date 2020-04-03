// #include "controller.h"

//
#include <string>
#include <sstream>
#include <iostream>
//

int main(int argc, char *argv[])
{
    bool graphics = true;
    std::string scriptFile1 = "sequence1.txt";
    std::string scriptFile2 = "sequence2.txt";
    int startLevel = 0;

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
            flag = argv[i];
            scriptFile1 = argv[i];
        }
        else if (flag == "-scriptfile2")
        {
            ++i;
            flag = argv[i];
            scriptFile2 = argv[i];
        }
        else if (flag == "-startlevel")
        {
            ++i;
            flag = argv[i];
            std::istringstream iss{argv[i]};
            iss >> startLevel;
        }
        else {
            std::cerr << "Invalid flag. Verify input is correct." << std::endl;
            return 1;
        }
    }
    std::cout << "p1 block source: " << scriptFile1 << std::endl
              << "p2 block source: "
              << scriptFile2 << std::endl
              << "starting on level " << startLevel << std::endl;

    // Controller c {graphics, scriptFile1, scriptFile2, startLevel};
    // c.runGame();
}