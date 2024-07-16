#include "app.h"
#include "init.h"
#include "ttf.h"

Instance	g_app = {0};
int			g_winw = 1000;
int			g_winh = 800;


raw_font myraw[5];
#include <stdio.h>

static void
load_fonts(void);

static SDL_HitTestResult 
my_hitTest(SDL_Window *win, const SDL_Point *area, void *data);

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
	g_app.grab = false;
	g_app.grab2 = false;
	g_app.move = false;
	g_app.w_years = 5;
	g_app.test = 0;

	TM_ASSERT(TTF_Init() == 0);
	load_fonts();
	TM_ASSERT(SDL_SetWindowHitTest(g_app.w, my_hitTest, NULL) == 0);
}

// NOTE: Separate thread ?
static SDL_HitTestResult 
my_hitTest(SDL_Window *win, const SDL_Point *area, void *data)
{
	int lenkey;
	const Uint8 *keyboard = SDL_GetKeyboardState(&lenkey);
	if (keyboard[SDL_GetScancodeFromKey(SDLK_LSHIFT)])
	{
		return SDL_HITTEST_DRAGGABLE;
	}
	return SDL_HITTEST_NORMAL;
}

static void
load_fonts(void)
{
	int i = 0;
	myraw[0].data = __Montserrat_Regular_ttf; myraw[0].len = __Montserrat_Regular_ttf_len;
	myraw[1].data = __Inter_Regular_ttf; myraw[1].len = __Inter_Regular_ttf_len;
	myraw[2].data = __Nunito_Regular_ttf; myraw[2].len = __Nunito_Regular_ttf_len;
	myraw[3].data = __Poppins_Regular_ttf; myraw[3].len = __Poppins_Regular_ttf_len;
	myraw[4].data = Inconsolata_Regular_ttf; myraw[4].len = Inconsolata_Regular_ttf_len;

	// HACK: maybe dont do that ?
	while (i < sizeof(myraw) / sizeof(*myraw))
	{
		SDL_RWops *chunk = SDL_RWFromMem(myraw[i].data, myraw[i].len);
		TM_ASSERT(chunk);
		TTF_Font *ttf = TTF_OpenFontRW(chunk, SDL_TRUE, 32);
		TM_ASSERT(ttf);
		g_app.ttf = ttf;
		init_font(&g_app.myfont[i], g_app.r, g_app.ttf);
		TM_ASSERT(&g_app.myfont[i]);
		TTF_CloseFont(g_app.ttf);
		i++;
	}
	g_app.current = g_app.myfont[0]; 
	g_app.index_font = 0;
}
