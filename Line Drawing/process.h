#include<stdlib.h>
#include<time.h>

/* DESCRIPTION: This function generates an integer ranging from 0 to n
 * PARAMETER:
 *    - n: specifies the range of number to be generated
 * RETURN VALUE:  Returns an integer value from 0 to n
 */
int gen(int n) {

	srand((unsigned) time(0));

	int limit;
	int r;

	limit = RAND_MAX - (RAND_MAX - n);

	while((r = rand()) >= limit);

	return r % n;

}

/* DESCRIPTION: This function checks on whether the user requests/interrupts during the line-rendering process
 * PARAMETER:
 *    - event: an event queue/list of pending events such as clicking or typing
 * RETURN VALUE:  Returns RESTART if user wants to go back from the start of the animation by clicking on the active window
 *                Returns TERMINATE if user wants to quit the animation either by typing the ESC key or clicking the close button
 *                Returns 0 if there is no pending event/user did not click or type anything
 */
int userRequest(SDL_Event *event) {
	if(SDL_PollEvent(event)) {
		switch(event->type) {
			case SDL_MOUSEBUTTONDOWN:
				return RESTART;
			break;

			case SDL_QUIT:
				return TERMINATE;
			case SDL_KEYDOWN:
				if(event->key.keysym.sym == SDLK_ESCAPE)
					return TERMINATE;
		}
	}

	return 0;
}
