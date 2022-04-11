#include "engine.h"
#include "sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "shot.h"

// Forward function declarations
void Update(float dt);
void RenderFrame(float dt);

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 576

// Street texture
Sprite street;
Sprite hracovaLod;

const int hracSirka = 100;
const int hracVyska = 100;


//=============================================================================
int main(int argc, char* argv[])
{
	if (!InitSDL())
	{
		return 1;
	}

	if (!CreateWindow("The Game", WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		return 1;
	}
	
	street = LoadSprite("assets/cyberpunk-street.png");
	hracovaLod = LoadSprite("assets/player.png");
	// Push functions to the game loop
	StartLoop(Update, RenderFrame);


	FreeSprite(street);
	FreeSprite(hracovaLod);
	CleanUp();
	return 0;
}

//=============================================================================
SDL_Rect hrac = { 30, 0, hracSirka, hracVyska };
// Shot* shot;
Shot* shots[3] = { NULL, NULL, NULL };
int speed = 200;
bool moved = false;
bool strelaExistuje = false;
void Update(float dt)
{
	moved = false;
	strelaExistuje = false;
	for (int i = 0; i < 3; i++)
	{
		if (shots[i] != NULL)
		{
			strelaExistuje = true;
			break;
		}
	}
	if (IsKeyDown(SDL_SCANCODE_LEFT))
	{
		
		if (IsKeyDown(SDL_SCANCODE_LSHIFT))
		{
			hrac.x -= (int)(speed * dt * 2 + 0.5f);
		}
		else
		{
			hrac.x -= (int)(speed * dt + 0.5f);
		}
		moved = true;
	}
		
	else if (IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		if (IsKeyDown(SDL_SCANCODE_LSHIFT))
		{
			hrac.x += (int)(speed * dt + 0.5f);
		}
		hrac.x += (int)(speed * dt + 0.5f);
		moved = true;
	}
		

	if (IsKeyDown(SDL_SCANCODE_UP))
	{
		if (IsKeyDown(SDL_SCANCODE_LSHIFT))
		{
			hrac.y -= (int)(speed * dt + 0.5f);
		}
			hrac.y -= (int)(speed * dt + 0.5f);
			moved = true;
	}
		
	else if (IsKeyDown(SDL_SCANCODE_DOWN))
	{
		if (IsKeyDown(SDL_SCANCODE_LSHIFT))
		{
			hrac.y += (int)(speed * dt + 0.5f);
		}
		hrac.y += (int)(speed * dt + 0.5f);
		moved = true;
	}
		


	if (hrac.x + hracVyska > WINDOW_WIDTH)
	{
		hrac.x = WINDOW_WIDTH - hrac.w;
	}
	else if (hrac.x < 0)
	{
		hrac.x = 0;
	}

	if (hrac.y < 0)
	{
		hrac.y = 0;
	}
	else if (hrac.y + hracVyska > WINDOW_HEIGHT)
	{
		hrac.y = WINDOW_HEIGHT - hracVyska;
	}


	// Change subsystem of project from Windows to Console
	// in order to see the stderr output
	if (IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		ExitGame();
	}
	if (IsKeyDown(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < 3; i++)
		{
			if (shots[i] == NULL)
			{
				shots[i] = new Shot(gRenderer, hrac.x + (hracSirka / 2), hrac.y);
			}
		}
		
			
		
		
		 
			
	}
	if (IsKeyDown(SDL_SCANCODE_BACKSPACE))
	{
		for (int i = 0; i < 3; i++)
		{
			shots[i] = NULL;
		}
		
	}

	//UPDATE STRELY
	if (moved)
	{
		for (int i = 0; i < 3; i++)
		{
			if (shots[i] != NULL)
			{
				shots[i]->Update();
			}
			
		}
		
	}
}

void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);

	// Draw sprite (scaled by factor of 3)
	int pixelAmp = 3;
	
	SDL_Rect backgroundRect = {
		0,
		0,
		street.sourceRect.w * pixelAmp,
		street.sourceRect.h * pixelAmp
	};
	SDL_RenderCopy(gRenderer, street.texture, NULL, &backgroundRect);

	
	for (int i = 0; i < 3; i++)
	{
		if (shots[i] != NULL)
			shots[i]->Render();
	}
	
	

	SDL_RenderCopy(gRenderer, hracovaLod.texture, NULL, &hrac);
}
