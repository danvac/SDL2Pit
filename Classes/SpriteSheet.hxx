#ifndef SPRITESHEET_HXX
#define SPRITESHEET_HXX

#include "Texture.hxx"

class SpriteSheet : public Texture
{
  public:
    int sprites;

    void renderSprite( int s );
    void renderSprite( int s, double angle );
    bool setSprites(SDL_Rect *s, int c);

    SpriteSheet();
    ~SpriteSheet();
  protected:
    SDL_Rect* _spriteRects;
    Texture _texture;
  private:
};

#endif // SPRITESHEET_HXX
