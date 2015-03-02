#include "game.h"

SDL_Rect baseclass::coord;

game::game(){
	init();
	block = load_image("blocks.png");
	background = load_image("background.png");
	bul = load_image("bullets.png");
	enemy1 = load_image("enemy1.png");
	camera.x = camera.y = 0;
	baseclass::coord.x = baseclass::coord.y = 0;
	running = true;
	shooting = false;
	baseclass::coord.w = camera.w = SCREEN_WIDTH;
	baseclass::coord.h = camera.h = SCREEN_HEIGHT;
	direction[0] = direction[1] = 0;
	player1 = new player(load_image("player.png"));
	// enemies.push_back(new enemy(enemy1,400,400,1,0));
}

bool game::init(){
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf("Warning: Linear texture filtering not enabled!");
		}

		window = SDL_CreateWindow("Royal Quest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}

		else{
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)){
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else{
				screen = SDL_GetWindowSurface(window);
			}
		}
	}
	return success;
}

game::~game(){
	SDL_FreeSurface(block);
	SDL_FreeSurface(background);
	SDL_FreeSurface(bul);
	SDL_Quit();
}

SDL_Surface* game::load_image(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xff, 0xff));
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}



void game::handleEvents(){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type){
		case SDL_QUIT: running = false;
			return;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym){
			case SDLK_LEFT: direction[0] = 1;
				player1->walk = true;
				player1->setDirection('l');

				break;
			case SDLK_RIGHT: direction[1] = 1;
				player1->walk = true;
				player1->setDirection('r');

				break;
			case SDLK_UP: player1->setJump();
				break;
			case SDLK_ESCAPE: SDL_Quit();
				break;
			case SDLK_f:
				shooting = true;
				// cout<<player1->getDirection()<<endl;
				//Adding new element to vector when player press f
				if (player1->getDirection() == 'r'){
					bullets.push_back(new bullet(bul, player1->getBox()->x + player1->getBox()->w - 5, player1->getBox()->y + 10, 5, 0));
				}
				else if (player1->getDirection() == 'l'){
					bullets.push_back(new bullet(bul, player1->getBox()->x, player1->getBox()->y + 10, -5, 0));

				}
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym){
			case SDLK_LEFT:
				player1->walk = false;
				direction[0] = 0;
				break;
			case SDLK_RIGHT:
				player1->walk = false;
				direction[1] = 0;
				break;
			case SDLK_f:shooting = false;
				break;
			}
		}
	}
}

void game::loadmap(string path){
	ifstream in("map.map");
	if (!in.is_open()){
		cout << "Problem loading the file";
	}
	int width, height;
	in >> width;
	in >> height;
	int current;
	cout << "Width: " << width << "Height: " << height;
	for (int i = 0; i<height; i++){
		vector< int > vec;
		for (int j = 0; j<width; j++){
			if (in.eof()){
				cout << "END of file reached too soon";
			}
			in >> current;
			//to add new enemies indicated by 9 in the map
			if (current == 9){
				enemies.push_back(new enemy(enemy1, j * 16, i * 16, 1, 0));
			}
			else{
				if (current >= 0 && current <= 63){
					vec.push_back(current);
				}
				else{
					vec.push_back(0);
				}
			}

		}
		map.push_back(vec);
	}
	in.close();
}

void game::showmap(){
	//int start = (baseclass::coord.x - (baseclass::coord.x%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	//int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE -(baseclass::coord.x+baseclass::coord.w)%baseclass::TILE_SIZE))/baseclass::TILE_SIZE;
	//if(start<0)
	//   start = 0;
	//if(end>map[0].size())
	//  end = map[0].size();

	for (int i = 0; i <(int)map.size(); i++){
		for (int j = 0; j<(int)map[0].size(); j++){
			if (map[i][j] != 0){
				SDL_Rect blockrect = { (map[i][j] - 1)*baseclass::TILE_SIZE, 0, baseclass::TILE_SIZE, baseclass::TILE_SIZE };
				SDL_Rect destinationRect = { j*baseclass::TILE_SIZE - baseclass::coord.x, i * 16 };
				SDL_BlitSurface(block, &blockrect, screen, &destinationRect);
			}
		}
	}
}



