#ifndef APP_H
#define APP_H

#include <stdbool.h>

#include <utils/logger.h>
#include <utils/asserts.h>

#include "render.h"
#include "events.h"

typedef struct Instance
{
	SDL_Renderer	*r;
	SDL_Window		*w;
	SDL_Event		e;

	bool			run;
	Mouse_state		mouse;
}Instance;

extern Instance		g_app;
extern int			g_winw;
extern int			g_winh;

#endif
