#ifndef APP_H
#define APP_H

#include <stdbool.h>

#include <utils/logger.h>
#include <utils/asserts.h>

#include "render.h"
#include "events.h"
#include "font.h"

#define CLAMP(x, a, b) SDL_min(a, SDL_max(x, b))

typedef struct Instance
{
	SDL_Renderer	*r;
	SDL_Window		*w;
	SDL_Event		e;

	bool			run;
	Mouse_state		mouse;

	int				years_width;
	font			myfont;
	TTF_Font		*ttf;
}Instance;

extern Instance		g_app;
extern int			g_winw;
extern int			g_winh;

#endif
