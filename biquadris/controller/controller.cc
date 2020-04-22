#include "controller.h"
#include "../player/heavylevel.h"
#include <vector>
#include <ncurses.h>

Controller::Controller(bool graphics, bool curses, std::vector<std::string> scriptFiles, int startLevel = 0)
    : startLevel{startLevel}, scriptFiles{scriptFiles}, curses{curses}
{
    makeDisplays(graphics, curses);
    makeBoards();
    initBoards();
    makeScores();
    makeMessages();
    makePlayerManagers();

    // set currentPlayer to first player
    currentPlayer = playerManagers.front();
}

void Controller::makeDisplays(bool graphics, bool curses)
{
    std::vector<std::shared_ptr<View>> p1Displays;
    std::vector<std::shared_ptr<View>> p2Displays;

    if (curses)
    {
        initscr();
        curs_set(0);
        p1Displays.emplace_back(std::make_shared<CursesDisplay>());
        p2Displays.emplace_back(std::make_shared<CursesDisplay>());
        inputBox = newwin(5, 55, 26, 5);
        wmove(inputBox, 0, 0);
        wrefresh(inputBox);
    }
    else
    {
        std::shared_ptr<TextDisplay> td = std::make_shared<TextDisplay>();
        p1Displays.emplace_back(td);
        p2Displays.emplace_back(td);
    }
    if (graphics)
    {
        std::shared_ptr<GraphicsDisplay> gd = std::make_shared<GraphicsDisplay>();
        p1Displays.emplace_back(gd);
        p2Displays.emplace_back(gd);
    }

    displays.emplace_back(p1Displays);
    displays.emplace_back(p2Displays);
}

void Controller::makeBoards()
{
    mainBoards.emplace_back(std::make_shared<MainBoard>(1));
    mainBoards.emplace_back(std::make_shared<MainBoard>(2));
    nextBlockBoards.emplace_back(std::make_shared<NextBlockBoard>(1));
    nextBlockBoards.emplace_back(std::make_shared<NextBlockBoard>(2));
    holdBlockBoards.emplace_back(std::make_shared<HoldBlockBoard>(1));
    holdBlockBoards.emplace_back(std::make_shared<HoldBlockBoard>(2));
}

void Controller::makeScores()
{
    // create Scores
    for (auto mainBoard : mainBoards)
        scores.emplace_back(std::make_shared<Score>(startLevel, mainBoard->getBoardNumber()));
    // link to Displays
    for (auto score : scores)
    {
        for (auto displayType : displays)
        {
            for (auto display : displayType)
                score->attach(display);
        }
        score->drawDisplays();
    }
}

void Controller::makeMessages()
{
    for (auto mainBoard : mainBoards)
        messages.emplace_back(std::make_shared<Message>(mainBoard->getBoardNumber()));

    for (auto message : messages)
    {
        for (auto displayType : displays)
        {
            for (auto display : displayType)
                message->attach(display);
        }
    }
}

void Controller::makePlayerManagers()
{
    // create PlayerManagers and initialize Blocks
    for (int i = 0; i < 2; ++i)
    {
        playerManagers.emplace_back(
            std::make_shared<PlayerManager>(scores[i],
                                            mainBoards[i], createLevel(startLevel, scriptFiles[i]), nextBlockBoards[i], holdBlockBoards[i],
                                            messages[i]));
        playerManagers[i]->initBlocks();
    }
    if (startLevel >= 3)
    {
        for (auto playerManager : playerManagers)
            playerManager->setPlayer(std::make_shared<HeavyLevel>(playerManager->getPlayer()));
    }

    // set each Players as each other's opponents
    playerManagers.front()->setOpponent(playerManagers.back());
    playerManagers.back()->setOpponent(playerManagers.front());
}

void Controller::initBoards()
{

    for (int i = 0; i < 2; ++i)
    {
        mainBoards[i]->init(i + 1);
        for (auto displayType : displays)
        {
            for (auto display : displayType)
                mainBoards[i]->setDisplay(display);
        }
        nextBlockBoards[i]->init(i + 1);
        for (auto displayType : displays)
        {
            for (auto display : displayType)
                nextBlockBoards[i]->setDisplay(display);
        }
        holdBlockBoards[i]->init(i + 1);
        for (auto displayType : displays)
        {
            for (auto display : displayType)
                holdBlockBoards[i]->setDisplay(display);
        }
        mainBoards[i]->refresh();
        nextBlockBoards[i]->refresh();
        holdBlockBoards[i]->refresh();
    }
}

std::shared_ptr<Level> Controller::createLevel(int levelNumber, std::string file)
{
    std::shared_ptr<Level> level;
    switch (levelNumber)
    {
    case 0:
        level = std::make_shared<Level0>(file);
        break;
    case 1:
        level = std::make_shared<Level1>(file);
        break;
    case 2:
        level = std::make_shared<Level2>(file);
        break;
    case 3:
        level = std::make_shared<Level3>(file);
        break;
    case 4:
        level = std::make_shared<Level4>(file);
    }
    return level;
}

