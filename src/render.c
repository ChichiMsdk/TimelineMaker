#include <utils/mycolors.h>
#include "app.h"
#include "primitive.h"

void
YU_SetRenderDrawColor(SDL_Renderer *r, SDL_Color c)
{
	SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
}

static inline void
clear_screen(SDL_Renderer *r, SDL_Color c)
{
	YU_SetRenderDrawColor(r, c);
	SDL_RenderClear(r);
}

void
render_frames(SDL_Renderer *r)
{
	SDL_Rect rect_mouse = {
		.x = g_app.mouse.pos.x,
		.y = 0,
		.w = 2,
		.h = g_winh
	};
	SDL_Rect rect_time = {
		.x = 0,
		.y = g_winh / 2,
		.w = g_winw,
		.h = 5
	};
	clear_screen(r, (SDL_Color){.r = 237, .g = 237, .b = 237, .a = 255});
	draw_fill_rect(r, (SDL_Color){.r = 221, .g = 221, .b = 221, .a = 255}, rect_mouse);
	draw_fill_rect(r, (SDL_Color){.r = 102, .g = 102, .b = 102, .a = 255}, rect_time);
	int i = 0;
	while (i < 10)
	{
		draw_fill_circle(r, i * g_winw / 10, rect_time.y + rect_time.h / 2, 8);
		i++;
	}

	SDL_RenderPresent(r);
}
