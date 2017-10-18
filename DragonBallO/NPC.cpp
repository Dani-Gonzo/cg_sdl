#define ANIM_RIGHT_COUNT 2
#define ANIM_LEFT_COUNT 2
#define ANIM_UP_COUNT 2
#define ANIM_DOWN_COUNT 2
//1.4142f = sqrt(sqr(1) + sqr(1))
#define SQRHYPE 1.4142f	
#include "NPC.h"
#include "Camera.h"
#include <stdlib.h> // Includes rand()

extern Camera gCamera;
extern float gDeltaTime; // How long it's been since the last update

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

namespace {
	int animRightIndices[ANIM_RIGHT_COUNT] = { 0, 1 };
	int animLeftIndices[ANIM_LEFT_COUNT] = { 4, 5 };
	int animUpIndices[ANIM_UP_COUNT] = { 2, 3 };
	int animDownIndices[ANIM_DOWN_COUNT] = { 6, 7 };

	//Animation timers...
	float moveRightTimer = 0.f;
	float moveLeftTimer = 0.f;
	float moveUpTimer = 0.f;
	float moveDownTimer = 0.f;
	float pauseTimer = 0.f;

	//Animation speeds...
	float animMoveSpeed = 10;
	int lastMoveIndex = 4;
}


void NPC::Update() {
	Brain();
	Move();
	Sprite::Update();
}

// Performs movement
void NPC::Move() {

	//Setting velocity...
	float velocity = mMoveSpeed * gDeltaTime;

	//Updates position. SQRHYPE is used so diagnal direction is NOT faster...
	mPos.x += (VertDirection != 0 ? (HorizDirection *
		SQRHYPE) / 2.0f : HorizDirection) * velocity;
	mPos.y += (HorizDirection != 0 ? (VertDirection *
		SQRHYPE) / 2.0f : VertDirection) * velocity;

	//Update animations...
	if (HorizDirection > 0) {
		moveRightTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveRightTimer % ANIM_RIGHT_COUNT;
		mSpriteClipIndex = animRightIndices[index];

		lastMoveIndex = animRightIndices[0];
	}
	else if (HorizDirection < 0) {
		moveLeftTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveLeftTimer % ANIM_LEFT_COUNT;
		mSpriteClipIndex = animLeftIndices[index];

		lastMoveIndex = animLeftIndices[0];
	}
	else if (VertDirection > 0) {
		moveDownTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveDownTimer % ANIM_DOWN_COUNT;
		mSpriteClipIndex = animDownIndices[index];

		lastMoveIndex = animDownIndices[0];
	}
	else if (VertDirection < 0) {
		moveUpTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveUpTimer % ANIM_UP_COUNT;
		mSpriteClipIndex = animUpIndices[index];

		lastMoveIndex = animUpIndices[0];
	}
	else {
		mSpriteClipIndex = lastMoveIndex;
	}
}

// Controls NPC movement direction and when
void NPC::Brain() {
	// Sets NPC to be stopped
	if (moveRightTimer > 5 && HorizDirection == 1) {
		HorizDirection = 0;
		moveRightTimer = 0;
	}
	if (moveLeftTimer > 5 && HorizDirection == -1) {
		HorizDirection = 0;
		moveLeftTimer = 0;
	}
	if (moveUpTimer > 5 && VertDirection == -1) {
		VertDirection = 0;
		moveUpTimer = 0;
	}
	if (moveDownTimer > 5 && VertDirection == 1) {
		VertDirection = 0;
		moveDownTimer = 0;
	}
	if (HorizDirection == 0 && VertDirection == 0) {
		pauseTimer += animMoveSpeed * gDeltaTime;
	}
	// rand() chooses random direction to walk
	if (pauseTimer > 50 && HorizDirection == 0 && VertDirection == 0) {
		int direction = rand() % 4;
		switch (direction) {
		case 0: HorizDirection = -1; break;
		case 1: HorizDirection = 1; break;
		case 2: VertDirection = -1; break;
		case 3: VertDirection = 1; break;
		}
		pauseTimer = 0;
	}

}