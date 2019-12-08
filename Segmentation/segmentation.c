#include <err.h>
#include <SDL.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

// Create blocs of characters
// We will use the coordonates to redraw the image
SDL_Surface* draw_blocs(SDL_Surface *img);

// Create lines between characters
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

    int cut_x = 0;
    int cut_x_max = 0;
    int cut_y = 0;
    int cut_y_max = 0;

    //int character_nb = 0;
    //char character_name = "";
	
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
                    cut_x = i;
                    cut_y = x + 1;
					first_cut = 0;
				}
				else if(is_blank && !first_cut)
				{
					for(int k = x; k < y; k++)
					{
						pixel = SDL_MapRGB(img -> format, 255, 0, 0);
						put_pixel(img, i, k, pixel);
					}
                    cut_x_max = i-1;
                    cut_y_max = y;
					first_cut = 1;
				}
			}
			first_line = 0;
			second_line = 0;
            //printf("test\n");
		}
        
        SDL_Surface* copy = SDL_CreateRGBSurface(0, cut_x_max - cut_x, cut_y_max - cut_y,
                                      img->format->BitsPerPixel,0,0,0,0);

        for(int w = 0; w < copy -> w; w++)
        {
            for(int h = 0; h < copy -> h; h++)
            {
              pixel = get_pixel(img, w + cut_x, h + cut_y);
              put_pixel(copy, w, h, pixel);
            }
        }
        SDL_SaveBMP(copy, "test.bmp");
        SDL_FreeSurface(copy);
        //character_name = (char)(character_nb) + ".jpg";
        //SDL_Surface* character = cut_image(img, cut_x, cut_x_max, cut_y, cut_y_max);
        //SDL_SaveBMP(character, "test.jpg");
        //character_nb += 1;
	}
	
	return(img);
}

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