void game::start(){
	Uint32 fpsRegulator;
	loadmap("map.map");
	//int f1=30;
	while (running){
		fpsRegulator = SDL_GetTicks();
		handleEvents();
		/*
		if(direction[0]){
		if(player1->getBox()->x > 0)
		player1->setXvel(-5);
		else{
		player1->setXvel(0);
		camera.x -= 5;
		baseclass::coord.x -= 5;
		}
		if(camera.x <= 0)
		camera.x = 2000 - SCREEN_WIDTH;
		}

		else if(direction[1]){
		if(player1->getBox()->x < 80)
		player1->setXvel(5);
		else{
		player1 ->setXvel(0);
		camera.x += 5;
		baseclass::coord.x += 5;
		}
		if(camera.x >= 2000-SCREEN_WIDTH)
		camera.x = 0;
		}
		else
		player1->setXvel(0);
		*/
		if (direction[0]){
			if (player1->getBox()->x > SCREEN_WIDTH / 2)
				player1->setXvel(-5);
			else{
				player1->setXvel(0);
				camera.x -= 5;
				baseclass::coord.x -= 5;
			}
			if (camera.x <= 0){
				camera.x = 0;
				baseclass::coord.x = 0;
				player1->setXvel(-5);
				// camera.x = 2000 - SCREEN_WIDTH;
			}
		}

		else if (direction[1]){
			if (player1->getBox()->x < SCREEN_WIDTH / 2)
				player1->setXvel(5);
			else{
				player1->setXvel(0);
				camera.x += 5;
				baseclass::coord.x += 5;
			}
			if (camera.x >= 2000 - SCREEN_WIDTH)
				camera.x = 0;
		}
		else
			player1->setXvel(0);
		//Checking Bullets collision
		bool noCollision = false;
		for (int i = 0; i < (int)map.size(); i++){
			for (int j = 0; j<(int)map[0].size(); j++){
				if (map[i][j] == 0)
					continue;
				SDL_Rect destinationRect = { j * 16 - baseclass::coord.x, i * 16, 16, 16 };
				for (int g = 0; g < (int)bullets.size(); g++){
					if (collision(bullets[g]->getBox(), &destinationRect)){
						noCollision = 1;
						delete bullets[g];
						bullets.erase(bullets.begin() + g);
					}
				}
			}
		}
		// Bullets are deleted once they leave the window
		for (int i = 0; i<(int)bullets.size(); i++){
			if (bullets[i]->getBox()->x >= screen->w || bullets[i]->getBox()->x <= 0){
				delete bullets[i];
				bullets.erase(bullets.begin() + i);

			}
		}

		player1->move(map);
		//player running animation

		static int frame_right;
		static int frame_left;
		if (player1->walk == true && player1->getDirection() == 'r' && player1->getGround() == true){
			//running right
			player1->setFrame(frame_right / 3);
			cout << endl << "current right frame: " << player1->getFrame();
			player1->show(screen);
			frame_right++;
			if (frame_right >= 9)
				frame_right = 0;

		}
		else if (player1->walk == true && player1->getDirection() == 'l' && player1->getGround() == true){
			// running left
			player1->setFrame(frame_left / 3);
			cout << endl << "current left frame: " << frame_left;
			player1->show(screen);
			frame_left--;
			if (frame_left <= 23)
				frame_left = 30;
		}

		//left and right shooting animation
		if (shooting == true && player1->getDirection() == 'r'){
			player1->setFrame(6);
		}
		else if (shooting == true && player1->getDirection() == 'l'){
			player1->setFrame(7);
		}

		//Bullets moving
		for (int i = 0; i<(int)bullets.size(); i++){
			bullets[i]->move();
		}
		//Collision of bullets with enemies
		for (int i = 0; i<(int)bullets.size(); i++){
			for (int j = 0; j<(int)enemies.size(); j++){
				SDL_Rect tmpRect = { enemies[j]->getBox()->x - baseclass::coord.x, enemies[j]->getBox()->y, 16, 16 };
				if (collision(&tmpRect, bullets[i]->getBox())){
					delete enemies[j];
					delete bullets[i];
					enemies.erase(enemies.begin() + j);
					bullets.erase(bullets.begin() + i);
				}
			}
		}
		//Collision of Player with enemies
		for (int j = 0; j<(int)enemies.size(); j++){
			SDL_Rect tmpRect = { enemies[j]->getBox()->x - baseclass::coord.x, enemies[j]->getBox()->y, 16, 16 };
			if (collision(&tmpRect, player1->getBox())){
				//Checks if player is on top of the enemy
				if (player1->getBox()->y + player1->getBox()->h >= enemies[j]->getBox()->y && player1->getBox()->y + player1->getBox()->h <= enemies[j]->getBox()->y + 10){
					delete enemies[j];
					enemies.erase(enemies.begin() + j);
				}
				else{
					player1->setHealth(player1->getHealth() - 1);
				}
			}
		}
		//Moving the enemy 1
		for (int i = 0; i<(int)enemies.size(); i++){
			enemies[i]->move(map);
		}

		SDL_BlitSurface(background, &camera, screen, NULL);
		showmap();
		player1->show(screen);
		//Bullets are displayed
		for (int i = 0; i<(int)bullets.size(); i++)
			bullets[i]->show(screen);
		//Showing the enemy 1
		for (int i = 0; i<(int)enemies.size(); i++){
			enemies[i]->show(screen);
		}
		SDL_UpdateWindowSurface(window);
		//Game over when the health reaches 0
		if (player1->getHealth() <= 0 || player1->getBox()->y >= screen->h){
			running = false;
			cout << "\nGAME over";
		}
		if (1000 / 30 >(SDL_GetTicks() - fpsRegulator)){
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - fpsRegulator));
		}
	}

}
