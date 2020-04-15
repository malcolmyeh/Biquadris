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

void Controller::runGame()
{
    while (true)
    {
        std::string cmd;
        char moveDirection;
        std::string rotateDirection;

        std::cin >> cmd;
        if (cmd == "move")
        {
            std::cin >> moveDirection;
            currentPlayer->moveBlock(moveDirection);
        }
        else if (cmd == "rotate")
        {
            std::cin >> rotateDirection;
            currentPlayer->rotateBlock(rotateDirection);
        }
        else if (cmd == "drop")
        {
            currentPlayer->dropBlock();
        }
        // short cuts
        else if (cmd == "a")
        { // move left
            currentPlayer->moveBlock('L');
        }
        else if (cmd == "s")
        { // move down
            currentPlayer->moveBlock('D');
        }
        else if (cmd == "d")
        { // move right
            currentPlayer->moveBlock('R');
        }
        else if (cmd == "w")
        { // drop
            currentPlayer->dropBlock();
        }
        else if (cmd == "e")
        { // rotate clockwise
            currentPlayer->rotateBlock("CC");
        }
        else if (cmd == "q")
        { // rotate counterclockwise
            currentPlayer->rotateBlock("CW");
        }
        else if (cmd == "quit")
        {
            break;
        }
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