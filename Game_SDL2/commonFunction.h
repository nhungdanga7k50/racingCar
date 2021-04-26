#ifndef commonFunction_H_
#define commonFunction_H_

#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 540;
const int WIDTH_RACE = 480;
const int BPP = 32;
const int NUM_OBSTACLE = 4;

static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_background = NULL;
static SDL_Surface *g_race = NULL;
static SDL_Surface *gameOver = NULL;
static SDL_Surface *g_bground1 = NULL;
static SDL_Surface *g_bground2 = NULL;
static SDL_Event g_event;
static Mix_Chunk *g_sound;

//Tạo một namespace để chứa các hàm xử lý chung
namespace commonFun
{
	SDL_Surface *LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface *screen, SDL_Surface *des, int x, int y);
	bool checkCollision(const SDL_Rect &object1, const SDL_Rect &object2);
	int showMenu(SDL_Surface *des, TTF_Font *font);
	int choose(SDL_Surface *des, TTF_Font *font, int addScore);
	void cleanUp();
}

#endif
