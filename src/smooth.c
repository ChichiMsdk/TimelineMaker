#include "smooth.h"

float 
easeInOutQuad(float t) 
{
	if (t < 0.5f) 
	{
		return 2.0f * t * t;
	}
	else 
	{
		return -1.0f + (4.0f - 2.0f * t) * t;
	}
}

float
interpolate2(float start, float end, float factor)
{
    float easedFactor = easeInOutQuad(factor);
    return start + easedFactor * (end - start);
}

float 
interpolate(float start, float end, float factor)
{ 
	return start + factor * (end - start); 
}
