void drawLine(SDL_Renderer **renderer, int A[2], int B[2]) {
	SDL_Point point;

	int dx = B[0] - A[0];
	int dy = B[1] - A[1];
	int steps, k;

	double xIncrement;
	double yIncrement;
	double x = A[0];
	double y = A[1];

	if(abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);

	xIncrement = dx / (float) steps;
	yIncrement = dy / (float) steps;

	for(k = 0; k < steps; ++k) {
		x += xIncrement;
		y += yIncrement;
		point.x = x;
		point.y = y;
		SDL_RenderDrawPoint(*renderer, point.x, point.y);
	}
}
