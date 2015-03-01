#include "player.h"



player::player(SDL_Surface* img){
    ground = false;
    jump = 0;
    image = img;
    box.x = 50;
    box.y = 50;
    box.w = 16;
    box.h = 20;
    xVel = 0;
    yVel = 0;
    direction = 'r';
    frame = 5;
    health = 5;
    walk = false;

    for(int i=0; i<15; i++){
        clips[i].x = i*16;
        clips[i].y = 0;
        clips[i].w = 16;
        clips[i].h = 25;
    }

}

player::~player(){
SDL_FreeSurface(image);
}

bool player::getGround(){
    return ground;
}

int player::getFrame(){
    return frame;
}

int player::getHealth(){
    return health;
}

void player::setHealth(int h){
    health = h;
}

void player::setFrame(int f){
    frame=f;
}

SDL_Rect* player::getBox(){
return &box;
}

char player::getDirection(){
    return direction;
}

void player::setDirection(char c){
    direction = c;
}

int player::getXvel(){
return xVel;
}

void player::setXvel(int vel){
xVel = vel;
}

void player::show(SDL_Surface* screen){
        SDL_BlitSurface(image,&clips[frame],screen,&box);

}

void player::move(const vector<vector <int> > &map){
    bool noCollision = 0;
    for(int i = 0;i < map.size();i++){
        for(int j=0; j<map[0].size(); j++){
                if(map[i][j] == 0){
                    if(xVel > 0)
                        frame =3;
                    continue;
                }
                SDL_Rect destinationRect = {j*16-baseclass::coord.x,i*16,16,16};
                if(collision(&box,&destinationRect)){
                    noCollision = 1;
                    if(destinationRect.y >= box.y + box.h - 11){
                        ground = 1;
                        frame = 5;
                        yVel = 0;
                    }
                    else if(destinationRect.y + destinationRect.h <= box.y + 11){
                        box.x++;
                        yVel=5;
                    }
                    if(box.x + box.w >= destinationRect.x - 5 && box.y + box.h >= destinationRect.y +6 && box.x + box.w <=destinationRect.x+20){
                        xVel=0;
                        box.x--;
                    }
                    else if( box.x <= destinationRect.x + destinationRect.w && box.y + box.h >= destinationRect.y + 6){
                        xVel = 0;
                        box.x++;
                    }
                }
        }
    }
    if(!noCollision && !jump){//Falling down
        frame = 4;
        yVel =5;
    }
    if(jump && yVel < 5 && direction == 'r'){//jump up right
        frame = 3;
        yVel++;
    }else if(jump && yVel < 5 && direction == 'l'){//jump up left
        frame = 11;
        yVel++;
    }
    else{
        jump = 0;
    }

//animation
/*
 if( this->walk == true && this->getDirection() == 'r'){
      cout<<"walking r";
      frame=0;
      //frame = frame /3;

        }else if( this->walk == true && this->getDirection() == 'l'){
           // player1->setFrame(7);
        }
*/

    box.x += xVel;
    box.y += yVel;

}

void player::setJump(){
if(ground && !jump){
    jump = 1;
    ground = 0;
    yVel =-16;
    box.y -= 5;
}
}

