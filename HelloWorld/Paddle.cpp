#include "Play.h"
#include "Paddle.h"
#include "Constants.h"

void drawPaddle(const Paddle& paddle) {//create rectangle for paddle


	Play::Point2f topLeft =
	{
		paddle.pos.x - PADDLEWIDTH / 2,
		paddle.pos.y - PADDLEHEIGHT / 2
	};

	Play::Point2f bottomRight =
	{
		paddle.pos.x + PADDLEWIDTH / 2,
		paddle.pos.y + PADDLEHEIGHT / 2
	};

	Play::DrawRect(topLeft, bottomRight, paddle.colour, true);
};

void updatePaddle(Paddle& paddle, float dt) {//move paddle left and right with A and D keys

	const float speed = 400.0f;
	const float halfWidth = 30.0f;

	if (Play::KeyDown(Play::KEY_A)) {
		paddle.pos.x -= speed * dt;
	}
	if (Play::KeyDown(Play::KEY_D)) {
		paddle.pos.x += speed * dt;
	}
	
	if (paddle.pos.x < halfWidth)
		paddle.pos.x = halfWidth;
		
	if (paddle.pos.x > DISPLAY_WIDTH - halfWidth)
		paddle.pos.x = DISPLAY_WIDTH - halfWidth;

	if (paddle.hitTimer > 0.0f) {
		paddle.hitTimer -= dt;
		if (paddle.hitTimer <= 0.0f) {
			paddle.hitTimer = 0.0f;
			paddle.colour = Play::cWhite;
		}
	}
};

