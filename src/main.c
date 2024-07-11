#define SDL_MAIN_HANDLED 
#include <SDL_main.h>
#include <SDL_timer.h>

#include "init.h"
#include "app.h"

int
main(void)
{
	init_systems();
	while (g_app.run)
	{
		Events(g_app.e);
		render_frames(g_app.r);
		SDL_Delay(16);
		SDL_min(2, 1);
	}
	return 0;
}