void Controller::restart()
{
    for (auto message : messages)
        message->clearMessage();
    for (auto score : scores)
        score->resetScore();

    mainBoards.clear();
    nextBlockBoards.clear();
    holdBlockBoards.clear();
    makeBoards();
    initBoards();
    playerManagers.clear();
    makePlayerManagers();
    currentPlayer = playerManagers.front();
    runGame();
}

void Controller::changeTurn()
{
    if (currentPlayer == playerManagers.front())
        currentPlayer = playerManagers.back();
    else
        currentPlayer = playerManagers.front();
}

// returns true if the command starts with input, iwwe. prefix
//   use of mismatch was found from:
//   https://stackoverflow.com/questions/7913835/check-if-one-string-is-a-prefix-of-another
bool startsWith(std::string input, std::string command)
{
    return (input.length() <= command.length()) &&
           (std::mismatch(input.begin(), input.end(), command.begin()).first == input.end());
}

void readString(WINDOW *inputBox, std::string &str)
{
    // wrefresh(inputBox);
    char nstr[80];
    wgetstr(inputBox, nstr);
    str = nstr;
    wclear(inputBox);
    wrefresh(inputBox);
}

void printString(WINDOW *inputBox, std::string str)
{
    wclear(inputBox);
    mvwprintw(inputBox, 0, 0, str.c_str());
    wrefresh(inputBox);
}

void Controller::gameEnd()
{
    for (auto score : scores)
        score->drawHighScore();
    std::vector<std::string> commands = {"restart", "quit"};
    std::string matchedCommand = "";

    while (true)
    {
        std::string input;
        if (curses)
            readString(inputBox, input);
        else
            std::cin >> input;
        if (std::cin.eof())
            break;

        bool errorFlag = false;

        for (auto command : commands)
        {
            if (startsWith(input, command) && matchedCommand != "")
            {
                errorFlag = true;
                break;
            }
            if (startsWith(input, command))
                matchedCommand = command;
        }

        if (matchedCommand == "")
        {
            std::cerr << "No commands matched." << std::endl;
            continue;
        }

        if (errorFlag)
        {
            std::cerr << "Unable to match command. Please try again." << std::endl;
            matchedCommand = "";
            errorFlag = false;
            continue;
        }

        if (matchedCommand == commands[0])
        { // restart
            restart();
        }
        else if (matchedCommand == commands[1])
        { // quit
            std::cout << "QUIT ENTERED" << std::endl;
            break;
        }
        matchedCommand = "";
    }
    delwin(inputBox);
    endwin();
}

