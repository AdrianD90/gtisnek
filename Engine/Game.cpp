#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snek({2, 2}),
	goal(rng, brd, snek) {
}

void Game::Go() {
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel() {
	if (gameIsStarted) {
		if (!gameIsOver) {
			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				deltaLoc = { 0, -1 };
			}

			if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				deltaLoc = { 0, 1 };
			}

			if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				deltaLoc = { -1, 0 };
			}

			if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
				deltaLoc = { 1, 0 };
			}

			++snekMoveCounter;
			if (snekMoveCounter >= snekMovePeriod) {
				snekMoveCounter = 0;
				const Location next = snek.GetNextHeadLocation(deltaLoc);
				if (!brd.IsInsideBoard(next) || snek.IsInTileExceptEnd(next)) {
					gameIsOver = true;
				}
				else {
					const bool eating = next == goal.GetLocation();
					if (eating) {
						snek.Grow();
					}
					snek.MoveBy(deltaLoc);
					if (eating) {
						goal.Respawn(rng, brd, snek);
					}
				}
			}
			++snekSpeedupCounter;
			if (snekSpeedupCounter >= snekSpeedupPeriod) {
				snekSpeedupCounter = 0;
				snekMovePeriod = std::max(snekMovePeriod - 1, snekMovePeriodMin);
			}
		}
	}
	else {
		gameIsStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}

void Game::ComposeFrame() {
	if (gameIsStarted) {
		snek.Draw(brd);
		goal.Draw(brd);
		if (gameIsOver) {
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}
		brd.DrawBorder();
	}
	else {
		SpriteCodex::DrawTitle(290, 225, gfx);
	}
}
