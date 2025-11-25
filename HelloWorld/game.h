#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Constants.h"
#include "Paddle.h"

void spawnBall();
void stepFrame(float);
void setupScene();
bool isColliding(const Paddle& paddle, const Play::GameObject& obj);

