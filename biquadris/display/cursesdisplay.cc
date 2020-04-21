#include "cursesdisplay.h"
#include <ncurses.h>
using namespace std;
CursesDisplay::CursesDisplay()
{
	initscr();
	curs_set(0);
	initColours();
	initScoreWindows();
	initNextBlockWindows();
	initBoardWindows();
	initMessageWindows();
	refresh();
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
}

void CursesDisplay::initScoreWindows()
{
	scoreWindows.emplace_back(newwin(4, 13, 2, 5));
	scoreWindows.emplace_back(newwin(4, 13, 2, 33));
	for (auto scoreWindow : scoreWindows)
	{
		box(scoreWindow, 0, 0);
		wrefresh(scoreWindow);
	}
}

void CursesDisplay::initNextBlockWindows()
{
	nextBlockWindows.emplace_back(newwin(5, 13, 6, 19));
	nextBlockWindows.emplace_back(newwin(5, 13, 6, 47));
	for (auto nextBlockWindow : nextBlockWindows)
	{
		box(nextBlockWindow, 0, 0);
		wrefresh(nextBlockWindow);
	}
}

void CursesDisplay::initBoardWindows()
{
	boardWindows.emplace_back(newwin(20, 13, 6, 5));
	boardWindows.emplace_back(newwin(20, 13, 6, 33));
	for (auto boardWindow : boardWindows)
	{
		box(boardWindow, 0, 0);
		wrefresh(boardWindow);
	}
}

void CursesDisplay::initMessageWindows()
{
	messageWindows.emplace_back(newwin(6, 13, 11, 19));
	messageWindows.emplace_back(newwin(6, 13, 11, 47));
	for (auto messageWindow : messageWindows)
	{
		box(messageWindow, 0, 0);
		wrefresh(messageWindow);
	}
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

	int r = cell.getPoint().getY();
	int c = cell.getPoint().getX();
	if (cell.getOrigin() == Point{1, 23})
	{ // if cell belongs to nextBlockBoard
		window = nextBlockWindows[which];
		c += 2;
		r += 2;
	}
	else if (cell.getOrigin() == Point{6, 23})
	{ // if cell belongs to holdBlockBoard
		window = nextBlockWindows[which];
		c += 8;
		r += 2;
	}
	else // if cell belongs to mainBoard
	{
		window = boardWindows[which];
		c += 1;
		r += 1;
	}
	if (cell.getIsBlind())
	{
		wattron(window, COLOR_PAIR(5));
		mvwaddch(window, r, c, '?');
		wattroff(window, COLOR_PAIR(5));
	}
	else if (cell.isFilled())
	{
		switch (cell.getColour())
		{
		case Xwindow::Cyan:
			wattron(window, COLOR_PAIR(8));
			mvwaddch(window, r, c, 'I');
			wattroff(window, COLOR_PAIR(8));
			break;
		case Xwindow::Blue:
			wattron(window, COLOR_PAIR(4));
			mvwaddch(window, r, c, 'J');
			wattroff(window, COLOR_PAIR(4));
			break;
		case Xwindow::Orange:
			wattron(window, COLOR_PAIR(5));
			mvwaddch(window, r, c, 'L');
			wattroff(window, COLOR_PAIR(5));
			break;
		case Xwindow::Yellow:
			wattron(window, COLOR_PAIR(6));
			mvwaddch(window, r, c, 'O');
			wattroff(window, COLOR_PAIR(6));
			break;
		case Xwindow::Green:
			wattron(window, COLOR_PAIR(3));
			mvwaddch(window, r, c, 'S');
			wattroff(window, COLOR_PAIR(3));
			break;
		case Xwindow::Red:
			wattron(window, COLOR_PAIR(2));

			mvwaddch(window, r, c, 'Z');
			wattroff(window, COLOR_PAIR(2));

			break;
		case Xwindow::Magenta:
			wattron(window, COLOR_PAIR(7));
			mvwaddch(window, r, c, 'T');
			wattroff(window, COLOR_PAIR(7));
			break;
		case Xwindow::Brown:
			wattron(window, COLOR_PAIR(1));
			mvwaddch(window, r, c, 'D');
			wattroff(window, COLOR_PAIR(1));
			break;
		}
	}
	else
	{
		wattron(window, COLOR_PAIR(1));
		mvwaddch(window, r, c, ' ');
		wattroff(window, COLOR_PAIR(1));
	}
	wrefresh(window);
}

void CursesDisplay::drawScore(Score &score)
{
	int which = score.getBoardNumber() - 1;

	mvwprintw(scoreWindows[which], 1, 1, "Level: %d", std::stoi(score.getLevel()));
	mvwprintw(scoreWindows[which], 2, 1, "Score: %d", std::stoi(score.getScore()));
	wrefresh(scoreWindows[which]);
}
void CursesDisplay::drawMessage(Message &message)
{
	int which = message.getBoardNumber() - 1;
	for (unsigned int i = 0; i < message.getText().size(); ++i)
	{
		mvwprintw(messageWindows[which], i + 1, 1, message.getText()[i].c_str());
	}
	wrefresh(messageWindows[which]);
}

void CursesDisplay::clearMessage(Message &message)
{
	int which = message.getBoardNumber() - 1;
	wclear(messageWindows[which]);
	box(messageWindows[which], 0, 0);

	wrefresh(messageWindows[which]);
}
