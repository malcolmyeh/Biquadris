#include "cursesdisplay.h"
#include <ncurses.h>
using namespace std;
CursesDisplay::CursesDisplay()
{
	initscr();
	initColours();
	initScoreWindows();
	initNextBlockWindows();
	initBoardWindows();
	initMessageWindows();
}

void CursesDisplay::initColours()
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_CYAN, COLOR_BLACK);
	initScoreWindows();
}

void CursesDisplay::initScoreWindows()
{
	scoreWindows.emplace_back(newwin(3, 11, 0, 0));
	scoreWindows.emplace_back(newwin(3, 11, 0, 16));
}

void CursesDisplay::initNextBlockWindows()
{
	nextBlockWindows.emplace_back(newwin(4, 11, 22, 0));
	nextBlockWindows.emplace_back(newwin(4, 11, 22, 16));
}

void CursesDisplay::initBoardWindows()
{ 
	boardWindows.emplace_back(newwin(18, 11, 3, 0));
	boardWindows.emplace_back(newwin(18, 11, 3, 16));
}

void CursesDisplay::initMessageWindows()
{
	messageWindows.emplace_back(newwin(4, 11, 25, 0));
	messageWindows.emplace_back(newwin(4, 11, 25, 16));
}

CursesDisplay::~CursesDisplay()
{
	for (auto window : scoreWindows)
		delwin(window);
	for (auto window : nextBlockWindows)
		delwin(window);
	for (auto window : boardWindows)
		delwin(window);
	for (auto window : messageWindows)
		delwin(window);
	endwin();
}

void CursesDisplay::drawCell(Cell &cell)
{
	WINDOW *window;
	int which = cell.getBoardNumber() - 1;
	if (cell.getOrigin() == Point{1, 23})
	{
		window = nextBlockWindows[which];
	}
	else
	{
		window = boardWindows[which];
	}
	if (cell.getIsBlind())
	{
		wattron(window, COLOR_PAIR(2));
		mvwaddch(window, cell.getPoint().getY(),
				 cell.getPoint().getX(), '?');
		wattroff(window, COLOR_PAIR(2));
	}
	else if (cell.isFilled())
	{
		switch (cell.getColour())
		{
		case Xwindow::Cyan:
			wattron(window, COLOR_PAIR(8));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'I');
			wattroff(window, COLOR_PAIR(8));
			break;
		case Xwindow::Blue:
			wattron(window, COLOR_PAIR(4));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'J');
			wattroff(window, COLOR_PAIR(4));
			break;
		case Xwindow::Orange:
			wattron(window, COLOR_PAIR(5));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'L');
			wattroff(window, COLOR_PAIR(5));
			break;
		case Xwindow::Yellow:
			wattron(window, COLOR_PAIR(6));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'O');
			wattroff(window, COLOR_PAIR(6));
			break;
		case Xwindow::Green:
			wattron(window, COLOR_PAIR(3));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'S');
			wattroff(window, COLOR_PAIR(3));
			break;
		case Xwindow::Red:
			wattron(window, COLOR_PAIR(2));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'Z');
			wattroff(window, COLOR_PAIR(2));
			break;
		case Xwindow::Magenta:
			wattron(window, COLOR_PAIR(7));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'T');
			wattroff(window, COLOR_PAIR(7));
			break;
		case Xwindow::Brown:
			wattron(window, COLOR_PAIR(1));
			mvwaddch(window, cell.getPoint().getY(),
					 cell.getPoint().getX(), 'D');
			wattroff(window, COLOR_PAIR(1));
			break;
		}
	}
	else
	{
		wattron(window, COLOR_PAIR(1));
		mvwaddch(window, cell.getPoint().getY(),
				 cell.getPoint().getX(), ' ');
		wattroff(window, COLOR_PAIR(1));
	}
}
void CursesDisplay::drawScore(Score &score)
{
	int which = score.getBoardNumber() - 1;
	wclear(scoreWindows[which]);
	wprintw(scoreWindows[which], "Level:%*d", 5, score.getLevel());
	wprintw(scoreWindows[which], "Score:%*d", 5, score.getScore());
	wprintw(scoreWindows[which], "-----------");
	wrefresh(scoreWindows[which]);
}
void CursesDisplay::drawMessage(Message &message)
{
	int which = message.getBoardNumber() - 1;
	wclear(messageWindows[which]);
	for (auto line : message.getText())
		wprintw(messageWindows[which], line.c_str());
}
void CursesDisplay::clearMessage(Message &message) {}