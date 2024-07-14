#include <utils/mycolors.h>
#include "app.h"
#include "primitive.h"
#include "smooth.h"

#include <stdio.h>
#include <string.h>

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
#define MIN_CIRCLES 3

#define MAX_SPACE 50
#define MIN_SPACE 25

static inline void
render_circles(SDL_Renderer *r, SDL_Rect r_time)
{
	static float current[1000];
	static float previous[1000];
	static float current2[1000];
	static float previous2[1000];
	char txt[20];

	float radius = 8;
	static int offset;
	static size_t accumulation;
	static int tmp = 0;

	if (g_app.grab)
	{
		int temp = g_app.startPos.pos.x - g_app.lastPos.pos.x;
		/* offset = fmod(offset, g_winw); */
		offset += temp;
		g_app.startPos = get_mouse_state();
	}
	int nb_circles = g_app.w_years;
	if (offset > g_winw)
	{
		tmp = offset;
		offset = 0;
		TMINFO("offset: %d", offset);
		g_app.s_years+= nb_circles;
	}
	else if (offset < 0)
	{
		tmp = offset;
		offset = g_winw;
		TMINFO("offset: %d", offset);
		g_app.s_years-= nb_circles;
	}

	float centerY = r_time.y + (r_time.h / 2.0f);

	int centerX;
	SDL_Rect rect = {.x = centerX, .y = 0, .w = 2, .h = g_winh};
	
	int i = 0 + g_app.test;
	/* int i = 0; */
	while (i < g_app.w_years * 2 )
	{
		centerX = g_winw / nb_circles;
		/* rect.x = i * (centerX + offset); */
		rect.x = ((i * centerX) - (offset - tmp % g_winw));
		current[i] = rect.x;
		/* current[i] = interpolate(previous[i], rect.x, 0.1f); */
		/* rect.x = current[i]; */
		draw_rect(r, TM_LIGHTGRAY, rect, FILLED);
		draw_fill_circle(r, rect.x, centerY, radius, TM_GRAY);
		i++;
	}
	for (int j = 0; j < nb_circles * 2; j++)
	{
		sprintf(txt, "%d", g_app.s_years + j);
		font_write(&g_app.current, r, (SDL_Point){.x = current[j], .y = (centerY + 20)}, txt, YU_RED);
	}
	memcpy(previous, current, sizeof(previous));
	memcpy(previous2, current2, sizeof(previous));
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

extern int array[4000];

static inline void
render_rectangle(SDL_Renderer *r)
{
	float nb = g_app.w_years;
	static float offset;
	static int acc;
	SDL_Rect rect = {.x = 0, .y = g_winh/2, .w = g_winw / nb, .h = 30};

	static int j = 0;
	if (g_app.grab)
	{
		int tmp = g_app.startPos.pos.x - g_app.lastPos.pos.x;
		offset = fmod(offset, g_winw);
		offset += tmp;

        /*
		 * acc += tmp;
		 * j += tmp;
		 * if (j < 0)
		 * 	j = 0;
		 * if (j >= 4000)
		 * 	j = 3999;
         */
			 
		g_app.startPos = get_mouse_state();
		/* TMINFO("offset: %f\ttmp: %d", offset, tmp); */
	}
	char txt[20];
	int k = 0;
	/* int i = g_winw / nb * -1; */
	int i = 0;
	/* while (i < nb * 2 ) */
	while (i < nb)
	{
		rect.x = (i * rect.w) - offset;
		g_app.current.color = YU_BLACK;
		if (i % 2)
			YU_SetRenderDrawColor(r, YU_RED);
		else
			YU_SetRenderDrawColor(r, YU_OLIVE);
		SDL_RenderFillRect(r, &rect);
		if (i > 0)
			snprintf(txt, 20, "%d", array[j] + i);
		else
			snprintf(txt, 20, "%d", array[j]);
		font_write(&g_app.current, r, (SDL_Point){.x = rect.x, .y = g_winh / 2 - 5}, txt, YU_BLACK);
		i++;
	}
}

void
render_frames(SDL_Renderer *r)
{
	SDL_Rect r_mouse = { .x = g_app.mouse.pos.x, .y = 0, .w = 2, .h = g_winh };
	clear_screen(r, TM_WHITE);
	draw_rect(r, TM_LIGHTGRAY, r_mouse, FILLED);
	render_timeline(r);
	/* render_rectangle(r); */
	font_write(&g_app.current, r, (SDL_Point){.x = g_winw - 400, .y = 100}, "Salut", YU_RED);
	render_mouse_fake_cursor(r, YU_ORANGE);
	SDL_RenderPresent(r);
}
