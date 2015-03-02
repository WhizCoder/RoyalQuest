#include "enemy.h"

enemy::enemy(SDL_Surface* img, int x, int y, int xvel, int yvel){
	image = img;
	box.x = x;
	box.y = y;
	box.w = image->w / 2;
	box.h = image->h;
	xVel = xvel;
	yVel = yvel;
	ground = 0;

	for (int i = 0; i<2; i++){
		clips[i].x = i * 25;
		clips[i].y = 0;
		clips[i].w = 15;
		clips[i].h = 25;
	}

}

void enemy::show(SDL_Surface* screen){
	SDL_Rect temp = { box.x - coord.x, box.y, 16, 16 };// changing to absolute coord
	SDL_BlitSurface(image, &clips[0], screen, &temp);
}

SDL_Rect* enemy::getBox(){
	return &box;
}

void enemy::move(vector< vector <int> >& map){

	bool noCollision = 0;
	for (int i = 0; i <(int) map.size(); i++){
		for (int j = 0; j<(int)map[0].size(); j++){
			if (map[i][j] == 0)
				continue;
			SDL_Rect destinationRect = { j * 16, i * 16, 16, 16 };
			if (collision(&box, &destinationRect)){
				noCollision = 1;
				if (destinationRect.y >= box.y + box.h - 11){
					ground = 1;
					yVel = 0;
					noCollision = 1;
				}
				else if (destinationRect.y + destinationRect.h <= box.y + 11){
					xVel = -xVel;

				}
				if (box.x + box.w >= destinationRect.x - 5 && box.y + box.h >= destinationRect.y + 6 && box.x + box.w <= destinationRect.x + 20){
					xVel = -xVel;
				}
				else if (box.x <= destinationRect.x + destinationRect.w && box.y + box.h >= destinationRect.y + 6){
					xVel = -xVel;
					box.x++;
				}
			}
		}
	}

	if (!noCollision)
		yVel = 5;
	//cout<<box.x<<endl;

	box.x += xVel;
	box.y += yVel;
}
