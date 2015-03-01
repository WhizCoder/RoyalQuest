#include <SDL.h>
#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

class baseclass{
protected:
	bool collision(SDL_Rect* rec1, SDL_Rect* rec2);
public:
	static SDL_Rect coord;
	static const int TILE_SIZE = 16;

};

#endif // BASE_H_INCLUDED
