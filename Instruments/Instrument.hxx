#ifndef INSTRUMENT_HXX
#define INSTRUMENT_HXX

#include "../Classes/SpriteSheet.hxx"
#include "../Classes/Texture.hxx"

class Instrument {
  public:
    void setDimensions( int w, int h );
    Instrument();
    ~Instrument();
  protected:
    int width;
    int height;

    SpriteSheet sheet;
    Texture texture;
};

#endif // INSTRUMENT_HXX
