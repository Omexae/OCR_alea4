#include <err.h>
#include <SDL.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

// TODO: Insert all the above functions.
void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void SDL_FreeSurface(SDL_Surface *surface);

int is_space(SDL_Surface* img)
{
	Uint32 pixel;
	Uint8 r, g, b;
	int space = 1;
	
	for(int y = 0; y < img->h; y++)
	{
		for(int x = 0; x < img->w; x++)
		{
			pixel = get_pixel(img, x, y);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			if(!r && !g && !b)
			{
				space = 0;
				break;
			}
		}
	}
	
	return space;
}

/*SDL_Surface* copy_image(SDL_Surface *img)
{
	Uint32 pixel;
	SDL_Surface* copy = SDL_CreateRGBSurface(0,
								  img -> w,
								  img -> h,
								  img -> format -> BitsPerPixel,0,0,0,0);
	  
	for(int x = 0; x < img -> w; x++)
	{
		for(int y = 0; y < img -> h; y++)
		{
		  pixel = get_pixel(img, x, y);
		  put_pixel(copy, x, y, pixel);
		}
	}
	return(copy);
}*/

SDL_Surface* draw_lines(SDL_Surface *img)
{
	Uint32 pixel;
	Uint8 r, g, b;
	int is_blank = 1;
	int first_cut = 1;
	int height = img -> h;
	int width = img -> w;
	
	for(int i = 0; i < height; i++)
	{
		is_blank = 1;
		
		int j = 0;
		while(j < width && is_blank)
		{
			pixel = get_pixel(img, j, i);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			if(!r && !g && !b)
			{
				is_blank = 0;
			}
			j++;
		}
		
		if(!is_blank && first_cut)
		{
			for(int k = 0; k < width; k++)
			{
				pixel = SDL_MapRGB(img -> format, 255, 0, 0);
				if(i > 0)
				{
					put_pixel(img, k, i - 1, pixel);
				}
			}
			first_cut = 0;
		}
		
		if(is_blank && !first_cut)
		{
			for(int k = 0; k < width; k++)
			{
				pixel = SDL_MapRGB(img -> format, 255, 0, 0);
				put_pixel(img, k, i, pixel);
			}
			first_cut = 1;
		}
	}
	
	return(img);
}

SDL_Surface* draw_columns(SDL_Surface *img)
{
	Uint32 pixel;
	Uint8 r, g, b;
	int is_blank = 1;
	int first_cut = 1;
	int first_line = 0;
	int second_line = 0;
	int x = 0;
	int height = img -> h;
	int width = img -> w;
	
	for(int y = 0; y < height; y++)
	{
		pixel = get_pixel(img, 0, y);
		SDL_GetRGB(pixel, img->format, &r, &g, &b);
		if(r && !g && !b)
		{
			if(first_line)
			{
				second_line = 1;
			}
			else
			{
				first_line = 1;
				x = y;
			}
		}
		
		if(first_line && second_line)
		{
			for(int i = 0; i < width; i++)
			{	
				is_blank = 1;
				for(int j = x; j < y; j++)
				{
					pixel = get_pixel(img, i, j);
					SDL_GetRGB(pixel, img->format, &r, &g, &b);
					if(r == 0 && g == 0 && b == 0)
					{
						is_blank = 0;
						break;
					}
				}
				
				if(!is_blank && first_cut)
				{
					for(int k = x; k < y; k++)
					{
						pixel = SDL_MapRGB(img -> format, 255, 0, 0);
						if(i > 0)
						{
							put_pixel(img, i - 1, k, pixel);
						}
					}
					first_cut = 0;
				}
				else if(is_blank && !first_cut)
				{
					for(int k = x; k < y; k++)
					{
						pixel = SDL_MapRGB(img -> format, 255, 0, 0);
						put_pixel(img, i, k, pixel);
					}
					first_cut = 1;
				}
			}
			first_line = 0;
			second_line = 0;
		}
	}
	
	return(img);
}

int main()
{
	SDL_Surface* image_surface;
	SDL_Surface* screen_surface;

	// TODO: Initialize the SDL
	init_sdl();

	image_surface = load_image("my_image.jpg");
	// TODO: Display the image.
	screen_surface = display_image(image_surface);

	// TODO: Wait for a key to be pressed.
	wait_for_keypressed();
	
	//int width = image_surface->w;
	//int height = image_surface->h;

	/*for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			Uint32 pixel = get_pixel(image_surface, x, y);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			int average = 0.3 * r + 0.59 * g + 0.11 * b;
			pixel = SDL_MapRGB(image_surface->format, average, average, average);
			//pixel = get_pixel(image_surface, x, y);
			put_pixel(image_surface, x, y, pixel);
		}
	}*/
	
	image_surface = draw_lines(image_surface);
	update_surface(screen_surface, image_surface);
	wait_for_keypressed();
	
	image_surface = draw_columns(image_surface);
	update_surface(screen_surface, image_surface);
	wait_for_keypressed();

	// TODO: Free the image surface.
	// TODO: Free the screen surface.
	SDL_FreeSurface(image_surface);
	SDL_FreeSurface(screen_surface);
	return 0;
}
