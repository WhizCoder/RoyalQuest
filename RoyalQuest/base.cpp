#include "base.h"

/*bool baseclass::collision(SDL_Rect* rec1,SDL_Rect* rec2){
if(rec1->y >= rec2->y + rec2->h)
return 0;
if(rec1->x >= rec2->x + rec2->w)
return 0;
if(rec1->y + rec1->h <= rec2->y)
return 0;
if(rec1->x + rec1->w <= rec2->x)
return 0;
return 1;

}
*/
bool baseclass::collision(SDL_Rect* a, SDL_Rect* b)
{

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;


	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;


	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;


	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}


	return true;
}
