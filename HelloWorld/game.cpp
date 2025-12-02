#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Constants.h"
#include "Paddle.h"
#include <algorithm>
#include <cmath>
#include <string>
#include <array>

Paddle gPaddle;
unsigned int score = 0;
std::string scoreText = "Score: 0";
std::array<unsigned int, 5> highScores = { 0, 0, 0, 0, 0 };

//spawns a ball in the middle of the screen
void spawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL,{ DISPLAY_WIDTH / 2, 60 }, 3,"ball");
	GameObject &ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, 1 }) * SPEED;
};


float Max(float a, float b) { return (a > b) ? a : b; }
float Min(float a, float b) { return (a < b) ? a : b; }

//checks collision between circle and rectangle
bool isCircleBrickColliding(const Play::GameObject& rectObj, const Play::GameObject& circleObj, float halfW, float halfH){

	float left = rectObj.pos.x - halfW;
	float right = rectObj.pos.x + halfW;
	float top = rectObj.pos.y - halfH;
	float bottom = rectObj.pos.y + halfH;

	float closestX = std::clamp(circleObj.pos.x, left, right);
	float closestY = std::clamp(circleObj.pos.y, top, bottom);

	float dx = circleObj.pos.x - closestX;
	float dy = circleObj.pos.y - closestY;

	return (dx * dx + dy * dy) < (circleObj.radius * circleObj.radius);

}

//collision check between paddle and ball
bool isColliding(const Paddle& paddle, const Play::GameObject& obj) {


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


	const float dx = obj.pos.x - Max(topLeft.x, Min(obj.pos.x, bottomRight.x));
	const float dy = obj.pos.y - Max(topLeft.y, Min(obj.pos.y, bottomRight.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}



void stepFrame(float time) {
	
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	
	for (int i = 0; i < size(ballIds); i++) {//updates and draws balls with checks if the ball hits the walls and destroys it if it goes off the bottom of the screen
		Play::UpdateGameObject(Play::GetGameObject(ballIds[i]));
		Play::DrawObject(Play::GetGameObject(ballIds[i]));

		if (Play::GetGameObject(ballIds[i]).pos.x > DISPLAY_WIDTH || Play::GetGameObject(ballIds[i]).pos.x < 0) {

			Play::GetGameObject(ballIds[i]).velocity.x = -Play::GetGameObject(ballIds[i]).velocity.x;
		}

		if (Play::GetGameObject(ballIds[i]).pos.y > DISPLAY_HEIGHT) {
			Play::GetGameObject(ballIds[i]).velocity.y = -Play::GetGameObject(ballIds[i]).velocity.y;
		}

		if (Play::GetGameObject(ballIds[i]).pos.y < 0) {
			Play::DestroyGameObject(ballIds[i]);
		}
	}

	for (int i = 0; i < size(brickIds); i++) {//draws bricks
		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
		Play::DrawObject(Play::GetGameObject(brickIds[i]));

	}

	for (int i2 = 0; i2 < size(ballIds); i2++) {
		Play::GameObject& ball = Play::GetGameObject(ballIds[i2]);
		for (int i = 0; i < size(brickIds); ++i) {

			if (brickIds[i] < 0) continue;

			Play::GameObject& brick = Play::GetGameObject(brickIds[i]);

			if (isCircleBrickColliding(brick, ball, BRICKHALFWIDTH, BRICKHALFHEIGHT)) {
				

				float dx = ball.pos.x - brick.pos.x;
				float dy = ball.pos.y - brick.pos.y;

				float overlapX = ball.radius + BRICKHALFWIDTH - std::abs(dx);
				float overlapY = ball.radius + BRICKHALFHEIGHT - std::abs(dy);
				
				if(overlapX > 0.0f && overlapY > 0.0f) {
					if (overlapX < overlapY) {

						ball.velocity.x = -ball.velocity.x;
					}
					else {
						ball.velocity.y = -ball.velocity.y;
					};
				};
				Play::DestroyGameObject(brickIds[i]);
				brickIds[i] = -1;
				++score;
				scoreText = "Score: " + std::to_string(score);
				break;

				/*float relativeHit = (Play::GetGameObject(ballIds[i2]).pos.x - Play::GetGameObject(brickIds[i]).pos.x / (PADDLEWIDTH * 0.5f));
				relativeHit = std::clamp(relativeHit, -1.0f, 1.0f);

				const float maxDeflectionDegree = 60.0f;
				const float maxDeflectionRadian = Play::DegToRad(maxDeflectionDegree);

				float bounceAngle = relativeHit * maxDeflectionRadian;

				float incomingVert = (Play::GetGameObject(ballIds[i2]).velocity.y >= 0.0f) ? 1.0f : -1.0f;
				float outVert = -incomingVert;

				Play::Vector2f newDir;
				newDir.x = std::sin(bounceAngle);
				newDir.y = outVert * std::abs(std::cos(bounceAngle));

				float currentSpeed = (Play::GetGameObject(ballIds[i2]).velocity.Length());
				if (currentSpeed <= 0.0001f) currentSpeed = SPEED;

				newDir.Normalize();
				Play::GetGameObject(ballIds[i2]).velocity = newDir * currentSpeed;*/
			}
		}
	}

	
	updatePaddle(gPaddle, time);
	drawPaddle(gPaddle);
	Play::DrawDebugText(Play::Point2D(80, 10), scoreText.c_str(), Play::cWhite);
	


	for (int id : ballIds)
	{
		Play::GameObject& ball = Play::GetGameObject(id);

		if (isColliding(gPaddle, ball))
		{
			float relativeHit = (ball.pos.x - gPaddle.pos.x) / (PADDLEWIDTH * 0.5f);
			relativeHit = std::clamp(relativeHit, -1.0f, 1.0f);

			const float maxDeflectionDegree = 60.0f;
			const float maxDeflectionRadian = Play::DegToRad(maxDeflectionDegree);

			float bounceAngle = relativeHit * maxDeflectionRadian;

			float incomingVert = (ball.velocity.y >= 0.0f) ? 1.0f : -1.0f;
			float outVert = -incomingVert;

			Play::Vector2f newDir;
			newDir.x = std::sin(bounceAngle);
			newDir.y = outVert * std::abs(std::cos(bounceAngle));

			float currentSpeed = ball.velocity.Length();
			if (currentSpeed <= 0.0001f) currentSpeed = SPEED;

			newDir.Normalize();
			ball.velocity = newDir * currentSpeed;

			gPaddle.colour = Play::cBlue;
			gPaddle.hitTimer = 0.15f;

		};
	};
	
};


void setupScene() {
	for (int y = 330; y >= 250; y -= 10) {
		
		for (int x = 32; x < DISPLAY_WIDTH - 32; x += 16) {
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 10, "brick");
		};	
	};

	gPaddle.pos = { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - (DISPLAY_HEIGHT - 50) };

	

};





