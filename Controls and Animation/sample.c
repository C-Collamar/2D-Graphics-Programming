/*My very first graphics programming code
 *My first program using APIs
 *I used SDL 2.0.4 at the time of this creation (09/21/16)
 */

/*
 *  This program makes use of rendering
 * objects to the screen frame by frame;
 * wihch is basically animation
 */

/*
 * CONTROLS:
 * 	Up Arrow key - moves object up
 * 	Down Arrow key - moves object down
 * 	Left Arrow key - moves object to the left
 * 	Right Arrow key - moves object to the right
 * 	Enter key - enlarges the object
 * 	Backspace key - reduces object size
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include"SDL.h"

const unsigned int WIDTH = 640;
const unsigned int HEIGHT = 480;


typedef struct object {
	unsigned int size; //size of object
	int x; //x-coordinate of object
	int y; //y-coordinate of object
} Object;

void init(SDL_Window **window, SDL_Renderer **renderer) {

	SDL_Init(SDL_INIT_VIDEO);

	*window = SDL_CreateWindow("Motion Rendering",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIDTH,
			HEIGHT,
			0);

	if(*window == NULL) {
		printf("ERROR; Window cannot be initialized.\n");
		exit(EXIT_FAILURE);
	}

	*renderer = SDL_CreateRenderer(*window, -1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);

	if(*renderer == NULL) {
		printf("ERROR: Renderer could not be initialized.\n");
		exit(EXIT_FAILURE);
	}

}
void destroy(SDL_Window **window, SDL_Renderer **renderer) {

	//destroy objects
	SDL_DestroyWindow(*window);
	SDL_DestroyRenderer(*renderer);

}
int processEvents(SDL_Event *event, Object *object) {

	while(SDL_PollEvent(event))
	{

		switch(event->type)
		{
			case SDL_QUIT:
				return 1;
			case SDL_WINDOWEVENT_CLOSE:
				return 1;

			case SDL_KEYDOWN:
				switch(event->key.keysym.sym)
				{
					case SDLK_ESCAPE:
					case SDL_QUIT:
						return 1;
					case SDLK_UP:
						object->y -= 30;
						break;
					case SDLK_DOWN:
						object->y += 30;
						break;
					case SDLK_LEFT:
						object->x -= 30;
						break;
					case SDLK_RIGHT:
						object->x += 30;
						break;
					case SDLK_RETURN:
						object->size += 10;
						object->x -= 5;
						object->y -= 5;
						break;
					case SDLK_BACKSPACE:
						object->size -= 10;
						object->x += 5;
						object->y += 5;
						break;
				}

				printf("Object location: [%i, %i]\tsize = %i\n", object->x, object->y, object->size);
				break;
		}

	}

	return 0;

}
void renderOnScreen(SDL_Window **window, SDL_Renderer **renderer, const Object *object) {

	//set render color to blue
	SDL_SetRenderDrawColor(*renderer, 0, 0, 255, 255);
	//colors the active renderer to blue
	SDL_RenderClear(*renderer);
	//sets render color to white
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);

	//Declare & initialize rect. object
	SDL_Rect rect = {object->x, object->y, object->size, object->size};

	//fill to the current rendering target
	SDL_RenderFillRect(*renderer, &rect);

	//present the drawing on the renderer to the screen
	SDL_RenderPresent(*renderer);

	//to avoid CPU overheating
	SDL_Delay(10);

}

int main(int argc, char *argv[]) {

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;

	Object object = {200, WIDTH/2 - object.size / 2, HEIGHT/2 - object.size / 2};
	int done = 0;

	//initialize all variables needed
	init(&window, &renderer);

	while(!done) {
		done = processEvents(&event, &object);
		renderOnScreen(&window, &renderer, &object);
	}

	destroy(&window, &renderer);

	//clean-up and quit
	SDL_Quit();

	return EXIT_SUCCESS;

}
