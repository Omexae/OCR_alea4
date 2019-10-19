# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: blacknwhite

blacknwhite: pixel_operations.o blacknwhite.o

blacknwhite.o: pixel_operations.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} blacknwhite

# END
