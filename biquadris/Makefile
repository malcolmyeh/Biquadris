CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
OBJECTS = displayTest.o subject/subject.o point/point.o board/cell.o level/level.o level/level0.o level/level1.o level/level2.o level/level3.o level/level4.o score/score.o block/block.o block/dblock.o block/iblock.o block/jblock.o block/lblock.o block/oblock.o block/sblock.o block/tblock.o block/zblock.o display/textdisplay.o display/window.o display/graphicsdisplay.o board/board.o player/player.o player/playermanager.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = displayTest

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY : clean
clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}