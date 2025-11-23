#pragma once
#include "Play.h"
#include "Constants.h"

struct Paddle
{
	Play::Point2f pos;
};
void drawPaddle(const Paddle& paddle);
void updatePaddle(Paddle& paddle, float dt);
