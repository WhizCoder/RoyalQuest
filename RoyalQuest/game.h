#include <fstream>
#include <vector>
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include<string>
#include "base.h"


#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

using namespace std;

class game{
	SDL_Surface* screen, *background, *block;
	SDL_Rect camera;
	vector< vector<int> > map;
	bool direction[2];
	SDL_Surface* load_image(string path);
	SDL_Window* window;
	bool running;
	void loadmap(string path);
	void showmap();
	void handleEvents();
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
public:
	game();
	~game();
	bool init();
	void start();
};

#endif // GAME_H_INCLUDED
