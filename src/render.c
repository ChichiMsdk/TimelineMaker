#include <utils/mycolors.h>
#include "app.h"
#include "primitive.h"

#define TM_WHITE (SDL_Color){.r = 237, .g = 237, .b = 237, .a = 255}
#define TM_LIGHTGRAY (SDL_Color){.r = 221, .g = 221, .b = 221, .a = 255}
#define TM_GRAY (SDL_Color){.r = 102, .g = 102, .b = 102, .a = 255}

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

#define MAX_CIRCLES 24
#define MIN_CIRCLES 8

static inline void
render_circles(SDL_Renderer *r, SDL_Rect r_time)
{
	int i = 0;
	TM_ASSERT(g_app.years_width > 0);
	float nb_circles = (float)g_winw / g_app.years_width;
	nb_circles = SDL_fmodf(nb_circles, 16);
	if (nb_circles < MIN_CIRCLES)
	{
		nb_circles += MIN_CIRCLES;
	}
	nb_circles = SDL_roundf(nb_circles);
	static int tmp;
	if (tmp != nb_circles)
	{
		TMINFO("circles: %f\tyears: %d\n", nb_circles, g_app.years_width);
		tmp = nb_circles;
	}

	int offset = g_winw / nb_circles;
	int centerX =  offset;
	int centerY = r_time.y + (r_time.h / 2);
	int radius = 8;
	SDL_Rect rect = {.x = centerX, .y = 0, .w = 2, .h = g_winh};
	while (i < nb_circles)
	{
		rect.x = i * centerX;
		draw_rect(r, TM_LIGHTGRAY, rect, FILLED);
		draw_fill_circle(r, i * centerX, centerY, radius, TM_GRAY);
		i++;
	}
}

static inline void
render_mouse_fake_cursor(SDL_Renderer *r, SDL_Color c)
{
	float scale = 2.0f;
	float thick = 2.0f;
	float dis = 4.0f;
	SDL_Point p_mouse = { 
		.x = g_app.mouse.pos.x,
		.y = g_app.mouse.pos.y - scale * dis,
	};
	draw_fill_cross(r, c, p_mouse, scale, thick, dis);
}

static inline void
render_timeline(SDL_Renderer *r)
{
	SDL_Rect r_time = { .x = 0, .y = g_winh / 2, .w = g_winw, .h = 5 };
	draw_rect(r, TM_GRAY, r_time, FILLED);
	render_circles(r, r_time);
}

void
render_frames(SDL_Renderer *r)
{
	SDL_Rect r_mouse = { .x = g_app.mouse.pos.x, .y = 0, .w = 2, .h = g_winh };
	clear_screen(r, TM_WHITE);
	draw_rect(r, TM_LIGHTGRAY, r_mouse, FILLED);
	render_timeline(r);
	SDL_Point p = {.x = g_winw - 400, .y = 100};
	g_app.myfont.color = YU_RED;
	font_write(&g_app.myfont, r, p, "Salut");
	render_mouse_fake_cursor(r, YU_ORANGE);
	SDL_RenderPresent(r);
}
