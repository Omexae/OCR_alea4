#ifndef DECOUPAGE_H
#define DECOUPAGE_H

#include <stdlib.h>
#include <SDL.h>

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
SDL_Surface* draw_lines(SDL_Surface *img);
SDL_Surface* draw_columns(SDL_Surface *img);
int is_space(SDL_Surface* img);

#endif
