CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: main

main: pixel_operations.o segmentation.o main.o 

main.o: pixel_operations.h segmentation.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main
