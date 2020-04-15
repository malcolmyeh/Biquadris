CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -I/usr/X11/include
OBJECTS = displayTest.o subject/subject.o point/point.o board/cell.o board/board.o level/level.o level/level0.o level/level1.o level/level2.o level/level3.o level/level4.o score/score.o block/block.o block/dblock.o block/iblock.o block/jblock.o block/lblock.o block/oblock.o block/sblock.o block/tblock.o block/zblock.o display/textdisplay.o display/window.o display/graphicsdisplay.o board/mainboard.o board/nextblockboard.o player/player.o player/playermanager.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = displaytest

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib

-include ${DEPENDS}

.PHONY : clean
clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}