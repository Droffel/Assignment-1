#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Constants.h"
#include "Paddle.h"

struct BrickSides
{
	Play::Point2f pos;
};

void spawnBall();
void stepFrame(float);
void setupScene();
bool isColliding(const Paddle& paddle, const Play::GameObject& obj);
bool isCircleBrickColliding(const Play::GameObject& rectObj, const Play::GameObject& circleObj, float halfW, float halfH);

