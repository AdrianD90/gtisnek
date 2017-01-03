#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Board brd;
	Snake snek;
	Location deltaLoc = { 1, 0 };
	std::mt19937 rng;
	Goal goal;
	static constexpr int snekMovePeriodMin = 4;
	int snekMovePeriod = 20;
	int snekMoveCounter = 0;
	static constexpr int snekSpeedupPeriod = 180;
	int snekSpeedupCounter = 0;
	bool gameIsOver = false;
	bool gameIsStarted = false;
	/********************************/
};