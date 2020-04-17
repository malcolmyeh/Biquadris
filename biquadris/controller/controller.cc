#include "controller.h"

    Controller::Controller(bool graphics, std::vector<std::string> scriptFiles, int startLevel = 0)
    {
        std::cout << "displays" << std::endl;
        // create Displays
        std::vector<std::vector<std::shared_ptr<View>>> playerViews(2);
        for (auto views : playerViews)
            views.emplace_back(std::make_shared<TextDisplay>());
        if (graphics)
        {
            for (auto views : playerViews)
                views.emplace_back(std::make_shared<GraphicsDisplay>());
        }
        std::cout << "boards" << std::endl;

        // create Boards (+ Cells)
        std::vector<std::vector<std::shared_ptr<Board>>> playerBoards(2);
        for (auto boards : playerBoards)
        {
            boards.emplace_back(std::make_shared<MainBoard>());
            boards.emplace_back(std::make_shared<NextBlockBoard>());
        }
        std::cout << "scores" << std::endl;

        // create Scores
        std::cout << "playerboards size: " << playerBoards.size() << std::endl;
        std::vector<std::shared_ptr<Score>> scores;
        for (auto boards : playerBoards)
        { // make Score with each mainBoard
            std::cout << "boards size: " << playerBoards.size() << std::endl;
            std::shared_ptr<Score> score = std::make_shared<Score>(startLevel, boards.front());
            std::cout << "check" << std::endl;
            scores.emplace_back(score);
        }
        std::cout << "pm" << std::endl;

        // create PlayerManagers and initialize starting Blocks
        for (int i = 0; i < 2; ++i)
        {
            playerManagers.emplace_back(std::make_shared<PlayerManager>(
                scores[i], playerBoards[i].front(), createLevel(startLevel, scriptFiles[i]), playerBoards[i].back()));
            playerManagers[i]->initBlocks();
        }

        std::cout << "set op" << std::endl;

        // set Players as each other's opponents
        playerManagers.front()->setOpponent(playerManagers.back()->getPlayer());
        playerManagers.back()->setOpponent(playerManagers.front()->getPlayer());

        std::cout << "link score display" << std::endl;

        // link Scores and Displays
        for (int i = 0; i < 2; ++i)
        {
            for (auto view : playerViews[i])
                scores[i]->attach(view);
            scores[i]->drawDisplays();
        }

        std::cout << "init board" << std::endl;

        // initialize Boards and link to Displays
        for (int i = 0; i < 2; ++i)
        {
            playerBoards[i].front()->init(i + 1);
            playerBoards[i].back()->init(i + 1);
            for (auto view : playerViews[i])
            {
                playerBoards[i].front()->setDisplay(view);
                playerBoards[i].back()->setDisplay(view);
            }
            playerBoards[i].front()->refresh();
            playerBoards[i].back()->refresh();
        }

        // set currentPlayer to first player
        currentPlayer = playerManagers.front();
    }

void Controller::changeTurn()
{
    if (currentPlayer = playerManagers.front())
        currentPlayer = playerManagers.back();
    else
        currentPlayer = playerManagers.front();
}

// returns true if the command starts with input, ie. prefix
//   use of mismatch was found from:
//   https://stackoverflow.com/questions/7913835/check-if-one-string-is-a-prefix-of-another
bool startsWith(std::string input, std::string command) {
    return (input.length() <= command.length()) && 
           (std::mismatch(input.begin(), input.end(), command.begin()).first == input.end())
}

void Controller::runGame()
{   
    // we can build a map later to support macros and remapping
    std::vector<std::string> commands = {"left", "down", "right", "clockwise", 
                                         "counterclockwise", "drop", "levelup", 
                                         "leveldown", "norandom", "random", 
                                         "sequence", "restart", "remap"};
    std::unordered_map<std::string, void (*)(int)> commands = {"left": };
    std::string matchedCommand = "";
    
    while (true)
    {   
        // getOpponentLost
        std::string input;
        std::cin >> input;
        int multiplier = 1;
        if (isDigit(input[0])) { // grab multiplier. if none, default is 1
            multiplier = std::atoi(input); 
        }

        for (command : commands) { // match command
            if (startsWith(input, command) && matchedCommand != "")
                // ambiguous, can't match - what will we do here? error flag to redo loop?
                std::cerr << "Unable to find command." << std::endl;

            if (startsWith(input, command))
                matchedCommand = command;
        }

        // change something in command array to remap. the if statement maps to a function. we may have to move the matching
        //   to a function for easier remapping
        if (matchedCommand == commands[0]) { // move left
            for (int i = 0; i < multiplier; ++i) currentPlayer->moveBlock('L');
        } else if (matchedCommand == commands[1]) { // move down
            for (int i = 0; i < multiplier; ++i) currentPlayer->moveBlock('D');
        } else if (matchedCommand == commands[2]) { // move right
            for (int i = 0; i < multiplier; ++i) currentPlayer->moveBlock('R');
        } else if (matchedCommand == commands[3]) { // rotate clockwise
            for (int i = 0; i < multiplier; ++i) currentPlayer->rotateBlock("CW");
        } else if (matchedCommand == commands[4]) { // rotate counterclockwise
            for (int i = 0; i < multiplier; ++i) currentPlayer->rotateBlock("CCW");
        } else if (matchedCommand == commands[5]) { // drop piece 
            for (int i = 0; i < multiplier; ++i) currentPlayer->dropBlock();
        } else if (matchedCommand == commands[6]) { // level up 

        } else if (matchedCommand == commands[7]) { // level down

        } else if (matchedCommand == commands[8]) { // no random

        } else if (matchedCommand == commands[9]) { // random 

        } else if (matchedCommand == commands[10]) { // sequence

        } else if (matchedCommand == commands[11]) { // restart 

        } else if (matchedCommand == commands[12]) { // remapping 
            std::string newCommand;
            std::cin >> newCommand;
            // here, we should probably match commands again and find the index of the commands array we want to remap
            //   and change it to that in the commands array.
        } // no need for else. it is verified in the matching phase. 

        // remember to reset multipliers and matchedCommand at the end of loop
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