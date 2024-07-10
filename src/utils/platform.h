#ifndef PLATFORM_H
#define PLATFORM_H

#include "defines.h"

void	mywrite(const char* message, u8 colour);
void	mywrite_error(const char* message, u8 colour);

f64		myget_absolute_time();

#endif // PLATFORM_H
