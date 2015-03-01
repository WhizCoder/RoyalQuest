#include "bullet.h"

bullet::bullet(SDL_Surface* img,int x,int y,int xvel,int yvel){
    box.x = x;
    box.y = y;
    image = img;
    box.w = 5;
    box.h = 10;
    xVel = xvel;
    yVel = yvel;
    frame = 0;


    for(int i=0; i<3; i++){
        clips[i].x = i*12;
        clips[i].y = 0;
        clips[i].w = 12;
        clips[i].h = 10;
    }

}

void bullet::move(){
    box.x += xVel;
    box.y += yVel;
}

void bullet::show(SDL_Surface* screen)
{
    if(frame >= 9)
        frame =0;

	//cout<<frame<<endl;//animation test
	frame ++;
    SDL_BlitSurface(image,&clips[frame%2],screen,&box);
 }

SDL_Rect* bullet::getBox(){
return &box;
}
