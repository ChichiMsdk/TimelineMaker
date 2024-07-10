#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "render.h"

void	draw_fill_rect(SDL_Renderer *r, SDL_Color c, SDL_Rect rect);
void	draw_fill_circle(SDL_Renderer *r, int32_t cX, int32_t cY, int32_t radius);
void	draw_circle(SDL_Renderer *r, int32_t cX, int32_t cY, int32_t radius);

#endif
