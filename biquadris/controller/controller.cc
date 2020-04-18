#include "controller.h"
#include <unordered_map>

Controller::Controller(bool graphics, bool curses, std::vector<std::string> scriptFiles, int startLevel = 0)
{
    makeDisplays(graphics, curses);
    makeBoards();
    initBoards();
    makeScores(startLevel);
    makeMessages();
    makePlayerManagers(startLevel, scriptFiles);

    // set currentPlayer to first player
    currentPlayer = playerManagers.front();
}

void Controller::makeDisplays(bool graphics, bool curses)
{
    std::vector<std::shared_ptr<View>> p1Displays;
    std::vector<std::shared_ptr<View>> p2Displays;
    p1Displays.emplace_back(std::make_shared<TextDisplay>());
    p2Displays.emplace_back(std::make_shared<TextDisplay>());
    if (graphics)
    {
        p1Displays.emplace_back(std::make_shared<GraphicsDisplay>());
        p2Displays.emplace_back(std::make_shared<GraphicsDisplay>());
    }
    // if (curses)
    // {
    //     p1Displays.emplace_back(std::make_shared<CursesDisplay>());
    //     p2Displays.emplace_back(std::make_shared<CursesDisplay>());
    // }
    displays.emplace_back(p1Displays);
    displays.emplace_back(p2Displays);
}

void Controller::makeBoards()
{
    mainBoards.emplace_back(std::make_shared<MainBoard>());
    mainBoards.emplace_back(std::make_shared<MainBoard>());
    nextBlockBoards.emplace_back(std::make_shared<NextBlockBoard>());
    nextBlockBoards.emplace_back(std::make_shared<NextBlockBoard>());
    holdBlockBoards.emplace_back(std::make_shared<HoldBlockBoard>());
    holdBlockBoards.emplace_back(std::make_shared<HoldBlockBoard>());
}

void Controller::makeScores(int startLevel)
{
    // create Scores
    for (auto mainBoard : mainBoards)
        scores.emplace_back(std::make_shared<Score>(startLevel, mainBoard));
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
        messages.emplace_back(std::make_shared<Message>(mainBoard));

    for (auto message : messages)
    {
        for (auto displayType : displays)
        {
            for (auto display : displayType)
                message->attach(display);
        }
    }
}

void Controller::makePlayerManagers(int startLevel, std::vector<std::string> scriptFiles)
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

void Controller::restart()
{
    for (auto mainBoard : mainBoards)
    {
        mainBoard->restart();
    }
    for (auto nextBlockBoard : nextBlockBoards)
    {
        nextBlockBoard->restart();
    }
    for (auto holdBlockBoard : holdBlockBoards)
    {
        holdBlockBoard->restart();
    }
    for (auto message : messages)
        message->clearMessage();
    for (auto score : scores)
        score->resetScore();
}

void Controller::changeTurn()
{
    if (currentPlayer == playerManagers.front())
        currentPlayer = playerManagers.back();
    else
        currentPlayer = playerManagers.front();
}

// returns true if the command starts with input, ie. prefix
//   use of mismatch was found from:
//   https://stackoverflow.com/questions/7913835/check-if-one-string-is-a-prefix-of-another
bool startsWith(std::string input, std::string command)
{
    return (input.length() <= command.length()) &&
           (std::mismatch(input.begin(), input.end(), command.begin()).first == input.end());
}

// std::string match(std::vector<std::string> commands, std::string input) {
//     std::string match = "";
//     for (command : commands) {
//         if (startsWith(input, command) && match != "") {

//         }
//     }
// }

void Controller::runGame()
{
    // we can build a map later to support macros and remapping
    std::vector<std::string> commands = {"left", "down", "right", "clockwise",
                                         "counterclockwise", "drop", "levelup",
                                         "leveldown", "norandom", "random",
                                         "sequence", "restart", "remap", "hold"};
    std::string matchedCommand = "";

    while (true)
    {
        // getOpponentLost
        std::string input;
        std::cin >> input;
        int multiplier = 1;
        if (isdigit(input[0]))
        { // grab multiplier. if none, default is 1
            multiplier = std::stoi(input);
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

        if (errorFlag)
        {
            std::cerr << "Unable to match command. Please try again." << std::endl;
            matchedCommand = "";
            multiplier = 1;
            errorFlag = false;
            continue;
        }

        // change something in command array to remap. the if statement maps to a function. we may have to move the matching
        //   to a function for easier remapping
        if (matchedCommand == commands[0])
        { // move left
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->moveBlock('L');
        }
        else if (matchedCommand == commands[1])
        { // move down
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->moveBlock('D');
        }
        else if (matchedCommand == commands[2])
        { // move right
            for (int i = 0; i < multiplier; ++i)
                currentPlayer->moveBlock('R');
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
                currentPlayer->dropBlock();
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
            currentPlayer->setRandom(false);
        }
        else if (matchedCommand == commands[9])
        { // random
            currentPlayer->setRandom(true);
        }
        else if (matchedCommand == commands[10])
        { // sequence
        }
        else if (matchedCommand == commands[11])
        { // restart
            restart();
        }
        else if (matchedCommand == commands[12])
        { // remapping
            matchedCommand = "";
            std::string oldCommand;
            std::cin >> oldCommand;
            for (auto command : commands)
            {
                if (startsWith(oldCommand, command) && matchedCommand != "")
                {
                    errorFlag = true;
                    break;
                }
                if (startsWith(input, command))
                    matchedCommand = command;
            }

            if (errorFlag)
            {
                std::cerr << "Unable to match command. Please try again." << std::endl;
                matchedCommand = "";
                multiplier = 1;
                errorFlag = false;
                continue;
            }
            std::string newCommand;
            std::cin >> newCommand;
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
        } // no need for else. it is verified in the matching phase.

        multiplier = 1;
        matchedCommand = "";
        changeTurn();
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
        break;
    }
    return level;
}