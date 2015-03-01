#include <SDL.h>
#include "base.h"
#include <vector>
#include <iostream>
using namespace std;

#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

class enemy:public baseclass{
    SDL_Rect box;
    int xVel,yVel;
    SDL_Surface* image;
    bool ground;
    SDL_Rect clips[2];
public:
    enemy(SDL_Surface*,int,int,int,int);
    void move(vector<vector <int> > &map);
    void show(SDL_Surface*);
    SDL_Rect* getBox();
};


#endif // ENEMY_H_INCLUDED
