#include "SpriteSheet.hxx"

extern SDL_Renderer* renderer;

void SpriteSheet::renderSprite( int s ) {
  SDL_Rect dstrect = { 0, 0, _spriteRects[s].w, _spriteRects[s].h };
  SDL_RenderCopyEx( renderer, _texture._texture, &_spriteRects[s], &dstrect, 0.0, NULL, SDL_FLIP_NONE );
}

void SpriteSheet::renderSprite( int s, double angle ) {
  SDL_Rect dstrect = { 0, 0, _spriteRects[s].w, _spriteRects[s].h };
  SDL_RenderCopyEx( renderer, _texture._texture, &_spriteRects[s], &dstrect, angle, NULL, SDL_FLIP_NONE );
}

bool SpriteSheet::setSprites( SDL_Rect *s, int c ) {
  if( c <= 0 ) return false;
  _spriteRects = s;
  sprites = c;
  return true;
}

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::~SpriteSheet()
{
}
