#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct {
	SDL_Event event;
	SDL_Window *native;
	char *title;
	int width;
	int height;
} window = {0};
SDL_Renderer *renderer = NULL;
bool is_running = false;

static int init_platform(void)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		return -1;

	window.width = 900;
	window.height = 600;
	window.title = malloc(7);
	if (!window.title)
		return -2;

	strncpy(window.title, "DeTile", 7);
	window.native = SDL_CreateWindow(window.title, window.width,
					 window.height, 0);
	if (!window.native)
		return -3;

	renderer = SDL_CreateRenderer(window.native, NULL);
	if (!renderer)
		return -4;

	is_running = true;
	return 0;
}

static void mainloop(void)
{
	while (is_running) {
		while (SDL_PollEvent(&window.event)) {
			if (window.event.type == SDL_EVENT_QUIT)
				is_running = false;
		}

		const bool *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
			is_running = false;

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
}

int main(void)
{
	int ret = init_platform();
	if (ret < 0)
		goto err_out;

	mainloop();

err_out:
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window.title)
		free(window.title);
	if (window.native)
		SDL_DestroyWindow(window.native);
	SDL_Quit();

	return ret;
}
