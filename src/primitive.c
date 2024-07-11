#include "primitive.h"
#include <utils/logger.h>
#include <utils/asserts.h>

void
draw_frect(SDL_Renderer *r, SDL_Color c, SDL_FRect rect, int fill)
{
	TM_ASSERT((fill == 0) || (fill == 1));
	if (fill == EMPTY)
	{
		YU_SetRenderDrawColor(r, c);
		SDL_RenderDrawRectF(r, &rect);
	}
	else if (fill == FILLED)
	{
		YU_SetRenderDrawColor(r, c);
		SDL_RenderFillRectF(r, &rect);
	}
}

void
draw_rect(SDL_Renderer *r, SDL_Color c, SDL_Rect rect, int fill)
{
	TM_ASSERT((fill == 0) || (fill == 1));
	if (fill == EMPTY)
	{
		YU_SetRenderDrawColor(r, c);
		SDL_RenderDrawRect(r, &rect);
	}
	else if (fill == FILLED)
	{
		YU_SetRenderDrawColor(r, c);
		SDL_RenderFillRect(r, &rect);
	}
}

void
draw_fill_rect(SDL_Renderer *r, SDL_Color c, SDL_Rect rect)
{
	YU_SetRenderDrawColor(r, c);
	SDL_RenderFillRect(r, &rect);
}

void
draw_fill_cross(SDL_Renderer *r, SDL_Color c, SDL_Point p, float s, float t, float d)
{
	TM_ASSERT(t > 0);
	TM_ASSERT(s > 0);

	float w_vert = 1.0f * t;
	float h_vert = 1.0f * d * s;

	float w_hori = 1.0f * d * s;
	float h_hori = 1.0f * t;

	SDL_FRect v = {
		.x = p.x - (w_vert / 2),
		.y = p.y - (h_vert / 2),
		.w = w_vert,
		.h = h_vert,
	};

	SDL_FRect h = {
		.x = p.x - (w_hori / 2),
		.y = p.y - (h_hori / 2),
		.w = w_hori,
		.h = h_hori,
	};

	draw_frect(r, c, v, FILLED);
	draw_frect(r, c, h, FILLED);
}

void 
draw_fill_circle(SDL_Renderer *r, int32_t cX, int32_t cY, int32_t radius, SDL_Color c)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

	YU_SetRenderDrawColor(r, c);
    while (x >= y)
    {
        // Draw horizontal lines to fill the circle
        SDL_RenderDrawLine(r, cX - x, cY - y, cX + x, cY - y);
        SDL_RenderDrawLine(r, cX - x, cY + y, cX + x, cY + y);
        SDL_RenderDrawLine(r, cX - y, cY - x, cX + y, cY - x);
        SDL_RenderDrawLine(r, cX - y, cY + x, cX + y, cY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void 
draw_circle(SDL_Renderer *r, int32_t cX, int32_t cY, int32_t radius)
{
	const int32_t diameter = (radius * 2);
	
	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);
	
	while (x >= y)
	{
	   //  Each of the following renders an octant of the circle
	   SDL_RenderDrawPoint(r, cX + x, cY - y);
	   SDL_RenderDrawPoint(r, cX + x, cY + y);
	   SDL_RenderDrawPoint(r, cX - x, cY - y);
	   SDL_RenderDrawPoint(r, cX - x, cY + y);
	   SDL_RenderDrawPoint(r, cX + y, cY - x);
	   SDL_RenderDrawPoint(r, cX + y, cY + x);
	   SDL_RenderDrawPoint(r, cX - y, cY - x);
	   SDL_RenderDrawPoint(r, cX - y, cY + x);
	
	   if (error <= 0)
	   {
	      ++y;
	      error += ty;
	      ty += 2;
	   }
	
	   if (error > 0)
	   {
	      --x;
	      tx += 2;
	      error += (tx - diameter);
	   }
	}
}
