#define SDL_MAIN_HANDLED 
#include <SDL_main.h>

#if 1
#include <SDL_timer.h>

#include "init.h"
#include "app.h"
#include "camera.h"

extern int	array[4000];
int			array[4000];

// note: add timer to all "animation" timings
int
main(void)
{
	init_systems();
	int j = -2000;
	for (int i = 0; i < 4000; i++)
		array[i++] = j++;
	while (g_app.run)
	{
		Events(g_app.e);

		render_frames(g_app.r);

		SDL_Delay(16);
	}
	return 0;
}

#endif

#if 0
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_opengl.h>
	#include <stdbool.h>
	
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int RECT_HEIGHT = 100;
	const float RECT_SPEED = 0.5f; // Speed of the rectangle movement
	bool grab = false;
	
	bool init(SDL_Window **window, SDL_GLContext *context) {
	    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	        return false;
	    }
	
	    *window = SDL_CreateWindow("Moving Rectangle",
	                               SDL_WINDOWPOS_CENTERED,
	                               SDL_WINDOWPOS_CENTERED,
	                               WINDOW_WIDTH, WINDOW_HEIGHT,
	                               SDL_WINDOW_OPENGL);
	
	    if (!*window) {
	        SDL_Log("Failed to create window: %s", SDL_GetError());
	        SDL_Quit();
	        return false;
	    }
	    *context = SDL_GL_CreateContext(*window);
	    if (!*context) {
	        SDL_Log("Failed to create OpenGL context: %s", SDL_GetError());
	        SDL_DestroyWindow(*window);
	        SDL_Quit();
	        return false;
	    }
	
	    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	
	    return true;
	}
	void render(float x) {
	    glClear(GL_COLOR_BUFFER_BIT);
	
	    glBegin(GL_QUADS);
	
	    for (int i = 0; i < WINDOW_WIDTH; i += 50) {
	        if ((i / 50) % 2 == 0) {
	            glColor3f(1.0f, 0.0f, 0.0f); // Red color
	        } else {
	            glColor3f(0.0f, 0.0f, 1.0f); // Blue color
	        }
	
	        float rectX = fmod(x + i, WINDOW_WIDTH);
	        glVertex2f(rectX, WINDOW_HEIGHT / 2.0f - RECT_HEIGHT / 2.0f);
	        glVertex2f(rectX + 50, WINDOW_HEIGHT / 2.0f - RECT_HEIGHT / 2.0f);
	        glVertex2f(rectX + 50, WINDOW_HEIGHT / 2.0f + RECT_HEIGHT / 2.0f);
	        glVertex2f(rectX, WINDOW_HEIGHT / 2.0f + RECT_HEIGHT / 2.0f);
	    }
	
	    glEnd();
	    SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
	}
	
	void handleEvents(bool *running, float *rectX) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				*running = false;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				grab = true;
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				grab = false;
			}  
			else if (event.type == SDL_MOUSEMOTION) {
				if (grab)
					*rectX = event.motion.x;
			}
		}
	}
	
	int main(int argc, char *argv[]) {
	    SDL_Window *window = NULL;
	    SDL_GLContext context;
	
	    if (!init(&window, &context)) {
	        return -1;
	    }
	
	    bool running = true;
	    float rectX = 0.0f;
	
	    while (running) {
	        handleEvents(&running, &rectX);
	        render(rectX);
	        /* SDL_Delay(16); // Approximately 60 FPS */
	    }
	
	    SDL_GL_DeleteContext(context);
	    SDL_DestroyWindow(window);
	    SDL_Quit();
	
	    return 0;
	}
	
#endif
