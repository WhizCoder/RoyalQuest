#include <fstream>
#include <vector>
#include <SDL.h>
#include <iostream>
#include<SDL_image.h>
#include<string>
#include "base.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

using namespace std;

class game:public baseclass{
    SDL_Surface* screen,*background,*block,*bul,*enemy1;
    SDL_Rect camera;
    vector< vector<int> > map;
    vector< bullet* > bullets;
    vector< enemy* > enemies;
    bool direction[2];
    SDL_Surface* load_image( string path);
    SDL_Window* window;
    bool running;
    void loadmap(string path);
    void showmap();
    void handleEvents();
    bool shooting;
    static const int SCREEN_WIDTH=640;
    static const int SCREEN_HEIGHT=480;
    player* player1;
public:
    game();
    ~game();
    bool init();
    void start();
};

#endif // GAME_H_INCLUDED
