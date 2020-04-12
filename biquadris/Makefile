CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
OBJECTS = displayTest.o subject/subject.o point/point.o board/cell.o level/level.o score/score.o block/block.o display/textdisplay.o display/window.o display/graphicsdisplay.o board/board.o player/player.o player/playermanager.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = displayTest

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY : clean
clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}