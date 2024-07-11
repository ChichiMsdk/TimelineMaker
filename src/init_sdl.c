#include "app.h"
#include "init.h"
#include <utils/ttf.h>

Instance	g_app = {0};
int			g_winw = 1000;
int			g_winh = 800;

/**
 *- Init all the systems, add params to choose which one
 *- Sets all the variable for the g_app instance
 *- Sets the fonts
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
	g_app.years_width = 32;

	TM_ASSERT(TTF_Init() == 0);
	SDL_RWops *chunk = SDL_RWFromMem(Inconsolata_Regular_ttf, Inconsolata_Regular_ttf_len);
	TM_ASSERT(chunk);
	TTF_Font *ttf = TTF_OpenFontRW(chunk, SDL_TRUE, 48);
	TM_ASSERT(ttf);
	g_app.ttf = ttf;
	init_font(&g_app.myfont, r, g_app.ttf);
	TM_ASSERT(&g_app.myfont);
}
