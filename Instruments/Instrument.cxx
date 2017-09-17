#include "Instrument.hxx"

void Instrument::setDimensions( int w, int h ) {
  width = w;
  height = h;
}

Instrument::Instrument() {
  width = 300;
  height = 300;
}

Instrument::~Instrument() {
  texture.~Texture();
}
