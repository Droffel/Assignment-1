#include "Play.h"
#include "Paddle.h"
#include "Constants.h"

void drawPaddle(const Paddle& paddle) {

	const int paddleWidth = 60;
	const int paddleHeight = 10;

	Play::Point2f topLeft =
	{
		paddle.pos.x - paddleWidth / 2,
		paddle.pos.y - paddleHeight / 2
	};

	Play::Point2f bottomRight =
	{
		paddle.pos.x + paddleWidth / 2,
		paddle.pos.y + paddleHeight / 2
	};

	Play::DrawRect(topLeft, bottomRight, Play::cWhite);
};

void updatePaddle(Paddle& paddle, float dt) {

	const float speed = 400.0f;
	const float halfWidth = 30.0f;

	if (Play::KeyDown(Play::KEY_A)) {
		paddle.pos.x -= speed * dt;
	};
	if (Play::KeyDown(Play::KEY_D)) {
		paddle.pos.x += speed * dt;
	};
	
	if (paddle.pos.x < halfWidth)
		paddle.pos.x = halfWidth;

	if (paddle.pos.x > DISPLAY_WIDTH - halfWidth)
		paddle.pos.x = DISPLAY_WIDTH - halfWidth;
};

