#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

//Initializing the SDL
void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

//Loading an image from a file
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

//Displaying an image
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

//Waiting for a key to be pressed
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

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    //Initialize the SDL
    init_sdl();

    //Load the image
    image_surface = load_image("my_image.jpg");
    //Display the image
    screen_surface = display_image(image_surface);

    //Wait for a key to be pressed
    wait_for_keypressed();

    unsigned width = image_surface->w;
    unsigned height = image_surface->h;

    //Grayscale
    for (unsigned y=0; y<height; y++)
    {
        for (unsigned x=0; x<width; x++)
        {
            //Get the pixel value
            Uint32 pixel = get_pixel(image_surface, x, y);
            //Get RGB values
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            //Get the weighted average of the RGB values
            Uint8 average = 0.3*r + 0.59*g + 0.11*b;
            //Update the RGB values
            r = average;
            g = average;
            b = average;
            //Get the new pixel value from the new RGB values
            pixel = SDL_MapRGB(image_surface->format, r, g, b);
            //Put the new pixel value on the surface
            put_pixel(image_surface, x, y, pixel);
        }
    }

    //Redraw the surfaces
    update_surface(screen_surface, image_surface);

    //Save image
    SDL_SaveBMP(image_surface, "grayscale.jpg");

    //Wait for a key to be pressed
    wait_for_keypressed();

    //BlacknWhite 25%
    for (unsigned y=0; y<height; y++)
    {
        for (unsigned x=0; x<width; x++)
        {
            //Get the pixel value
            Uint32 pixel = get_pixel(image_surface, x, y);
            //Get RGB values
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            //Get the weighted average of the RGB values
            Uint8 average = 0.3*r + 0.59*g + 0.11*b;

            //Update the RGB values
            //Pixel Blanc
            if (average > 191)
            {
                r = 255;
                g = 255;
                b = 255;
            }
            //Pixel Noir
            else
            {
                r = 0;
                g = 0;
                b = 0;
            }

            //Get the new pixel value from the new RGB values
            pixel = SDL_MapRGB(image_surface->format, r, g, b);
            //Put the new pixel value on the surface
            put_pixel(image_surface, x, y, pixel);
        }
    }

    //Redraw the surfaces
    update_surface(screen_surface, image_surface);

    //Save image
    SDL_SaveBMP(image_surface, "blacknwhite25.jpg");

    //Wait for a key to be pressed
    wait_for_keypressed();

    //Load the grayscale image
    image_surface = load_image("grayscale.jpg");

    //BlacknWhite 50%
    for (unsigned y=0; y<height; y++)
    {
        for (unsigned x=0; x<width; x++)
        {
            //Get the pixel value
            Uint32 pixel = get_pixel(image_surface, x, y);
            //Get RGB values
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            //Get the weighted average of the RGB values
            Uint8 average = 0.3*r + 0.59*g + 0.11*b;

            //Update the RGB values
            //Pixel Blanc
            if (average > 127)
            {
                r = 255;
                g = 255;
                b = 255;
            }
            //Pixel Noir
            else
            {
                r = 0;
                g = 0;
                b = 0;
            }

            //Get the new pixel value from the new RGB values
            pixel = SDL_MapRGB(image_surface->format, r, g, b);
            //Put the new pixel value on the surface
            put_pixel(image_surface, x, y, pixel);
        }
    }

    //Redraw the surfaces
    update_surface(screen_surface, image_surface);

    //Save image
    SDL_SaveBMP(image_surface, "blacknwhite50.jpg");

    //Wait for a key to be pressed
    wait_for_keypressed();

    //Load the grayscale image
    image_surface = load_image("grayscale.jpg");

    //BlacknWhite 75%
    for (unsigned y=0; y<height; y++)
    {
        for (unsigned x=0; x<width; x++)
        {
            //Get the pixel value
            Uint32 pixel = get_pixel(image_surface, x, y);
            //Get RGB values
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            //Get the weighted average of the RGB values
            Uint8 average = 0.3*r + 0.59*g + 0.11*b;

            //Update the RGB values
            //Pixel Blanc
            if (average > 63)
            {
                r = 255;
                g = 255;
                b = 255;
            }
            //Pixel Noir
            else
            {
                r = 0;
                g = 0;
                b = 0;
            }

            //Get the new pixel value from the new RGB values
            pixel = SDL_MapRGB(image_surface->format, r, g, b);
            //Put the new pixel value on the surface
            put_pixel(image_surface, x, y, pixel);
        }
    }

    //Redraw the surfaces
    update_surface(screen_surface, image_surface);

    //Save image
    SDL_SaveBMP(image_surface, "blacknwhite75.jpg");

    //Wait for a key to be pressed
    wait_for_keypressed();

    //Free the surfaces
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
