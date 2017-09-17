#include <iostream>
#include "SDL2/SDL_image.h"
#include "Texture.hxx"

extern SDL_Renderer* renderer;

int Texture::getWidth() {
  return _width;
}

int Texture::getHeight() {
  return _height;
}

bool Texture::createBlank( int w, int h ) {
  free();
  _texture = SDL_CreateTexture(
               renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h
             );
  if( _texture == NULL ) {
    std::cerr << "SDL_CreateTexture(): " << SDL_GetError() << std::endl;
    return false;
  }
  else {
    setBlendMode();
    _width = w;
    _height = h;
    return true;
  }
}

void Texture::free() {
  if( _texture != NULL ) {
    SDL_DestroyTexture( _texture );
    _texture = NULL;
  }
  _width = 0;
  _height = 0;
}

bool Texture::loadImage( std::string image ) {
  free();

  SDL_Surface* loaded = IMG_Load( image.c_str() );
  if( loaded == NULL ) {
    std::cerr << "IMG_Load(): " << IMG_GetError() << std::endl;
  }
  else {
    _texture = SDL_CreateTextureFromSurface( renderer, loaded );
    if( _texture == NULL ) {
      std::cerr << "SDL_CreateTextureFromSurface(): " << SDL_GetError() << std::endl;
    }
    else {
      SDL_SetTextureBlendMode( _texture, SDL_BLENDMODE_BLEND );
      _width = loaded->w;
      _height = loaded->h;
    }
    SDL_FreeSurface( loaded );
  }

  return _texture != NULL;

}

void Texture::render() {
  render( 0, 0 );
}

void Texture::render( int x, int y ) {
  SDL_Rect dstrect = { x, y, _width, _height };
  SDL_RenderCopy( renderer, _texture, NULL, &dstrect );
}

void Texture::render( int x, int y, double angle, SDL_Point* center ) {
  SDL_RenderCopyEx( renderer, _texture, NULL, NULL, angle, center, SDL_FLIP_NONE );
}

void Texture::render( int x, int y, double angle, SDL_Rect* srcrect ) {
  SDL_Rect dstrect = { x, y, _width, _height };
  if( srcrect != NULL ) {
    dstrect.w = srcrect->w;
    dstrect.h = srcrect->h;
  }
  SDL_RenderCopyEx( renderer, _texture, srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE );
}

void Texture::render( int x, int y, SDL_Rect* srcrect, SDL_Rect* dstrect, double angle, SDL_Point* center ) {
  SDL_RenderCopyEx( renderer, _texture, srcrect, dstrect, angle, center, SDL_FLIP_NONE );
}

void Texture::setAsRenderTarget() {
  SDL_SetRenderTarget( renderer, _texture );
}

void Texture::setBlendMode( SDL_BlendMode blendmode ) {
  SDL_SetTextureBlendMode( _texture, blendmode );
}


Texture::Texture() {
  _texture = NULL;

  _width = 0;
  _height = 0;
}

Texture::~Texture() {
  free();
}
