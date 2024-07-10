#include "primitive.h"

void
draw_fill_rect(SDL_Renderer *r, SDL_Color c, SDL_Rect rect)
{
	YU_SetRenderDrawColor(r, c);
	SDL_RenderFillRect(r, &rect);
}

void 
draw_fill_circle(SDL_Renderer *r, int32_t cX, int32_t cY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

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
