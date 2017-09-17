#ifndef COLORS_HXX
#define COLORS_HXX

//#define COLOR_BLACK 0x00, 0x00, 0x00, 0xFF
#define COLOR_GAINSBORO 0xDC, 0xDC, 0xDC, 0xFF
#define COLOR_WHITE 0xFF, 0xFF, 0xFF, 0xFF
#define COLOR_YELLOW 0xFF, 0xFF, 0x00, 0xFF

#define RGB(color) color.r, color.g, color.b
#define RGBA(color) color.r, color.g, color.b, color.a

extern SDL_Color black;
extern SDL_Color dimgray;
extern SDL_Color gainsboro;
extern SDL_Color white;
extern SDL_Color whitesmoke;
extern SDL_Color yellow;

#endif // COLORS_HXX