void Controller::runGame()
{
    std::vector<std::string> commands = {"left", "down", "right", "clockwise",
                                         "counterclockwise", "drop", "levelup",
                                         "leveldown", "norandom", "random",
                                         "sequence", "restart", "remap", "hold",
                                         "I", "J", "L", "O", "S", "T", "Z", "blind",
                                         "heavy", "force", "quit"};
    std::vector<std::string> fileInput;
    bool readFileInput = false;
    std::string matchedCommand = "";
    currentPlayer->setIsPlaying(); // set p1 to take first turn

    while (true)
    {
        if (currentPlayer->getIsLost())
            gameEnd();
        if (!currentPlayer->getIsPlaying())
        {                 // if current player turn ends
            changeTurn(); // change player
            currentPlayer->setIsPlaying();
        }
        std::string input;
        if (readFileInput)
        {
            if (fileInput.empty())
            {
                readFileInput = false;
            }
            else
            {
                input = fileInput[0];
                fileInput.erase(fileInput.begin(), fileInput.begin() + 1);
            }
        }
        else
        {
            if (curses)
                readString(inputBox, input);
            else
                std::cin >> input;
            if (std::cin.eof())
                break;
        }
        int multiplier = 1;
        if (isdigit(input[0]))
        { // grab multiplier. if none, default is 1
            multiplier = std::stoi(input);
            for (unsigned int i = 0; i < std::to_string(multiplier).length(); ++i)
            {
                input.erase(0, 1);
            }
        }

        bool errorFlag = false;

        for (auto command : commands)
        { // match command
            if (startsWith(input, command) && matchedCommand != "")
            {
                errorFlag = true;
                break;
            }
            if (startsWith(input, command))
                matchedCommand = command;
        }

        if (matchedCommand == "")
        {
            if (curses)
                printString(inputBox, "No commands matched. ");
            else
                std::cerr << "No commands matched." << std::endl;
            continue;
        }

        if (errorFlag)
        {
            if (curses)
                printString(inputBox, "Unable to match command. Please try again.");
            else
                std::cerr << "Unable to match command. Please try again." << std::endl;
            matchedCommand = "";
            multiplier = 1;
            errorFlag = false;
            continue;
        }

        if (matchedCommand == commands[0])
        { // move left
            currentPlayer->moveBlock('L', multiplier);
        }
        else if (matchedCommand == commands[1])
        { // move down
            currentPlayer->moveBlock('D', multiplier);
        }
        else if (matchedCommand == commands[2])
        { // move right
            currentPlayer->moveBlock('R', multiplier);
        }
        else if (matchedCommand == commands[3])
        { // rotate clockwise
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->rotateBlock("CW");
        }
        else if (matchedCommand == commands[4])
        { // rotate counterclockwise
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->rotateBlock("CCW");
        }
        else if (matchedCommand == commands[5])
        { // drop piece
            for (int i = 0; i < multiplier; ++i)
            {
                currentPlayer->dropBlock();
                if (currentPlayer->getIsLost())
                    break;
            }
        }
        else if (matchedCommand == commands[6])
        { // level up
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->changeLevel(1);
        }
        else if (matchedCommand == commands[7])
        { // level down
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->changeLevel(-1);
        }
        else if (matchedCommand == commands[8])
        { // no random
            std::string file;
            if (curses)
                readString(inputBox, file);
            else
                std::cin >> file;
            currentPlayer->setRandom(false);
            currentPlayer->setLevel(createLevel(currentPlayer->getLevel(), file));
        }
        else if (matchedCommand == commands[9])
        { // random
            currentPlayer->setRandom(true);
        }
        else if (matchedCommand == commands[10])
        { // sequence
            std::string filename;
            if (curses)
                readString(inputBox, filename);
            else
                std::cin >> filename;
            std::ifstream infile{filename};
            if (!infile.good())
            {
                multiplier = 1;
                matchedCommand = "";
                std::cerr << "File either does not exist, or cannot be opened." << std::endl;
                continue;
            }

            // file exists - move on
            while (infile >> filename)
            {
                fileInput.emplace_back(filename);
            }
            readFileInput = true;
        }
        else if (matchedCommand == commands[11])
        { // restart
            restart();
        }
        else if (matchedCommand == commands[12])
        { // remapping
            matchedCommand = "";
            std::cout << "MATCHED COMMAND IS: " << matchedCommand << std::endl;
            std::string oldCommand;
            if (curses)
                readString(inputBox, oldCommand);
            else
                std::cin >> oldCommand;
            std::cout << "OLD COMMAND IS:" << oldCommand << std::endl;
            std::string newCommand;
            if (curses)
                readString(inputBox, newCommand);
            else
                std::cin >> newCommand;
            for (auto command : commands)
            {
                if (startsWith(oldCommand, command) && matchedCommand != "")
                {
                    errorFlag = true;
                    break;
                }
                if (startsWith(oldCommand, command))
                {
                    matchedCommand = command;
                    std::cout << "MATCHED COMMAND JUST CHANGED TO:" << matchedCommand << std::endl;
                }
            }
            std::cout << "MATCHED COMMAND IS: " << matchedCommand << std::endl;
            if (matchedCommand == "")
            {
                std::cerr << "Old command did not match anything." << std::endl;
                continue;
            }

            if (errorFlag)
            {
                std::cerr << "Unable to match command. Please try again." << std::endl;
                matchedCommand = "";
                multiplier = 1;
                errorFlag = false;
                continue;
            }

            for (auto a : commands)
            {
                if (a == newCommand)
                { // duplicate
                    errorFlag = true;
                    break;
                }
            }
            if (errorFlag)
            {
                std::cerr << "New command requested already exists, please try again." << std::endl;
                matchedCommand = "";
                multiplier = 1;
                errorFlag = false;
                continue;
            }

            // matched old command is found and new command to change it to is entered. remap now
            for (auto &a : commands)
            {
                if (a == oldCommand)
                    a = newCommand;
            }
        }
        else if (matchedCommand == commands[13])
        { // hold command
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->holdBlock();
        }
        else if (matchedCommand == commands[14])
        { // I
            currentPlayer->forceBlock('I');
        }
        else if (matchedCommand == commands[15])
        { // J
            currentPlayer->forceBlock('J');
        }
        else if (matchedCommand == commands[16])
        { // L
            currentPlayer->forceBlock('L');
        }
        else if (matchedCommand == commands[17])
        { // O
            currentPlayer->forceBlock('O');
        }
        else if (matchedCommand == commands[18])
        { // S
            currentPlayer->forceBlock('S');
        }
        else if (matchedCommand == commands[19])
        { // T
            currentPlayer->forceBlock('T');
        }
        else if (matchedCommand == commands[20])
        { // Z
            currentPlayer->forceBlock('Z');
        }

        else if (matchedCommand == commands[21])
        { // blind
            currentPlayer->blind();
        }
        else if (matchedCommand == commands[22])
        { // heavy
            currentPlayer->makeHeavy();
        }
        else if (matchedCommand == commands[23])
        { // force
            char blockType;
            if (curses)
                blockType = wgetch(inputBox);
            else
                std::cin >> blockType;
            currentPlayer->forceOpponentBlock(blockType);
        }
        else if (matchedCommand == commands[24])
        { // quit
            break;
        } // no need for else. it is verified in the matching phase.
        multiplier = 1;
        matchedCommand = "";
    }
    delwin(inputBox);
    endwin();
}
