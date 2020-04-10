CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
OBJECTS = displayTest.o subject/subject.o point/point.o board/cell.o score/score.o display/textdisplay.o display/window.o display/graphicsdisplay.o  board/board.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = displayTest

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY : clean
clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}