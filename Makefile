CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -O3 -I/usr/include/SDL2 -D_REENTRANT `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
LDLIBS = -lm -L/usr/lib/x86_64-linux-gnu -lSDL2


SRC_NN = Xor/neural_net/nn.c Xor/matrix/matrix.c Xor/matrix/vector.c
SCR_PIXEL = Blacknwhite/pixel_operations.c

all: main

# Main
OBJ = ${SRC:.c=.o}

main: ${OBJ}
	$(CC) -o main ${OBJ} ${CFLAGS} ${LDLIBS}
  
SRC_XOR = Xor/xor.c ${SRC_NN} ${SRC_SDL}
OBJ_XOR = ${SRC_XOR:.c=.o}

xornn: ${OBJ_XOR}
				$(CC) -o xornn ${OBJ_XOR} ${CFLAGS} ${LDLIBS}

clean:
	${RM} ${OBJ}
	${RM} ${OBJ_XOR}
	${RM} ${OBJ_BLACKNWHITE}
