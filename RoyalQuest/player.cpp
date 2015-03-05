#include "player.h"



player::player(SDL_Surface* img){
    ground = false;
    jump = 0;
    image = img;
    box.x = 50;
    box.y = 100;
    box.w = 16;
    box.h = 16;
    xVel = 0;
    yVel = 5;
    direction = 'r';
    frame = 5;
    health = 5;
    walk = false;

    for(int i=0; i<15; i++){
        clips[i].x = i*16;
        clips[i].y = 0;
        clips[i].w = 16;
        clips[i].h = 20;
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

bool player::playerCollision(SDL_Rect a,const vector<vector <int> > &map){
      for(int i = 0;i < (int)map.size();i++){
        for(int j=0; j<(int)map[0].size(); j++){
            SDL_Rect destinationRect = {j*16-baseclass::coord.x,i*16,16,16};//relative coord
            if(map[i][j] != 0){
                if (collision(&box,&destinationRect)){
                    return true;
                }
				
            }
        }
      }
	 return false;
}

void player::move(const vector<vector <int> > &map){
    bool collide = false;
    box.x += xVel;

    if(playerCollision(box,map)){
        cout<<xVel<<" ";
        box.x -= xVel;
        if(xVel == 0 && direction == 'r' ){
            box.x-=5;
            cout<<direction<<" ";
        }else if(xVel == 0 && direction == 'l'){
            box.x+=5;
            cout<<direction<<" ";
        }
        collide = true;
		cout << "Player collided with object!" << endl; /*Player collides with an object*/
    }

    box.y += yVel;
    if(playerCollision(box,map)){
        ground = true;
        box.y-=yVel;
        collide = true;
    }


if(collide == true && !jump){//Falling down
        frame = 5;
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

}



void player::setJump(){
	if (!jump && ground){ /*check if player is on d ground*/
        jump = 1;
        ground = false;
		yVel = -12; /*sets the jump height - how high the player should jump*/
        box.y -= 5;
    }
}


