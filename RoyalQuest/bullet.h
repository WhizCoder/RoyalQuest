#include <SDL.h>
#include <iostream>
using namespace std;

#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

class bullet{
SDL_Rect box;
int xVel,yVel;
SDL_Surface* image;
SDL_Rect clips[4];
int frame;
public:
    bullet(SDL_Surface* img,int x,int y,int xVel,int yVel);
    void move();
    void show(SDL_Surface* screen);
    SDL_Rect* getBox();
};


#endif // BULLET_H_INCLUDED
