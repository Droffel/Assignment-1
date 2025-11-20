#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Constants.h"
void spawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL,{ DISPLAY_WIDTH / 2, 60 }, 4,"ball");
	GameObject &ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, 1 }) * SPEED;
};

void stepFrame(float) {
	
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);

	for (int i = 0; i < size(ballIds); i++) {	
		Play::UpdateGameObject(Play::GetGameObject(ballIds[i]));
		Play::DrawObject(Play::GetGameObject(ballIds[i]));
		if (int(Play::GetGameObject(ballIds[i]).pos.x) >= DISPLAY_WIDTH || int(Play::GetGameObject(ballIds[i]).pos.x) <= 0) {
			Play::GetGameObject(ballIds[i]).velocity.x = (Play::GetGameObject(ballIds[i]).velocity.x) * (-1);
		};

		if (int(Play::GetGameObject(ballIds[i]).pos.y) >= DISPLAY_HEIGHT || int(Play::GetGameObject(ballIds[i]).pos.y) <= 0) {
			Play::GetGameObject(ballIds[i]).velocity.y = (Play::GetGameObject(ballIds[i]).velocity.y) * (-1);
		};
	};

	for (int i = 0; i < size(brickIds); i++) {
		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
		Play::DrawObject(Play::GetGameObject(brickIds[i]));
		for (int i2 = 0; i2 < size(ballIds); i2++) {
			if (Play::IsColliding(Play::GetGameObject(brickIds[i]), Play::GetGameObject(ballIds[i2]))) {
				Play::DestroyGameObject(brickIds[i]);
				Play::GetGameObject(ballIds[i]).velocity *= -1;
			};
		};
	};

	
};

void setupScene() {
	for (int y = 330; y >= 250; y -= 10) {
		
		for (int x = 32; x < DISPLAY_WIDTH - 32; x += 16) {
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
		};	
	};		
};



