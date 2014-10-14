// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	//player 1
	if (!sonyTexture.initialize(graphics, SONY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Sony texture initialization failed"));
	if (!sony.initialize(this, 50,50,0, &sonyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init sony"));
	if (!bgTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Background texture initialization failed"));
	if (!bg.initialize(graphics, 640,480,0, &bgTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init background"));
	sony.setX(50);
	sony.setY(GAME_HEIGHT/2 - (sony.getHeight()*SONY_IMAGE_SCALE)/2);
	sony.setScale(SONY_IMAGE_SCALE);

	//player 2
	if (!sony2.initialize(this, 50,50,0, &sonyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init sony"));
	sony2.setX(590);
	sony2.setY(GAME_HEIGHT/2 - (sony2.getHeight()*SONY_IMAGE_SCALE)/2);
	sony2.setScale(SONY_IMAGE_SCALE);

	
	sonyVel.xVel = 0;
	sonyVel.yVel = 60;

	sony2Vel.xVel = 0;
	sony2Vel.yVel = 60;

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	//Unomment to get the image to move

	D3DXVECTOR2	pos;
	D3DXVECTOR2	pos2;
	//pos.x = sony.getX() + sonyVel.xVel * frameTime;
	//sony.setX(pos.x);
//WRAP

 

//REFLECT
 

 ////////////////
// INPUT MODS
 ////////////////

	D3DXVECTOR2 direction(0,0);
	D3DXVECTOR2 direction2(0,0);
	
	
	if (input->isKeyDown(VK_UP))
		direction.y = -1;
	if (input->isKeyDown(VK_DOWN))
		direction.y = 1;
	if (GetAsyncKeyState( 'S' ) )
		direction2.y = 1;
	if( GetAsyncKeyState( 'W' ) )
		direction2.y = -1;
	

	// Wrap around
	/*
	if(sony.getX()>GAME_WIDTH)
		sony.setX(-sony.getWidth()*sony.getScale());
	if(sony.getX()+sony.getWidth()*sony.getScale()<0)
		sony.setX(GAME_WIDTH);
	if(sony.getY()>GAME_HEIGHT)
		sony.setY(-sony.getHeight()*sony.getScale());
	if(sony.getY()+sony.getHeight()*sony.getScale()<0)
		sony.setY(GAME_HEIGHT);
	*/

	// Reflect
	/*
	if(sony.getX()+sony.getWidth()*sony.getScale()>GAME_WIDTH)
		sonyVel.xVel *= -1;
	if(sony.getX()<0)
		sonyVel.xVel *= -1;
	if(sony.getY()+sony.getHeight()*sony.getScale()>GAME_HEIGHT)
		sonyVel.yVel *= -1;
	if(sony.getY()<0)
		sonyVel.yVel *= -1;
	*/
	/*
	if(sony.getX()+sony.getWidth()*sony.getScale()>GAME_WIDTH)
		direction.x = 0;
	if(sony.getX()<0)
		direction.x = 0;
	if(sony.getY()+sony.getHeight()*sony.getScale()>GAME_HEIGHT)
		direction.y = 0;
	if(sony.getY()<0)
		direction.y = 0;
	*/
	D3DXVec2Normalize(&direction, &direction);

	pos.y = sony.getY() + sonyVel.yVel * frameTime * direction.y;
	sony.setY(pos.y);


	pos2.y = sony2.getY() + sony2Vel.yVel * frameTime * direction2.y;
	sony2.setY(pos2.y);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	bg.draw();
	sony.draw();
	sony2.draw();

	

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	sonyTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
   
	sonyTexture.onResetDevice();

    Game::resetAll();
    return;
}
