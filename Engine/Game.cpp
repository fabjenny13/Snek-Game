/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(50,15, gfx),
	snek({ 5,5 }), 
	goal({ 10,10 })
{
	brd.SpawnPoison();
	brd.SpawnObstacle();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			delta_loc = { 0, -1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1, 0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1, 0 };
		}

		Location nextHeadLocation = snek.GetHeadLocation() + delta_loc;
		if (goal.IsEaten(snek.GetHeadLocation()))
		{
			goal.Respawn(brd);
			brd.SpawnObstacle();
			snek.Grow();
		}
		else if (brd.IsPoisonConsumed(snek.GetHeadLocation()) && minCoolDown < cooldownPeriod)
		{
			cooldownPeriod -= 0.05f;
		}


		if (timePassed < cooldownPeriod)
		{
			timePassed += stepTime;
		}
		else
		{
			timePassed = 0.0f;
			if (brd.IsObstacleHit(nextHeadLocation) || snek.CollidedWithSelf(nextHeadLocation) || brd.IsWallHit(nextHeadLocation))
			{
				gameOver = true;
			}
			else
			{
				snek.Move(delta_loc);
			}
		}

	}
}

void Game::ComposeFrame()
{
	brd.Draw();
	snek.Draw(brd);
	goal.Draw(brd);
	if (gameOver)
	{
		SpriteCodex::DrawGameOver(Graphics::ScreenWidth / 2 - 50, Graphics::ScreenHeight / 2 - 50, gfx);
	}

}
