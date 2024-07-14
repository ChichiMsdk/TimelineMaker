#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>

typedef struct font font;
typedef struct font_data font_data;
typedef struct glyph glyph;

typedef struct glyph
{
	SDL_Texture	*texture;
	char		*c;
	int			w;
	int			h;
} glyph;

typedef struct font_data
{
	TTF_Font	*font;
	int			height;
	char		padding[4];
	/* Text storage for graphemes; simplified here */
	size_t		text_buf_len;
	size_t		text_buf_capacity;
	char		*text_buf;
	char		*text_next;
	/* the glyph atlas */
	size_t		glyphs_capacity;
	size_t		glyphs_len;
	glyph		*glyphs;
} font_data;

typedef struct font
{
	/* State; see below */
	SDL_Color	color;
	font_data	data;
	float		x;
	float		y;
} font;

void				init_font(font *f, SDL_Renderer *r, TTF_Font *ttf);
void				font_write(font *f, SDL_Renderer *r, SDL_Point p, const char *txt);
static const glyph	*font_putchar(font *f, SDL_Renderer *r, SDL_Point dest, char txt);
static void			font_build_atlas(font *f, TTF_Font *ttf, SDL_Renderer *r);
static void			font_glyph_create_texture(TTF_Font *ttf, SDL_Renderer *r, glyph *g);
SDL_Texture 		*create_static_text(TTF_Font *ttf, SDL_Renderer *r, const char *text);
#endif
