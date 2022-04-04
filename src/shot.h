#pragma once
#include "SDL.h"
#include "sprite.h"
#include "engine.h"

class Shot
{
public:
	Shot(SDL_Renderer* ren, const int parX, const int parY);
	~Shot();

	void Render();
	void Update();
private:

	int y;
	int x;

	Sprite ObjTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};
