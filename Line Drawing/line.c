#include<stdio.h>
#include<stdlib.h>

#include "SDL.h"
#include "macros.h"
#include "memory.h"
#include "graphics.h"
#include "process.h"

//create a line object defined by two end-points, A and B
typedef struct Line {
	int A[2];
	int B[2];
} Line;

int main(int argc, char *argv[]) {
	//initialize the proper SDL subsystem to be used
	init();

	SDL_Window *window = createWindow(); //create a window to present the rendered image
	SDL_Renderer *renderer = createRenderer(window); //this is where lines will be drawn
	SDL_Event event; //used for reading events in the event queue
	Line point; //this line object will be manipulated by adjusting its end-point coordinates, and rendered into the renderer

	int xPixels = (WIDTH / UNIT); //defines the number of horizontal pixels to be added to/subtracted from the current x-coordinate of a point
	int yPixels = (WIDTH / UNIT); //defines the number of vertical pixels to be added to/subtracted from the current y-coordinate of a point

	//mark the center point
	int center[2] = {WIDTH / 2, HEIGHT / 2};

	//mark the beginning of the animation
	BEGIN:

	//set the background color to {199, 0, 57, 255}
	SDL_SetRenderDrawColor(renderer, 199, 0, 57, 255);
	SDL_RenderClear(renderer);

	//initially set the drawing color to white
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//keep repeating the process below
	while(1) {
		//set the initial position of the line to vertical, centered
		point.A[0] = center[0];
		point.A[1] = xPixels;

		point.B[0] = center[0];
		point.B[1] = center[1];

		//FOR QUADRANT 1:
		while(point.A[1] + yPixels <= point.B[1]) {
			//check if user wants to restart the animation from the beginning or terminate the program
			switch(userRequest(&event)) {
				case RESTART:
					goto BEGIN;
				case TERMINATE:
					goto END;
			}

			//Change the position of the line accordingly
			point.A[1] += yPixels;
			point.B[0] += xPixels;

			//display the line in its updated position
			drawLine(&renderer, point.A, point.B);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
		}

		//FOR QUADRANT 4:
		while(point.B[0] - xPixels > center[0]) {
			//check if user wants to restart the animation from the beginning or terminate the program
			switch(userRequest(&event)) {
				case RESTART:
					goto BEGIN;
				case TERMINATE:
					goto END;
			}

			//Change the position of the line accordingly
			point.B[0] -= xPixels;
			point.A[1] += yPixels;

			//display the line in its updated position
			drawLine(&renderer, point.A, point.B);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
		}

		//FOR QUADRANT 3:
		while(point.A[1] - yPixels > center[1]) {
			//check if user wants to restart the animation from the beginning or terminate the program
			switch(userRequest(&event)) {
				case RESTART:
					goto BEGIN;
				case TERMINATE:
					goto END;
			}

			//Change the position of the line accordingly
			point.B[0] -= xPixels;
			point.A[1] -= yPixels;

			//display the line in its updated position
			drawLine(&renderer, point.A, point.B);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
		}

		//FOR QUADRANT 2:
		while(point.B[0] < center[0]) {
			//check if user wants to restart the animation from the beginning or terminate the program
			switch(userRequest(&event)) {
				case RESTART:
					goto BEGIN;
				case TERMINATE:
					goto END;
			}

			//Change the position of the line accordingly
			point.B[0] += xPixels;
			point.A[1] -= yPixels;

			//display the line in its updated position
			drawLine(&renderer, point.A, point.B);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
		}

		//set the drawing color to a randomly generated color
		SDL_SetRenderDrawColor(renderer, gen(255), gen(255), gen(255), 255);
	}

	//mark the end of the animation
	END:

	//properly deallocate memory and exit the program
	cleanup(&window, &renderer);
	return(EXIT_SUCCESS);
}
