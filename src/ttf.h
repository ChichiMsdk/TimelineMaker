#ifndef TTF_H
#define TTF_H

#include <fonts/Inconsolata-Regular.h>
#include <fonts/Montserrat-Regular.h>
#include <fonts/Poppings-Regular.h>
#include <fonts/Inter-Regular.h>
#include <fonts/Nunito.h>

typedef struct raw_font
{
	void			*data;
	unsigned int	len;
}raw_font;

extern raw_font myraw[5];

#endif
