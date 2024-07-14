#include "buttons.h"
#include "app.h"

extern Instance		g_app;

Mouse_state
get_mouse_state(void)
{
	int x, y;
	Mouse_state mouse = {0};
	uint32_t flags = SDL_GetMouseState(&x, &y);
	mouse.pos = vec2i(x, y);
	mouse.flags = flags;
	return mouse;
}

/* data struct to loop through all the buttons */
void
loop_gui(Button **buttons)
{

}

void
button_check_hover(Mouse_state mouse, Button *button)
{
	Vec2i m_pos = mouse.pos;
	uint32_t m_button = SDL_BUTTON(mouse.flags);

	int i = 0;
	/* checks if inside button */
	while (i < button->count)
	{
		if ((m_pos.x < button[i].rect.w + button[i].rect.x
				&& m_pos.x >= button[i].rect.x)
				&& (m_pos.y < button[i].rect.h + button[i].rect.y
				&& m_pos.y >= button[i].rect.y)) 
		{
			button[i].hovered = true;
			/* create array of cursor beforehand */
			/* SDL_SetCursor(g_inst.cursorclick); */
			break;
		}
		else
		{
			button[i].hovered = false;
			/* button[i].pressed = false; */
			/* SDL_SetCursor(g_inst.cursordefault); */
		}
		i++;
	}
}

/* note: make a function pointer callback for the button when pressed */
void
button_check_pressed(Mouse_state mouse, Button *button)
{
	Vec2i m_pos = mouse.pos;
	uint32_t m_button = SDL_BUTTON(mouse.flags);

	int i = 0;
	/* checks if inside button */
	while (i < button->count)
	{
		if ((m_pos.x < button[i].rect.w + button[i].rect.x
				&& m_pos.x >= button[i].rect.x)
				&& (m_pos.y < button[i].rect.h + button[i].rect.y
				&& m_pos.y >= button[i].rect.y)) 
		{
			/* create array of cursor beforehand */
			if (m_button == SDL_BUTTON_LEFT)
			{
				button[i].pressed = true;
			}
		}
		else
		{
			button[i].pressed = false;
		}
		i++;
	}
}

void
timeline_mouse_pressed(Mouse_state mouse)
{
	g_app.startPos = get_mouse_state();
	g_app.grab = true;
}

void
timeline_mouse_released(Mouse_state mouse)
{
	g_app.lastPos = get_mouse_state();
	g_app.grab = false;
}

void
button_check_released(Mouse_state mouse, Button *button)
{
	Vec2i m_pos = mouse.pos;
	uint32_t m_button = SDL_BUTTON(mouse.flags);
	/* checks if inside button */
	int i = 0;
	while (i < button->count)
	{
		if ((m_pos.x < button[i].rect.w + button[i].rect.x
				&& m_pos.x >= button[i].rect.x)
				&& (m_pos.y < button[i].rect.h + button[i].rect.y
				&& m_pos.y >= button[i].rect.y)) 
		{
			if (button[i].pressed)
			{
				{
				/* create array of cursor beforehand */
					button[i].released = true;
				}
			}
		}
		button[i].pressed = false;
		i++;
	}
}

void
drop_file(const char *fname)
{
	
}

void
dialog_callback(void *userdata, const char * const *filelist, int filter)
{
	if (!filelist)
	{
		TMWARN("Could retrieve file list");
		return ;
	}
	if (!*filelist)
		return ;

	int i = 0;
	while (filelist[i])
	{
		drop_file(filelist[i]);
		i++;
	}
}

