#ifndef includes_h
#define includes_h

#ifdef EMSCRIPTEN_BUILD
#define RESOURCES_PATH string("")
#define CONFIG_PATH RESOURCES_PATH + string("config/")
#define IMG_PATH RESOURCES_PATH + string("images/")
#define SOUNDS_PATH RESOURCES_PATH + string("sounds/")
#else
#define RESOURCES_PATH string("")
#define CONFIG_PATH RESOURCES_PATH + string("config\\")
#define IMG_PATH RESOURCES_PATH + string("images\\")
#define SOUNDS_PATH RESOURCES_PATH + string("sounds\\")
#endif

#if defined(ENABLE_FPGA_USB) || defined(__MICROBLAZE__) || defined(__PPC__)
typedef unsigned int Uint32;
typedef struct SDL_Rect {
    int x;
    int y;
    int w;
    int h;
} SDL_Rect;
typedef struct SDL_Point {
    int x;
    int y;
} SDL_Point;
typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Surface SDL_Surface;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Event {
    int type;
} SDL_Event;
typedef struct SDL_GameController SDL_GameController;
typedef struct Mix_Chunk Mix_Chunk;
typedef struct Mix_Music Mix_Music;
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

#define WIN_WIDTH 256
#define WIN_HEIGHT 240

#define LEFT_FIGHTER  "left.fighter"
#define RIGHT_FIGHTER "right.fighter"

#include <iostream>
#include <assert.h>
#include <list>
#include <map>
#include <vector>
#include <algorithm>    // std::for_each
#include <fstream>
#include <time.h>       /* time */

using namespace std;

#endif /* includes_h */
