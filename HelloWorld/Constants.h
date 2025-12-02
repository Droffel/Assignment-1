#pragma once

const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 360;
const float BRICKHALFWIDTH = 8.0f;
const float BRICKHALFHEIGHT = 5.0f;
const float BRICKWIDTH = 5.0f;
const int DISPLAY_SCALE = 2;
const float SPEED = 4.0f;
const float PADDLEWIDTH = 60.0f;
const float PADDLEHEIGHT = 10.0f;

enum ObjectType {
	TYPE_BALL,
	TYPE_BRICK,
};