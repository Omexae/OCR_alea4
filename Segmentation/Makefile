CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: decoupage

decoupage: pixel_operations.o decoupage.o

decoupage.o: pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} decoupage
