#include "app.h"
#include "init.h"

Instance	g_app = {0};
int			g_winw = 1000;
int			g_winh = 800;

/**
 *- Init all the systems, add params to choose which one
 *- Sets all the variable for the g_app instance
 */

void
init_systems(void)
{
	int x = SDL_WINDOWPOS_UNDEFINED;
	int y = SDL_WINDOWPOS_UNDEFINED;
	SDL_Window *w;
	SDL_Renderer *r;

	TM_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0);

	w = SDL_CreateWindow("Timeline Maker", x, y, g_winw, g_winh, 0);
	TM_ASSERT(w);

	r = SDL_CreateRenderer(w, -1, 0);
	TM_ASSERT(r);

	SDL_Event e;

	g_app.r = r;
	g_app.w = w;
	g_app.e = e;
	g_app.run = true;
}
