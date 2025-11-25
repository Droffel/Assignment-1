#pragma once
#include "Play.h"
#include "Constants.h"

struct Paddle
{
	Play::Point2f pos;

	Play::Colour colour{ 100.0f, 100.0f, 100.0f };
	float hitTimer{ 0.0f };
};
void drawPaddle(const Paddle& paddle);
void updatePaddle(Paddle& paddle, float dt);
