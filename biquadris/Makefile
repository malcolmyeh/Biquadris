CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -I/usr/X11/include
OBJECTS = main.o subject/subject.o point/point.o board/cell.o board/board.o level/level.o level/level0.o level/level1.o level/level2.o level/level3.o level/level4.o score/score.o block/block.o block/dblock.o block/iblock.o block/jblock.o block/lblock.o block/oblock.o block/sblock.o block/tblock.o block/zblock.o display/textdisplay.o display/window.o display/graphicsdisplay.o board/mainboard.o board/nextblockboard.o board/holdblockboard.o player/player.o player/playerdecorator.o player/heavyplayer.o player/heavylevel.o player/playermanager.o message/message.o controller/controller.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib

-include ${DEPENDS}

.PHONY : clean
clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}