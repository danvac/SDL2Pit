#ifndef TEXTURE_HXX
#define TEXTURE_HXX

#include <string>
#include <SDL2/SDL.h>

class Texture {
  public:
    int getWidth();
    int getHeight();


    bool createBlank( int width, int height );
    void free();
    bool loadImage( std::string image );
    void render();
    void render( int x, int y );
    void render( int x, int y, double angle, SDL_Point* center );
    void render( int x, int y, double angle, SDL_Rect* srcrect = NULL );
    void render( int x, int y, SDL_Rect* srcrect, SDL_Rect* dstrect, double angle, SDL_Point* center );
    void setAsRenderTarget();
    void setBlendMode( SDL_BlendMode blendmode = SDL_BLENDMODE_BLEND );

    Texture();
    ~Texture();
    SDL_Texture* _texture;


  protected:
    int _width;
    int _height;
};

#endif // TEXTURE_HXX
