#include<SDL.h>
#include<iostream>
#include<vector>
#include "base.h"
using namespace std;

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class player:baseclass{
    SDL_Rect box;
    SDL_Surface* image;
    SDL_Rect clips[20];
    bool ground;
    bool jump;
    char direction;
    int xVel,yVel;
    int frame;
    int health;
public:
    bool playerCollision(SDL_Rect a,const vector<vector <int> > &map);
    bool walk;
    player(SDL_Surface* img);
    ~player();
    SDL_Rect* getBox();
    void setXvel(int vel);
    int getXvel();
    int getHealth();
    void setHealth(int);
    char getDirection();
    void setDirection(char);
    void setFrame(int);
    int getFrame();
    bool getGround();
    void move(const vector<vector <int> > &map);
    void show(SDL_Surface* screen);
    void setJump();

};

#endif // PLAYER_H_INCLUDED
