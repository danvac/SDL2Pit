#ifndef VIEWPORTS_HXX
#define VIEWPORTS_HXX

#include "SDL2/SDL.h"

enum instrument { TOP_LEFT, TOP_CENTER, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT };

void setViewPorts( SDL_Rect* viewPorts );

#endif // VIEWPORTS_HXX
