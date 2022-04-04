#include "shot.h"
#include "sprite.h"

Shot::Shot(SDL_Renderer* ren, const int parX, const int parY) :
	srcRect({ 0 }),
	destRect({ 0 })
{
	renderer = ren;
	ObjTexture =  LoadSprite("assets/shot.png");
	srcRect.h = 30;
	srcRect.w = 10;
	srcRect.x = 0;
	srcRect.y = 0;
	x = parX;
	y = parY;
	destRect.h = 30;
	destRect.w = 10;
}

Shot::~Shot()
{
	FreeSprite(ObjTexture);
}

void Shot::Update()
{
	destRect.x = x;
	destRect.y += 10;
}

void Shot::Render()
{
	SDL_RenderCopy(renderer, ObjTexture.texture, &srcRect, &destRect);
}