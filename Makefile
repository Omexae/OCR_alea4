CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -O3 -I/usr/include/SDL2 -D_REENTRANT `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
LDLIBS = -lm -L/usr/lib/x86_64-linux-gnu -lSDL2


SRC_NN = Xor/neural_net/nn.c Xor/matrix/matrix.c Xor/matrix/vector.c
SCR_PIXEL = Blacknwhite/pixel_operations.c
SRC_SDL = Xor/pixel/pixel_operations.c Xor/image_manipulation/to_binarize.c Xor/image_manipulation/smooth.c Xor/image_manipulation/SDL_functions.c Xor/decoupage/decoupage.c  Xor/decoupage/reconstruct.c Xor/image_manipulation/rotate.c

all: main

# Main
SRC = Xor/main.c Xor/image_manipulation/open_image.c Xor/image_manipulation/GTK_functions.c ${SRC_NN} ${SRC_SDL}
OBJ = ${SRC:.c=.o}

main: ${OBJ}
	$(CC) -o main ${OBJ} ${CFLAGS} ${LDLIBS}

SRC_TRAIN = Xor/train.c ${SRC_NN} ${SRC_SDL}
OBJ_TRAIN = ${SRC_TRAIN:.c=.o}

train: ${OBJ_TRAIN}
	$(CC) -o train ${OBJ_TRAIN} ${CFLAGS} ${LDLIBS}
  
SRC_XOR = Xor/xor.c ${SRC_NN} ${SRC_SDL}
OBJ_XOR = ${SRC_XOR:.c=.o}

xornn: ${OBJ_XOR}
				$(CC) -o xornn ${OBJ_XOR} ${CFLAGS} ${LDLIBS}

clean:
	${RM} ${OBJ}
	${RM} ${OBJ_XOR}
	${RM} ${OBJ_BLACKNWHITE}
	${RM} ${OBJ_TRAIN}
