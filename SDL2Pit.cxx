#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include "Classes/Colors.hxx"
#include "Classes/Viewports.hxx"
#include "DCSBIOS/ExportStreamListener.hxx"
#include "DCSBIOS/Protocol.hxx"
#include "SDL2Pit.hxx"


bool run = true;

DcsBios::ProtocolParser parser;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

int receiveThread( void* data ) {
  UDPpacket* packet;
  UDPsocket socket;

  if( data != NULL ) {
    std::cerr << "receiveThread: data is not NULL" << std::endl;
  }

  if( SDLNet_Init() < 0 ) {
    std::cerr << "SDLNet_Init(): " << SDLNet_GetError() << std::endl;
  }
  else {
    if( !( socket = SDLNet_UDP_Open( INCOMING_PORT ) ) ) {
      std::cerr << "SDLNet_UDP_Open: " << SDLNet_GetError() << std::endl;
    }
    else {
      if( !( packet = SDLNet_AllocPacket( 1536 ) ) ) {
        std::cerr << "SDLNet_AllocPacket: " << SDLNet_GetError() << std::endl;
      }
      else {
        while( run ) {
          if( SDLNet_UDP_Recv( socket, packet ) ) {
            for( int i = 0; i < packet->len; i++ ) {
              parser.processChar( packet->data[i] );
            }
          }
          else {
            SDL_Delay( 1 );
          }
        }
        SDLNet_FreePacket( packet );
      }
      SDLNet_UDP_Close( socket );
    }
    SDLNet_Quit();
  }

  return EXIT_SUCCESS;
}

int main() {
  SDL_Thread* thread = SDL_CreateThread( receiveThread, "ReceiveThread", NULL );

  int result = EXIT_SUCCESS;
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    std::cerr << "SDL_Init(): " << SDL_GetError() << std::endl;
    result = EXIT_FAILURE;
  }
  else {
    window = SDL_CreateWindow( "SDL2Pit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) {
      std::cerr << "SDL_CreateWindow(): " << SDL_GetError() << std::endl;
      result = EXIT_FAILURE;
    }
    else {
      renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if( renderer == NULL ) {
        std::cerr << "SDL_CreateRenderer(): " << SDL_GetError() << std::endl;
        result = EXIT_FAILURE;
      }
      else {
        SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );
        if( !IMG_Init( IMG_INIT_PNG ) ) {
          std::cerr << "IMG_Init(): " << IMG_GetError() << std::endl;
          result = EXIT_FAILURE;
        }
        else {
#ifdef _SDL_TTF_H
          if( TTF_Init() == -1 ) {
            std::cerr << "TTF_Init(): " << TTF_GetError << std::endl;
          }
#endif
          FPSmanager manager;

          SDL_Event event;
          SDL_Rect viewPorts[6];

          SDL_initFramerate( &manager );
          SDL_setFramerate( &manager, 60 );

          setViewPorts( viewPorts );

          while( run ) {
            while( SDL_PollEvent( &event ) != 0 ) {
              if( event.type == SDL_QUIT ) {
                run = false;
              }
              else if( event.type == SDL_KEYDOWN ) {
                switch( event.key.keysym.sym ) {
                  case SDLK_ESCAPE:
                    run = false;
                    break;
                }
              }
            }

            SDL_SetRenderDrawColor( renderer, RGBA( black ) );
            SDL_RenderSetViewport( renderer, NULL );
            //SDL_RenderClear( renderer );

            // Speedmeter
            SDL_RenderSetViewport( renderer, &viewPorts[TOP_LEFT] );
            //SDL_RenderClear( renderer );
            circleRGBA( renderer, 300/2, 300/2, 300/2-1, COLOR_WHITE );
            vlineRGBA(renderer,   0, 0, 300, COLOR_WHITE);
            vlineRGBA(renderer, 299, 0, 300, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0,   0, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0, 299, COLOR_WHITE);

            // Attitude Direction Indicator
            SDL_RenderSetViewport( renderer, &viewPorts[TOP_CENTER] );
            circleRGBA( renderer, 300/2, 300/2, 300/2-1, COLOR_WHITE );
            vlineRGBA(renderer,   0, 0, 300, COLOR_WHITE);
            vlineRGBA(renderer, 299, 0, 300, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0,   0, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0, 299, COLOR_WHITE);
            //adi.render();

            // Altimeter
            SDL_RenderSetViewport( renderer, &viewPorts[TOP_RIGHT] );
            vlineRGBA(renderer,   0, 0, 300, COLOR_WHITE);
            vlineRGBA(renderer, 299, 0, 300, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0,   0, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0, 299, COLOR_WHITE);
            circleRGBA( renderer, 300/2, 300/2, 300/2-1, COLOR_WHITE );

            // Accelerometer
            SDL_RenderSetViewport( renderer, &viewPorts[BOTTOM_LEFT] );
            vlineRGBA(renderer,   0, 0, 300, COLOR_WHITE);
            vlineRGBA(renderer, 299, 0, 300, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0,   0, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0, 299, COLOR_WHITE);
            circleRGBA( renderer, 300/2, 300/2, 300/2-1, COLOR_WHITE );

            // Horizontal Situation Indicator
            SDL_RenderSetViewport( renderer, &viewPorts[BOTTOM_CENTER] );
            vlineRGBA(renderer,   0, 0, 300, COLOR_WHITE);
            vlineRGBA(renderer, 299, 0, 300, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0,   0, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0, 299, COLOR_WHITE);
            circleRGBA( renderer, 300/2, 300/2, 300/2-1, COLOR_WHITE );

            // Vertical Velocity Indicator
            SDL_RenderSetViewport( renderer, &viewPorts[BOTTOM_RIGHT] );
            vlineRGBA(renderer,   0, 0, 300, COLOR_WHITE);
            vlineRGBA(renderer, 299, 0, 300, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0,   0, COLOR_WHITE);
            hlineRGBA(renderer, 300, 0, 299, COLOR_WHITE);
            circleRGBA( renderer, 300/2, 300/2, 300/2-1, COLOR_WHITE );

            SDL_RenderPresent( renderer );
            SDL_framerateDelay( &manager );
          }

#ifdef _SDL_TTF_H
          TTF_Quit();
#endif
          IMG_Quit();
        }
        SDL_DestroyRenderer( renderer );
        renderer = NULL;
      }
      SDL_DestroyWindow( window );
      window = NULL;
    }
    SDL_Quit();
    SDL_WaitThread( thread, NULL );
  }

  return result;
}
