//this function initializes SDL video subsystem
void init(void) {
	SDL_Init(SDL_INIT_VIDEO);
}

SDL_Renderer* createRenderer(SDL_Window *win) {
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);

	if(ren == NULL) {
		printf("ERROR: Renderer cannot be initialized.\n");
		exit(EXIT_FAILURE);
	}

	return ren;
}

SDL_Window* createWindow(void) {
	SDL_Window *win = SDL_CreateWindow("Line Drawing",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIDTH,
			HEIGHT,
			0);

	if(win == NULL) {
		printf("ERROR: Window cannot be initialized.\n");
		exit(EXIT_FAILURE);
	}

	return win;
}

void destroyWindow(SDL_Window **win) {
	SDL_DestroyWindow(*win);
}

void destroyRenderer(SDL_Renderer **ren) {
	SDL_DestroyRenderer(*ren);
}

//this function deallocates memory allocated at the beginning of the program
void cleanup(SDL_Window **win, SDL_Renderer **ren) {
	destroyWindow(win);
	destroyRenderer(ren);
	SDL_Quit();
}
