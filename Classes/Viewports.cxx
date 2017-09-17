#include "Viewports.hxx"

void setViewPorts( SDL_Rect* viewPorts ) {
  viewPorts[TOP_LEFT].x = 0;
  viewPorts[TOP_LEFT].y = 0;
  viewPorts[TOP_LEFT].w = 300;
  viewPorts[TOP_LEFT].h = 300;
  viewPorts[TOP_CENTER].x = 362;
  viewPorts[TOP_CENTER].y = 0;
  viewPorts[TOP_CENTER].w = 300;
  viewPorts[TOP_CENTER].h = 300;
  viewPorts[TOP_RIGHT].x = 724;
  viewPorts[TOP_RIGHT].y = 0;
  viewPorts[TOP_RIGHT].w = 300;
  viewPorts[TOP_RIGHT].h = 300;
  viewPorts[BOTTOM_LEFT].x = 0;
  viewPorts[BOTTOM_LEFT].y = 300;
  viewPorts[BOTTOM_LEFT].w = 300;
  viewPorts[BOTTOM_LEFT].h = 300;
  viewPorts[BOTTOM_CENTER].x = 362;
  viewPorts[BOTTOM_CENTER].y = 300;
  viewPorts[BOTTOM_CENTER].w = 300;
  viewPorts[BOTTOM_CENTER].h = 300;
  viewPorts[BOTTOM_RIGHT].x = 724;
  viewPorts[BOTTOM_RIGHT].y = 300;
  viewPorts[BOTTOM_RIGHT].w = 300;
  viewPorts[BOTTOM_RIGHT].h = 300;
}
