#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "render.h"

typedef enum FILL
{
	EMPTY = 0,
	FILLED = 1
}FILL;

void	draw_fill_circle(SDL_Renderer *r, int32_t cX, int32_t cY, int32_t ra, SDL_Color c);
void	draw_circle(SDL_Renderer *r, int32_t cX, int32_t cY, int32_t radius);

void	draw_rect(SDL_Renderer *r, SDL_Color c, SDL_Rect rect, int fill);
void	draw_fill_rect(SDL_Renderer *r, SDL_Color c, SDL_Rect rect);

void	draw_fill_cross(SDL_Renderer *r, SDL_Color c, SDL_Point p,float s, float t, float d);

#endif
