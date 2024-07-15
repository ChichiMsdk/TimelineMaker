#include "app.h"
#include <stdio.h>
void
key_up(SDL_Keycode key)
{
/* record_pressed(key); */
	switch (key)
	{
		case SDLK_ESCAPE:
			g_app.run = false;
			break;
		case SDLK_BACKSPACE:
			break;
		case SDLK_KP_PLUS:
			break;
		case SDLK_KP_MINUS:
			break;
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_y:
			break;
		case SDLK_DOWN:
			break;
		case SDLK_UP:
			break;
	}
}

void
move_win(void)
{
	int x = 0, y = 0;
	int xw, yw;
	Mouse_state m = get_mouse_state();
	if (m.flags == SDL_BUTTON_LMASK)
	{
		SDL_GetMouseState(&x, &y);
		SDL_GetWindowPosition(g_app.w, &xw, &yw);
		TMINFO("Winx: %d\tWiny: %d", xw, yw);
		TMWARN("Mx: %d\tMy: %d", x, y);
		SDL_SetWindowPosition(g_app.w, xw + x, yw + y);
	}
}

void
key_down(SDL_Keycode key)
{
/* record_pressed(key); */
	switch (key)
	{
		case SDLK_ESCAPE:
			g_app.run = false;
			break;
		case SDLK_BACKSPACE:
			break;
		case SDLK_KP_PLUS:
			break;
		case SDLK_KP_MINUS:
			break;
		case SDLK_LEFT:
			g_app.s_years--;
			if (g_app.s_years < 0)
				g_app.s_years = 0;
			break;
		case SDLK_RIGHT:
			g_app.s_years++;
			if (g_app.s_years > 999)
				g_app.s_years = 999;
			break;
		case SDLK_y:
			break;
		case SDLK_LSHIFT:
			break;
		case SDLK_DOWN:
			g_app.index_font--;
			if (g_app.index_font < 0)
				g_app.index_font = 4;
			g_app.current = g_app.myfont[g_app.index_font];
			printf("g_app.index_font: %d\n", g_app.index_font);
			break;
		case SDLK_UP:
			g_app.index_font++;
			if (g_app.index_font >= 5)
				g_app.index_font = 0;
			g_app.current = g_app.myfont[g_app.index_font];
			printf("g_app.index_font: %d\n", g_app.index_font);
			break;
	}
}

void
mouse_wheel(SDL_MouseWheelEvent wheel)
{
	if (wheel.y > 0) 
	{
		g_app.w_years++;
		if (g_app.w_years > 100)
			g_app.w_years = 100;
	} 
	else if (wheel.y < 0)
	{
		g_app.w_years--;
		if (g_app.w_years <= 0)
			g_app.w_years = 1;
	}
}

void
Events(SDL_Event e)
{
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
				g_app.run = false;
			case SDL_KEYUP:
				key_up(e.key.keysym.sym);
				break;
			case SDL_KEYDOWN:
				key_down(e.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				if (g_app.grab)
				{
					/* TMINFO("move and grab"); */
					g_app.lastPos = get_mouse_state();
					g_app.mouse = get_mouse_state();
				}
				g_app.lastPos = get_mouse_state();
				g_app.mouse = get_mouse_state();
				break;
			case SDL_MOUSEBUTTONUP:
				timeline_mouse_released(get_mouse_state());
				break;
			case SDL_MOUSEBUTTONDOWN:
				timeline_mouse_pressed(get_mouse_state());
				break;
			case SDL_MOUSEWHEEL:
				mouse_wheel(e.wheel);
				break;
		}
	}
}
#if 0
void
drop_event(char *fname)
{
	/* printf("len_file_name: %llu\n", strlen(fname)); */
	AudioData audio = {0};
	if (load_new_audio_to_play(fname, 0, &audio) < 0)
	{
		/* replays the previous one */
		change_audio_to_play(g_playlist.current, 0);
		return ;
	}
	g_playlist.music[g_playlist.current] = audio;
	/* SDL_RaiseWindow(g_inst.window); */
	/* SDL_SetAudioStreamGetCallback(g_play_sfx.stream, put_callback, &g_play_sfx); */
}
#endif
