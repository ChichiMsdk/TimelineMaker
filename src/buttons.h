#ifndef BUTTONS_H
#define BUTTONS_H

#include <SDL_stdinc.h>
#include <SDL_mouse.h>

#include <stdbool.h>

#include <utils/vector.h>

typedef struct Mouse_state
{
	Vec2i				pos;
	uint32_t			flags;
}Mouse_state;

typedef struct Button
{
	SDL_FRect			rect;
	SDL_Color			color;
	SDL_Color			color_pressed;
	// SDL_Texture			*text[2];
	bool				pressed, released, hovered;
	void				*(*fn)(void *);
	int					count;
}Button;

enum
{
	B_UP = 0,
	B_DOWN = 1
};

Mouse_state		get_mouse_state(void);

#endif //BUTTONS_H
