#ifndef RENDER_H
#define RENDER_H

#include <SDL_render.h>

void	render_frames(SDL_Renderer *r);
void	YU_SetRenderDrawColor(SDL_Renderer *r, SDL_Color c);
void	draw_vert_mouseline(SDL_Renderer *r);
void	draw_fill_rect(SDL_Renderer *r, SDL_Color c, SDL_Rect rect);

#endif //RENDER_H
